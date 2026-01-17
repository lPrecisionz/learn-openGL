#ifndef VAO_H
#define VAO_H

#include "common.hpp"

namespace Precision{

struct vertex_attr_data {
  unsigned int type;    // GL_FLOAT - GL_UNSIGNED_INT -- etc
  unsigned int location;
  size_t       attr_count,
               offset;
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
  void init_ebo();
  void bind();
};

} //namespace Precision

#endif
