#include "../include/renderer.hpp"

namespace Precision{

Renderer::~Renderer(){
  std::cout << "RENDERER::DESTROYED" << std::endl;
}

void Renderer::init_window(const char *name, const int width, const int height){
  m_window.init(name, width, height);
}

void Renderer::init_shader(const char *vertex_path, const char *fragment_path){
  m_shader.init(vertex_path, fragment_path);
}

void Renderer::init_vao(){
  m_vao.init();
}

void Renderer::init_vbo(const float *arr, const size_t arr_size, const unsigned int draw_kind, const size_t stride, const std::vector<vertex_attr_data> attr_data){
  m_vao.init_vbo(arr, arr_size, draw_kind, stride, attr_data);
}

void Renderer::draw_vbo(unsigned int mode, unsigned int start_index, unsigned int vertice_count){
  m_vao.bind();
  glDrawArrays(GL_TRIANGLES, 0, vertice_count);
}

} // namespace Precision
