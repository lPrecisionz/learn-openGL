#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace Prec{

constexpr unsigned int LOCAL_VERSION = 3;

class Renderer{
public:
  const char  *m_window_name;
  GLFWwindow  *m_window;
  unsigned int m_vertex_shader;
  unsigned int m_fragment_shader;
  unsigned int m_shader_program;

public:
  Renderer() : m_window(nullptr) {};
  ~Renderer();
  void init(const char* window_name);
  void process_input();
  void init_shader(const int shader_kind, const char* src_path);
  void link_program();
  
private: 
  const unsigned int base_width =  800; 
  const unsigned int base_height = 600;
  void delete_shaders();

};

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

} //namespace Precsr
