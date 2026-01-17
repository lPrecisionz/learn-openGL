#ifndef RENDERER_H
#define RENDERER_H

#include "window.hpp"
#include "shader.hpp"
#include "vao.hpp"
namespace Precision{
  
class Renderer{
public:
  Window m_window {}; 
  Shader m_shader {};
  VAO    m_vao    {}; // currently doing single VAO, expect to have a vector<vao> later

public:
  Renderer(){};
  ~Renderer();
  void init_window(const char *name, const int width, const int height);
  void init_shader(const char *vertex_path, const char *fragment_path);
  void init_vao();
  // maybe have a function pointer to point to vao->init_vbo() ?
  void init_vbo(const float *arr, const size_t arr_size, const unsigned int draw_kind, const size_t stride, const std::vector<vertex_attr_data> attr_data);
  void init_ebo(const unsigned int *arr, const size_t arr_size, const unsigned int draw_kind, const size_t stride);
  void draw_vbo(unsigned int mode, unsigned int start_index, unsigned int vertice_count);
  void draw_ebo(unsigned int mode, unsigned int start_index, unsigned int indice_count);

};

}; // namespace Precision

#endif
