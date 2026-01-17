#include "../include/vao.hpp"
#include "common.hpp"

namespace Precision{

void VAO::init(){
  unsigned int vao_count { 1 };
  glGenVertexArrays(vao_count, &m_ID);
}

void VAO::init_vbo(const float *arr, const size_t arr_size, const unsigned int draw_kind, const size_t stride, const std::vector<vertex_attr_data> attr_data){
  glGenBuffers(1, &m_VBO);
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  glBufferData(GL_ARRAY_BUFFER, arr_size, arr, draw_kind);

  unsigned int normalize_flag = GL_FALSE;
  for(auto i : attr_data){
    glVertexAttribPointer(i.location, i.attr_count, i.type, normalize_flag, stride, (void*)i.offset);
    glEnableVertexAttribArray(i.location);
  }
  std::cout << "VBO::BINDED::" << m_VBO;
}

void VAO::init_ebo(){

}

void VAO::bind(){
  glBindVertexArray(m_ID);
}

} // namespace Precision
