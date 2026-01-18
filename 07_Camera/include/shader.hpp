#ifndef SHADER_H
#define SHADER_H

#include "common.hpp"
#include <string.h> 
#include <fstream>
#include <sstream>
#include "texture.hpp"

namespace Precision{

class Shader{
public:
  unsigned int m_program_id, 
               m_vertex, 
               m_fragment;
  Texture m_texture;

public:
  Shader() {};
  void init(const char* vertex_path, const char *fragment_path);
  void set_int  (const char* uniform, int val);
  void set_float(const char* uniform, float val); 
  void set_bool (const char* uniform, bool val);
  void set_mat4fv(const char* uniform, glm::mat4 &mat);
  void use() { glUseProgram(m_program_id); }
  void gen_texture(const char *file_path, const unsigned int unit, const std::string sampler_name);

private:
  const std::string read_file(const char *path);
  void compile(unsigned int shader_kind, const char *source_code);
  void link();
};

} // namespace Precision

#endif 
