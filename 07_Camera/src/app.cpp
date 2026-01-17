#include "../include/app.hpp"
namespace Precision{

constexpr unsigned int SCREEN_WIDTH  = 800; 
constexpr unsigned int SCREEN_HEIGHT = 600;
constexpr std::string  WINDOW_NAME   = "I love Clairo";

const char *vertex_path   = "./shaders/vertex.glsl";
const char *fragment_path = "./shaders/fragment.glsl";
/*
void check_error(){
  std::cout << "glGetError()::" << glGetError() << std::endl;
}
*/
void App::run(){
  Renderer renderer {};
  renderer.init_window(WINDOW_NAME.c_str(), SCREEN_WIDTH, SCREEN_HEIGHT);
  renderer.init_shader(vertex_path, fragment_path);
  renderer.init_vao();
  renderer.init_vbo(
    triangle, 
    sizeof(triangle), 
    GL_STATIC_DRAW, 
    sizeof(float) * 6, 
    triangle_data 
  );
  renderer.m_shader.gen_texture("./img/clairo.jpg", 0, "texture1");

  while(!glfwWindowShouldClose(renderer.m_window.get_window())){
    glClearColor(0.5f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    renderer.draw_vbo(GL_TRIANGLES, 0, 3);
    glfwPollEvents();
    glfwSwapBuffers(renderer.m_window.get_window());
  }
}

}; // namespace Precision
