#include "../include/renderer.hpp"

const char *vertex_shader_source = "#version 330 core\n"
  "layout (location=0) in vec3 aPos;\n"
  "void main()\n"
  "{\n"
  " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
  "}\0";

const char *fragment_shader_source = "#version 330 core\n"
  "out vec4 FragColor;\n"
  "void main()\n"
  "{\n"
  "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
  "}\0";
float vertices[] = {
   0.0f, 0.0f, 0.0f, 
   0.5f, 0.5f, 0.0f, 
   1.0f, 0.0f, 0.0f
};

unsigned int indices[] = {
  0, 1, 3, 
  1, 2, 3
};

int main(){
    Prec::Renderer renderer;
    renderer.init("my window");
    renderer.init_shader(GL_FRAGMENT_SHADER, fragment_shader_source);
    renderer.init_shader(GL_VERTEX_SHADER, vertex_shader_source);
    renderer.link_program();
    renderer.init_buffer(Prec::BufferKind::VBO, vertices, sizeof(float) * 3);
    //renderer.init_buffer(Prec::BufferKind::EBO, )
    while (!glfwWindowShouldClose(renderer.m_window)){
      renderer.process_input();
      glfwSwapBuffers(renderer.m_window);
      glfwPollEvents();
    }

    return 0;
}
