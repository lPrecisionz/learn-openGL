#include "../include/renderer.hpp"

namespace Prec{

void Renderer::init(const char* window_name){
  glfwInit();
  m_window_name = window_name;
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, LOCAL_VERSION);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, LOCAL_VERSION);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  m_window = glfwCreateWindow(base_width, base_height,m_window_name, NULL, NULL);

  if(m_window == nullptr){
    throw std::runtime_error("Failed to initialize window.");
    glfwTerminate();
    return;
  }

  glfwMakeContextCurrent(m_window);
  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    throw std::runtime_error("Failed to initialize GLAD.");
  
  glViewport(0,0,base_width,base_height);
  glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
}

Renderer::~Renderer(){
  glfwTerminate();
}

void Renderer::process_input(){
  if(glfwGetKey(m_window, GLFW_KEY_ENTER) == GLFW_PRESS){
    glfwSetWindowShouldClose(m_window, true);
  }
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height){
  glViewport(0,0,width,height);
}

} //namespace Prec
