#ifndef WINDOW_H
#define WINDOW_H

#include "common.hpp"

namespace Precision{

constexpr int GLFW_VERSION = 3;

class Window{
private:
  GLFWwindow *m_window { nullptr };
  const char *m_name;
  unsigned int m_height,
               m_width;
                 
public:
  Window() {};
  void init(const char *name, const int width, const int height);
  ~Window(); 
  GLFWwindow *get_window();
  static void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0,0,width,height);
  }

};

} // namespace Precision

#endif
