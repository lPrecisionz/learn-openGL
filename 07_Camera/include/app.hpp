#ifndef APP_H
#define APP_H

#include <iostream> 
#include "renderer.hpp"
namespace Precision {

const float triangle[] = {
  // position          // color
  -0.75f, -0.25f, 0.0f,  1.0f, 0.0f, 0.0f, // bottom left
   0.0f,  0.75f, 0.0f,  0.0f, 1.0f, 0.0f, // top
   0.75f,  -0.25f, -0.0f,  0.0f, 0.0f, 1.0f  // bottom right
};

// this is horrible, please fix it later
const std::vector<vertex_attr_data> triangle_data {
  // type -> location -> attr count -> offset
  vertex_attr_data {GL_FLOAT, 0, 3, 0}, 
  vertex_attr_data {GL_FLOAT, 1, 3, 3 * sizeof(float)}
}; 

class App{
public:
  static void run();
};

}; // namespace Precision

#endif
