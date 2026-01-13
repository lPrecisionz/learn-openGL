#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Renderer{
public:
  GLFWwindow *m_window;

public:
  Renderer() : m_window(nullptr) {};
  void init();

private: 
  const unsigned int base_width =  800; 
  const unsigned int base_height = 600;
};
