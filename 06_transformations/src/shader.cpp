#include "../include/shader.hpp"

namespace Prec{

Shader::Shader(const char* vertex_path, const char* fragment_path){
  std::string vertex_code   = read_from_file(vertex_path);
  std::string fragment_code = read_from_file(fragment_path);

  compile(GL_VERTEX_SHADER,   vertex_code.c_str());
  compile(GL_FRAGMENT_SHADER, fragment_code.c_str());
  link_program();
  delete_shaders();
}

std::string Shader::read_from_file(const char* source){
  std::string   shader_code;
  std::ifstream shader_file;

  shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  try{
    std::cout << source << std::endl;
    shader_file.open(source);
    std::stringstream shader_stream;
    shader_stream << shader_file.rdbuf();
    shader_file.close();
    shader_code = shader_stream.str();
  } catch(std::ifstream::failure &e){
    std::cout << "ERROR::SHADER::FILE::NOT_READ" << std::endl;
  }
  // reference to shader_code.c_str(); dies after this function, so we return the string instead
  return shader_code; 
}

void Shader::compile(unsigned int shader_kind, const char* source){
  unsigned int *curr_shader = nullptr;
  unsigned int src_string_count = 1;

  if(shader_kind == GL_VERTEX_SHADER){
    curr_shader = &m_vertex_id;
    std::cout << "Set vertex Shader." << std::endl;
  }
  
  if(shader_kind == GL_FRAGMENT_SHADER){
    curr_shader = &m_fragment_id;
    std::cout << "Set fragment Shader." << std::endl;
  }  

  *curr_shader = glCreateShader(shader_kind);
  glShaderSource(*curr_shader, src_string_count, &source, NULL);
  glCompileShader(*curr_shader);

  int success = 0;
  char info_log[512];
  glGetShaderiv(*curr_shader, GL_COMPILE_STATUS, &success);
  if(!success){
    glGetShaderInfoLog(*curr_shader, 512, NULL, info_log);
    std::cerr << "ERROR::SHADER::COMPILATION" << std::endl << info_log;
  } else{
    std::cout << "Successfully compiled shader" << std::endl;
  }
}

void Shader::link_program(){
  m_program_id = glCreateProgram();
  glAttachShader(m_program_id, m_vertex_id);
  glAttachShader(m_program_id, m_fragment_id);
  glLinkProgram(m_program_id);
  
  int success = 0;
  char info_log[512];
  glGetProgramiv(m_program_id, GL_LINK_STATUS, &success);  
  if(!success){
    glGetProgramInfoLog(m_program_id, 512, NULL, info_log);
    std::cout << "ERROR::SHADER::PROGRAM" << std::endl;
  }
  std::cout << "Compiled Program -\t" << m_program_id << std::endl;
}

void Shader::delete_shaders(){
  glDeleteShader(m_vertex_id);
  glDeleteShader(m_fragment_id);
  std::cout << "Deleted Shaders -\t" << "VERTEX/FRAGMENT" << std::endl;
}

void Shader::use() {
  glUseProgram(m_program_id);
}

void Shader::set_bool (const std::string &name, bool value) const {
  glUniform1i(glGetUniformLocation(m_program_id, name.c_str()), static_cast<int>(value));
}

void Shader::set_int(const std::string &name, int value) const{
  glUniform1i(glGetUniformLocation(m_program_id, name.c_str()), value);
}

void Shader::set_float(const std::string &name, float value) const{
   glUniform1f(glGetUniformLocation(m_program_id, name.c_str()), value);
}

void Shader::set_uniform_color(const char* uniform_name, float r, float g, float b, float a){
  int vertex_color_location = glGetUniformLocation(m_program_id, uniform_name);
  glUseProgram(m_program_id);
  glUniform4f(vertex_color_location, r, g, b, a);
}

} //namespace Prec
