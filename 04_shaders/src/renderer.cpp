#include "../include/renderer.hpp"

namespace Prec{

void Renderer::init(const char* window_name){
  glfwInit();
  m_window_name = window_name;
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, LOCAL_VERSION);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, LOCAL_VERSION);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  m_window = glfwCreateWindow(base_width, base_height,m_window_name, NULL, NULL);

  if(m_window == nullptr){
    throw std::runtime_error("Failed to initialize window.");
    glfwTerminate();
    return;
  }

  glfwMakeContextCurrent(m_window);
  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
    glfwTerminate();
    throw std::runtime_error("Failed to initialize GLAD.");
  }
  glViewport(0,0,base_width,base_height);
  glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
}

Renderer::~Renderer(){
  glfwTerminate();
}

void Renderer::process_input(){
  if(glfwGetKey(m_window, GLFW_KEY_ENTER) == GLFW_PRESS){
    glfwSetWindowShouldClose(m_window, true);
  }
}

void Renderer::init_shader(const int shader_kind, const char* src_path){
  unsigned int *curr_shader = nullptr;
  unsigned int src_string_count = 1;

  if(shader_kind == GL_VERTEX_SHADER){
    curr_shader = &m_vertex_shader;
    std::cout << "Set vertex Shader." << std::endl;
  }
  
  if(shader_kind == GL_FRAGMENT_SHADER){
    curr_shader = &m_fragment_shader;
    std::cout << "Set fragment Shader." << std::endl;
  }

  *curr_shader = glCreateShader(shader_kind);
  glShaderSource(*curr_shader, src_string_count, &src_path, NULL);
  glCompileShader(*curr_shader);
  
  int success = 0;
  char info_log[512];
  glGetShaderiv(*curr_shader, GL_COMPILE_STATUS, &success);
  if(!success){
    glGetShaderInfoLog(*curr_shader, 512, NULL, info_log);
    std::cerr << "ERROR::SHADER::COMPILATION" << std::endl << info_log;
  }

  std::cout << "Compiled shader -\t" << *curr_shader << std::endl;
}

void Renderer::link_program(){
  m_shader_program = glCreateProgram();
  glAttachShader(m_shader_program, m_vertex_shader);
  glAttachShader(m_shader_program, m_fragment_shader);
  glLinkProgram(m_shader_program);
  
  int success = 0;
  char info_log[512];
  glGetProgramiv(m_shader_program, GL_LINK_STATUS, &success);  
  if(!success){
    glGetProgramInfoLog(m_shader_program, 512, NULL, info_log);
    std::cout << "ERROR::SHADER::PROGRAM" << std::endl;
  }

  delete_shaders();
  std::cout << "Compiled Program -\t" << m_shader_program << std::endl;
}

void Renderer::delete_shaders(){
  glDeleteShader(m_vertex_shader);
  glDeleteShader(m_fragment_shader);
  std::cout << "Deleted Shaders -\t" << "pedrin" << std::endl;
}

void Renderer::init_vao(){
  glGenVertexArrays(1, &m_VAO);
  glBindVertexArray(m_VAO);
  std::cout << "Binded vertex array -\t" << m_VAO << std::endl;
}

void Renderer::init_vbo(const float *arr, const size_t arr_size, const size_t stride){
  glGenBuffers(1, &m_VBO);
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  glBufferData(GL_ARRAY_BUFFER, arr_size, arr, GL_STATIC_DRAW);
  //not sure what first arg is, second I figure it's vertex count
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
  glEnableVertexAttribArray(0); // honestly just remember to init VAO Before this
  
  std::cout << "Finished binding buffer -\t" << m_VBO << std::endl;
}

void Renderer::init_ebo(const unsigned int *indices, const size_t arr_size, const size_t stride){
  glGenBuffers(1, &m_EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, arr_size, indices, GL_STATIC_DRAW);
  //not sure what first arg is, second I figure it's vertex count
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
  glEnableVertexAttribArray(0); // honestly just remember to init VAO Before this
  
  std::cout << "Finished binding buffer -\t" << m_EBO << std::endl;
}

void Renderer::set_uniform_color(const char* uniform_name, float r, float g, float b, float a){
  int vertex_color_location = glGetUniformLocation(m_shader_program, uniform_name);
  glUseProgram(m_shader_program);
  glUniform4f(vertex_color_location, r, g, b, a);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height){
  glViewport(0,0,width,height);
}

} //namespace Prec
