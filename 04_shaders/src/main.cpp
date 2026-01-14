#include "../include/renderer.hpp"
#include <math.h>

const char *vertex_shader_source = "#version 330 core\n"
  "layout (location=0) in vec3 aPos;\n"
  "layout (location=1) in vec3 aColor;\n"
  "out vec3 our_color;\n"
  "void main()\n"
  "{\n"
  " our_color = aColor;\n"
  " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
  "}\0";

const char *fragment_shader_source = "#version 330 core\n"
  "out vec4 FragColor;\n"
  "in vec3 our_color;\n"
  "void main()\n"
  "{\n"
  "FragColor = vec4(our_color, 1.0);\n"
  "}\0";

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
  glUseProgram(renderer.m_shader_program);
  glBindVertexArray(renderer.m_VAO);
  glDrawArrays(GL_TRIANGLES, 0, vertice_count);
  glBindVertexArray(0);
}

void draw_element(Prec::Renderer &renderer, const unsigned int &indice_count){
  glUseProgram(renderer.m_shader_program);
  glBindVertexArray(renderer.m_VAO);
  glDrawElements(GL_TRIANGLES, indice_count, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

int main(){
  Prec::Renderer renderer;
  renderer.init("my window");
  renderer.init_shader(GL_VERTEX_SHADER, vertex_shader_source);
  renderer.init_shader(GL_FRAGMENT_SHADER, fragment_shader_source);
  renderer.link_program();
  renderer.init_vao();
  renderer.init_vbo(vertices, sizeof(vertices), sizeof(float) * 6, sizeof(float)*3); 
  //renderer.init_ebo(indices, sizeof(indices), sizeof(float) * 3); 

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
