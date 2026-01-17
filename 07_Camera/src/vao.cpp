#include "../include/vao.hpp"

namespace Precision{

void VAO::init(){
  unsigned int vao_count { 1 };
  glGenVertexArrays(vao_count, &m_ID);
  std::cout << "VAO::INITIALIZED::" << m_ID << std::endl;
}

void VAO::init_vbo(const float *arr, const size_t arr_size, const unsigned int draw_kind, const size_t stride, const std::vector<vertex_attr_data> attr_data){
  bind();
  glGenBuffers(1, &m_VBO);
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  glBufferData(GL_ARRAY_BUFFER, arr_size, arr, draw_kind);

  unsigned int normalize_flag = GL_FALSE;
  for(auto i : attr_data){
    glVertexAttribPointer(i.location, i.attr_count, i.type, normalize_flag, stride, (void*)i.offset);
    glEnableVertexAttribArray(i.location);
  }
  std::cout << "VBO::BINDED::" << m_VBO << std::endl;
}

void VAO::init_ebo(const unsigned int *indice_arr, const size_t arr_size,const unsigned int draw_kind, const size_t stride){
  bind();
  glGenBuffers(1, &m_EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, arr_size, indice_arr, draw_kind);
  std::cout << "EBO::BINDED::" << m_EBO << std::endl;
}

void VAO::bind(){
  glBindVertexArray(m_ID);
}

 } // namespace Precision
