#ifndef APP_H
#define APP_H

#include <iostream> 
#include "renderer.hpp"
namespace Precision {

const float triangle[] = {
  // position          // color            //texture coord
  -0.75f, -0.25f,  0.0f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f,// bottom left
   0.0f,   0.75f , 0.0f,  0.0f, 1.0f, 0.0f, 0.5f, 1.0f,// top
   0.75f, -0.25f, -0.0f,  0.0f, 0.0f, 1.0f, 1.0f, 0.0f// bottom right
};

// this is horrible, please fix it later
const std::vector<vertex_attr_data> triangle_data {
  // type -> location -> attr count -> offset
  vertex_attr_data {GL_FLOAT, 0, 3, 0}, 
  vertex_attr_data {GL_FLOAT, 1, 3, 3 * sizeof(float)},
  vertex_attr_data {GL_FLOAT, 2, 2, 6 * sizeof(float)}

}; 

const float square[] = {
  // position          // color            //texture coord
   -0.5f,  -0.5f,  0.0f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f,// bottom left
   -0.5f,   0.5f , 0.0f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,// top left
    0.5f,  -0.5f, -0.0f,  0.0f, 0.0f, 1.0f, 1.0f, 0.0f,// bottom right
    0.5f,   0.5f, -0.0f,  0.0f, 0.0f, 1.0f, 1.0f, 1.0f //  top right right
};

const unsigned int square_indices[] {
  0, 1, 2, 
  3, 2, 1
};

const unsigned int vertice_count { 4 };
const unsigned int indice_count  { 6 };

const std::vector<vertex_attr_data> square_data {
  // type -> location -> attr count -> offset
  vertex_attr_data {GL_FLOAT, 0, 3, 0}, 
  vertex_attr_data {GL_FLOAT, 1, 3, 3 * sizeof(float)},
  vertex_attr_data {GL_FLOAT, 2, 2, 6 * sizeof(float)}
}; 
const float cube[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

const std::vector<vertex_attr_data> cube_data {
  // type -> location -> attr count -> offset
  vertex_attr_data {GL_FLOAT, 0, 3, 0}, 
  vertex_attr_data {GL_FLOAT, 1, 2, 3 * sizeof(float)},
}; 

const glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f), 
    glm::vec3( 2.0f,  5.0f, -15.0f), 
    glm::vec3(-1.5f, -2.2f, -2.5f),  
    glm::vec3(-3.8f, -2.0f, -12.3f),  
    glm::vec3( 2.4f, -0.4f, -3.5f),  
    glm::vec3(-1.7f,  3.0f, -7.5f),  
    glm::vec3( 1.3f, -2.0f, -2.5f),  
    glm::vec3( 1.5f,  2.0f, -2.5f), 
    glm::vec3( 1.5f,  0.2f, -1.5f), 
    glm::vec3(-1.3f,  1.0f, -1.5f)  
};


class App{
public:
  static void run();
};

}; // namespace Precision

#endif
