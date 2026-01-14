#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace Prec{

constexpr unsigned int LOCAL_VERSION = 3;

enum BufferKind {
  VBO, 
  EBO
};

class Renderer{
public:
  const char  *m_window_name;
  GLFWwindow  *m_window;
  unsigned int m_vertex_shader, 
               m_fragment_shader, 
               m_shader_program, 
               m_VBO, 
               m_EBO, 
               m_VAO;

public:
  Renderer() : m_window(nullptr) {};
  ~Renderer();
  void init(const char* window_name);
  void process_input();
  void init_shader(const int shader_kind, const char* src_path);
  void link_program();
  void init_vao();
  void init_vbo(const float *arr, const size_t arr_size, const size_t stride, const size_t offset);
  void init_ebo(const unsigned int *indices, const size_t arr_size, const size_t stride, const size_t offset);
  void set_uniform_color(const char* uniform_name, float r, float g, float b, float a);
  
private: 
  const unsigned int base_width =  800; 
  const unsigned int base_height = 600;
  void delete_shaders();

};

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

} //namespace Precsr
