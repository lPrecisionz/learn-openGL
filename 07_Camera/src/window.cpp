#include "../include/window.hpp"

namespace Precision{

void Window::init(const char *name, const int width, const int height){
  m_name   = name;
  m_width  = width;
  m_height = height;

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GLFW_VERSION);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GLFW_VERSION);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  m_window = glfwCreateWindow(m_width, m_height, m_name, NULL, NULL);
  glfwMakeContextCurrent(m_window);
  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
    std::cerr << "ERROR::WINDOW::GLADGLLOADER" << std::endl;
    throw std::runtime_error("Couldn't attach GLAD");
  }

  glViewport(0, 0, m_width, m_height); 
  glfwSetFramebufferSizeCallback(m_window,framebuffer_size_callback); 
  std::cout << "WINDOW::INITIALIZED" << std::endl;
}

Window::~Window() {
  glfwTerminate();
  std::cout << "WINDOW::TERMINATED";
}

GLFWwindow *Window::get_window() {
  return m_window;
}

} //namespace Precision
