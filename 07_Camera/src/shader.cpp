#include "../include/shader.hpp"

namespace Precision{

void Shader::init(const char* vertex_path, const char *fragment_path){
  std::string vertex_code   = read_file(vertex_path);
  std::string fragment_code = read_file(fragment_path);

  compile(GL_VERTEX_SHADER, vertex_code.c_str());
  compile(GL_FRAGMENT_SHADER, fragment_code.c_str());
}
  
const std::string Shader::read_file(const char *path){
  std::string   shader_code; 
  std::ifstream shader_file;
  
  shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  try{
    shader_file.open(path);
    std::stringstream shader_stream;
    shader_stream << shader_file.rdbuf();
    shader_file.close();
    shader_code = shader_stream.str();
  } catch(std::ifstream::failure &e){
    std::cout << "SHADER::ERROR::READING::FILE" << std::endl << e.what();
  }
  return shader_code;
}

void Shader::compile(unsigned int shader_kind, const char *source_code){
  unsigned int *curr_shader     { nullptr };
  unsigned int src_string_count {    1    };

  if(shader_kind == GL_VERTEX_SHADER)
    curr_shader = &m_vertex;
  if(shader_kind == GL_FRAGMENT_SHADER)
    curr_shader = &m_fragment;

  *curr_shader = glCreateShader(shader_kind);
  glShaderSource(*curr_shader, src_string_count, &source_code, NULL);
  glCompileShader(*curr_shader);

  int  success{ 0 };
  char log    [512];

  glGetShaderiv(*curr_shader, GL_COMPILE_STATUS, &success);
  if(!success){
    glGetShaderInfoLog(*curr_shader, 512, NULL, log);
    std::cout << "SHADER::ERROR::COMPILING" << std::endl << log;
    return;
  }
  std::cout << "COMPILED::SHADER::" << *curr_shader << std::endl;
}

void Shader::set_int  (const char* uniform, int val) {}

void Shader::set_float(const char* uniform, int val) {}

void Shader::set_bool (const char* uniform, int val) {}

} // Shader
