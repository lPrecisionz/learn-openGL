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

} // namespace Precision
