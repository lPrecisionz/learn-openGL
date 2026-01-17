#include "../include/app.hpp"
namespace Precision{

constexpr unsigned int SCREEN_WIDTH = 800; 
constexpr unsigned int SCREEN_HEIGHT = 600;

constexpr std::string WINDOW_NAME = "I love Clairo";

void App::run(){
  Renderer renderer {};
  renderer.init_window(WINDOW_NAME.c_str(), SCREEN_WIDTH, SCREEN_HEIGHT);

  while(!glfwWindowShouldClose(renderer.m_window.get_window())){
    glfwPollEvents();
  }
}

}; // namespace Precision
