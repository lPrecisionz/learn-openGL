#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <iostream>

namespace Prec{
class Shader{
public:
  unsigned int m_program_id, 
               m_vertex_id, 
               m_fragment_id;

public:
  Shader(const char* vertex_path, const char* fragment_path);
  void use();
  void set_bool (const std::string &name, bool  value) const;
  void set_int  (const std::string &name, int   value) const;
  void set_float(const std::string &name, float value) const;
  void set_uniform_color(const char* uniform_name, float r, float g, float b, float a);

private:
  std::string read_from_file(const char* source);
  void compile_shaders(const char *vertex_source, const char* fragment_source);
  void compile(unsigned int shader_kind, const char* source);
  void link_program();
  void delete_shaders();
};

} //namespace Prec

#endif
