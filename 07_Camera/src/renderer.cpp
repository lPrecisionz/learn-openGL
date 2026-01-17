#include "../include/renderer.hpp"

namespace Precision{

Renderer::~Renderer(){
  std::cout << "RENDERER::DESTROYED" << std::endl;
}

void Renderer::init_window(const char *name, const int width, const int height){
  m_window.init(name, width, height);
}

} // namespace Precision
