#ifndef RENDERER_H
#define RENDERER_H

#include "window.hpp"
#include "shader.hpp"

namespace Precision{
  
class Renderer{
public:
  Window m_window {}; 
  Shader m_shader {};

public:
  Renderer(){};
  ~Renderer();
  void init_window(const char *name, const int width, const int height);
  void init_shader(const char *vertex_path, const char *fragment_path);
};

}; // namespace Precision

#endif
