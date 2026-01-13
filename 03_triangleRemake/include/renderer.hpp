#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace Prec{

constexpr unsigned int LOCAL_VERSION = 3;

class Renderer{
public:
  GLFWwindow *m_window;
  const char *m_window_name;

public:
  Renderer() : m_window(nullptr) {};
  ~Renderer();
  void init(const char* window_name);
  void process_input();

private: 
  const unsigned int base_width =  800; 
  const unsigned int base_height = 600;
};

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

} //namespace Prec
