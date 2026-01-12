#include "../include/renderer.hpp"
#include <stdexcept>


Renderer::Renderer(){
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, LOCAL_VERSION);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, LOCAL_VERSION);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  m_window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, m_window_name, NULL, NULL);
  
  if(m_window == NULL){
    glfwTerminate();
    throw std::runtime_error("Failed to create GLFW window.");
  }

  glfwMakeContextCurrent(m_window);
  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
    throw std::runtime_error("Failed to initialize GLAD");
  }

  glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
  glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
}

void Renderer::process_input(){
  if(glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(m_window, true);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height){
  glViewport(0, 0, width, height);
}

Renderer::~Renderer(){
  glfwTerminate();
}
