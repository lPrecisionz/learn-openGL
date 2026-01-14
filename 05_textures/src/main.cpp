#include "../include/renderer.hpp"
#include <math.h>
#include <ostream>
#include "stb_image.cpp"

float vertices[] = {
    // spatial          // color
    0.0f, 0.5f,  0.0f,  1.0f, 0.0f, 0.0f, //top
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, //bottom left 
    0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
};

unsigned int indices[] = {
  0, 1, 3, 
  1, 2, 3
};

const unsigned int indice_count = 6;
const unsigned int vertice_count = 3;

void draw_triangle(Prec::Renderer &renderer, const unsigned int &vertice_count){
  glUseProgram(renderer.m_shader->m_program_id);
  glUseProgram(3);
  glBindVertexArray(renderer.m_VAO);
  glDrawArrays(GL_TRIANGLES, 0, vertice_count);
  glBindVertexArray(0);
}

void draw_element(Prec::Renderer &renderer, const unsigned int &indice_count){
  glUseProgram(renderer.m_shader->m_program_id);
  glBindVertexArray(renderer.m_VAO);
  glDrawElements(GL_TRIANGLES, indice_count, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

int main(){
  // loading texture
  int width, height, channels_no;
  unsigned char* data = stbi_load("./img/container.jpg", &width, &height, &channels_no, 0);

  const char* vertex_shader_path   = "./shaders/vertex.glsl"; 
  const char* fragment_shader_path = "./shaders/fragment.glsl";

  Prec::Renderer renderer;
  renderer.init("I love clairo");
  renderer.init_shader(vertex_shader_path, fragment_shader_path);
  renderer.init_vao();

  size_t stride = sizeof(float) * 6;
  size_t offset = sizeof(float) * 3;
  renderer.init_vbo(vertices, sizeof(vertices), stride, offset); 
  //renderer.init_ebo(indices, sizeof(indices), sizeof(float) * 3); 
  std::cout << "Program :\t" << renderer.m_shader->m_program_id << std::endl
            << "VAO ID :\t"  << renderer.m_VAO << std::endl 
            << "VBO ID :\t"  << renderer.m_VBO << std::endl;

  // exercise 2 - set h offset
  std::string uniform_name = "h_offset";
  renderer.m_shader->use();
  renderer.m_shader->set_float(uniform_name, 0.5f);

  while (!glfwWindowShouldClose(renderer.m_window)){
    renderer.process_input();

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    draw_triangle(renderer, vertice_count);

    glfwSwapBuffers(renderer.m_window);
    glfwPollEvents();
  }

  return 0;
}
