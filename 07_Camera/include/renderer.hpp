#ifndef RENDERER_H
#define RENDERER_H

#include "window.hpp"

namespace Precision{
  
class Renderer{
public:
  Window m_window {}; 

public:
  Renderer(){};
  ~Renderer();
  void init_window(const char *name, const int width, const int height);
};

}; // namespace Precision

#endif
