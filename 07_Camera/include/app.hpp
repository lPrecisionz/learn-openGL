#ifndef APP_H
#define APP_H

#include <iostream> 
#include "renderer.hpp"
namespace Precision {

const float vertices[] = {
  // position          // color
  -1.0f, -1.0f, 0.0f,  1.0f, 1.0f, 1.0f, // bottom left
   0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 1.0f, // top
   1.1f,  1.1f, 0.0f,  1.0f, 1.0f, 1.0f  // bottom right
};

class App{
public:
  static void run();
};

}; // namespace Precision

#endif
