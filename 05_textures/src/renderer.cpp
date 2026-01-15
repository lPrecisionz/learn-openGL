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
  delete[] m_shader;
  std::cout << "terminated and deleted shader" << std::endl;
}

void Renderer::process_input(){
  if(glfwGetKey(m_window, GLFW_KEY_ENTER) == GLFW_PRESS){
    glfwSetWindowShouldClose(m_window, true);
  }
}

void Renderer::init_vao(){
  glGenVertexArrays(1, &m_VAO);
  glBindVertexArray(m_VAO);
  std::cout << "Binded vertex array -\t" << m_VAO << std::endl;
}

void Renderer::init_vbo(const float *arr, const size_t arr_size, const size_t stride, const size_t offset){
  glGenBuffers(1, &m_VBO);
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  glBufferData(GL_ARRAY_BUFFER, arr_size, arr, GL_STATIC_DRAW);
  // pos attribute
  unsigned int location = 0;
  unsigned int attrib_count = 3;

  glVertexAttribPointer(location, attrib_count, GL_FLOAT, GL_FALSE, stride, (void*)0);
  glEnableVertexAttribArray(location);
  //color
  location = 1;
  glVertexAttribPointer(location, attrib_count, GL_FLOAT, GL_FALSE, stride, (void*)offset);
  glEnableVertexAttribArray(location); // honestly just remember to init VAO Before this
  
  attrib_count = 2;
  //texture
  size_t texture_offset = 6 * sizeof(float);
  location = 2;
  glVertexAttribPointer(location, attrib_count, GL_FLOAT, GL_FALSE, stride, (void*)texture_offset);
  glEnableVertexAttribArray(location);

  std::cout << "Finished binding buffer -\t" << m_VBO << std::endl;
}

void Renderer::init_ebo(const unsigned int *indices, const size_t arr_size, const size_t stride, const size_t offset){
  glGenBuffers(1, &m_EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, arr_size, indices, GL_STATIC_DRAW);
  
  // Coords
  unsigned int location=  0;
  glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, stride, (void*)offset);
  glEnableVertexAttribArray(location); // honestly just remember to init VAO Before this
  /* 
  // Color
  location = 1; 
  glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, stride, (void*)offset);
  glEnableVertexAttribArray(location);
  // Texture
  size_t texture_offset = offset * 2; 
  location = 2;  
  glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, stride, (void*)texture_offset);
  glEnableVertexAttribArray(location);
  */
  std::cout << "Finished binding buffer -\t" << m_EBO << std::endl;
}

void Renderer::init_shader(const char *vertex_src_path, const char *frag_src_path){
  m_shader = new Shader(vertex_src_path, frag_src_path);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height){
  glViewport(0,0,width,height);
}

} //namespace Prec
