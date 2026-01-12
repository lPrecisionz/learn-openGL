#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

constexpr unsigned int LOCAL_VERSION = 3;
constexpr unsigned int WINDOW_WIDTH  = 800;
constexpr unsigned int WINDOW_HEIGHT = 600;

class Renderer{
public: 
  GLFWwindow *m_window;
  const char *m_window_name {"Window"};

public:
  Renderer();
  ~Renderer();
  void process_input();

};

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

