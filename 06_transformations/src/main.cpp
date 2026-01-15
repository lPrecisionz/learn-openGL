#include "../include/renderer.hpp"
#include <math.h>
#include <ostream>
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"

float vertices[] = {
  // positions          // colors           // texture coords (note that we changed them to 'zoom in' on our texture image)
  0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
  0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
  -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
  -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
};
unsigned int indices[] = {
  0, 1, 3, 
  1, 2, 3
};

const unsigned int indice_count = 6;
const unsigned int vertice_count = 4;
 

void draw_triangle(Prec::Renderer &renderer, const unsigned int &vertice_count){
  glUseProgram(renderer.m_shader->m_program_id);
  glBindVertexArray(renderer.m_VAO);
  glDrawArrays(GL_TRIANGLES, 0, vertice_count);
  glBindVertexArray(0);
}

void draw_element(Prec::Renderer &renderer, const unsigned int &indice_count, const unsigned int &texture0, const unsigned int &texture1){
  glUseProgram(renderer.m_shader->m_program_id);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture0); 
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, texture1); 
  glDrawElements(GL_TRIANGLES, indice_count, GL_UNSIGNED_INT, 0);
  glBindVertexArray(renderer.m_VAO);
}

unsigned int gen_texture(const char* path, const unsigned int tex_index){
  int width, height, channel_no;
  stbi_set_flip_vertically_on_load(true);
  unsigned char* img_data = stbi_load(path, &width, &height, &channel_no, 0);
  if(!img_data){
    std::cout << "Couldn't load image " << path << std::endl;
    return 0;
  }

  unsigned int texture_id;
  unsigned int rgb_kind;
  if(tex_index == 0){
    rgb_kind = GL_RGB;
  } else{
    rgb_kind = GL_RGBA;
  }
  glGenTextures(1, &texture_id);
  glActiveTexture(GL_TEXTURE0 + tex_index);
  glBindTexture(GL_TEXTURE_2D, texture_id);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, rgb_kind, GL_UNSIGNED_BYTE, img_data);
  glGenerateMipmap(GL_TEXTURE_2D);
  stbi_image_free(img_data);
  std::cout << "Loaded texture " << tex_index << " and destroyed img." << std::endl;
  return texture_id;
}

void transform_vector(){
  glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
  glm::mat4 trans = glm::mat4(1.0f);
  std::cout << vec.x << " " << vec.y << " " << vec.z << std::endl;
  trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
  vec = trans * vec;
  std::cout << vec.x << " " << vec.y << " " << vec.z << std::endl;
}

int main(){
  
  transform_vector();
  return 0;
  const char* vertex_shader_path   = "./shaders/vertex.glsl"; 
  const char* fragment_shader_path = "./shaders/fragment.glsl";

  Prec::Renderer renderer;
  renderer.init("I love clairo");
  renderer.init_shader(vertex_shader_path, fragment_shader_path);
  renderer.init_vao();

  unsigned int texture0 = gen_texture("./img/container.jpg", 0);
  unsigned int texture1 = gen_texture("./img/awesomeface.png", 1);

  size_t stride = sizeof(float) * 8;
  size_t offset = sizeof(float) * 3;
  renderer.init_vbo(vertices, sizeof(vertices), stride, offset); 
  renderer.init_ebo(indices, sizeof(indices), stride, 0); 

  std::cout << "Program :\t" << renderer.m_shader->m_program_id << std::endl
            << "VAO ID :\t"  << renderer.m_VAO << std::endl 
            << "VBO ID :\t"  << renderer.m_VBO << std::endl;

  // exercise 2 - set h offset
  std::string uniform_name = "h_offset";
  renderer.m_shader->use();
  renderer.m_shader->set_float(uniform_name, 0.0f);
  renderer.m_shader->set_int("ourTexture_0", 0);
  renderer.m_shader->set_int("ourTexture_1", 1);

  float mix_factor = 0;
  while (!glfwWindowShouldClose(renderer.m_window)){
    renderer.process_input();
    if(glfwGetKey(renderer.m_window, GLFW_KEY_UP) == GLFW_PRESS){
      mix_factor += 0.01;     
    }
    if(glfwGetKey(renderer.m_window, GLFW_KEY_DOWN) == GLFW_PRESS){
      mix_factor -= 0.01;     
    }
    
    renderer.m_shader->set_float("mix_factor", mix_factor);
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    draw_element(renderer, indice_count, texture0, texture1);

    glfwSwapBuffers(renderer.m_window);
    glfwPollEvents();
  }

  return 0;
}
