#ifndef VAO_H
#define VAO_H

#include "common.hpp"

namespace Precision{

struct vertex_attr_data {
  unsigned int type, // GL_FLOAT - GL_UNSIGNED_INT -- etc
               location,
               attr_count;      
  size_t offset;

  vertex_attr_data(unsigned int t, unsigned int loc, unsigned int ac, size_t off) : type(t), location(loc), attr_count(ac), offset(off) {};
};

class VAO {
public:
  unsigned int m_ID, 
               m_VBO, 
               m_EBO;

public:
  VAO() {};
  void init();
  void init_vbo(const float *arr, const size_t arr_size, const unsigned int draw_kind, const size_t stride, const std::vector<vertex_attr_data> attr_data);
  void init_ebo(const unsigned int *indice_arr, const size_t arr_size,const unsigned int draw_kind);
  void bind();
};

} //namespace Precision

#endif
