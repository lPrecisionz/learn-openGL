#include <../include/renderer.hpp>

const char *vertex_shader_source = "#version 330 core\n"
  "layout (location=0) in vec3 aPos;\n"
  "void main()\n"
  "{\n"
  " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
  "}\0";

const char *fragment_shader_source = "#version 330 core\n"
  "out vec4 FragColor;\n"
  "void main()\n"
  "{\n"
  "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
  "}\0";

const char *fragment_shader_source2 = "#version 330 core\n"
  "out vec4 FragColor;\n"
  "void main()\n"
  "{\n"
  "FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
  "}\0";
/*
float vertices[] = {
  0.5f,  0.5f, 0.0f,  // top right
  0.5f, -0.5f, 0.0f,  // bottom right
  -0.5f, -0.5f, 0.0f,  // bottom left
  -0.5f,  0.5f, 0.0f   // top left 
};
*/

float vertices_1[] = {
  -1.0f, 0.0f, 0.0f, // bottom-left
  -0.5f, 0.5f, 0.0f, // top
   0.0f, 0.0f, 0.0f, // bottom right
};

float vertices_2[] = {
   0.0f, 0.0f, 0.0f, 
   0.5f, 0.5f, 0.0f, 
   1.0f, 0.0f, 0.0f
};

unsigned int indices[] = {
  0, 1, 3, 
  1, 2, 3
};

int main(){
  Renderer renderer {};
  
  // Create vertex shader object
  unsigned int vertex_shader; 
  vertex_shader  = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
  glCompileShader(vertex_shader);

  // Check shader compilation status
  int  success {0};
  char info_log[512];
  glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);

  if(!success){
    glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info_log;
  } 

  // Create Fragment Shader
  unsigned int fragment_shader;
  fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
  glCompileShader(fragment_shader);

  // Check shader compilation status
  glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);

  if(!success){
    glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
    std::cout << "ERROR::SHADER::FRAGMENT1::COMPILATION_FAILED\n" << info_log;
  }

  unsigned int fragment_shader2; 
  fragment_shader2 = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader2, 1, &fragment_shader_source2, NULL);
  glCompileShader(fragment_shader2);
 
  glGetShaderiv(fragment_shader2, GL_COMPILE_STATUS, &success);

  if(!success){
    glGetShaderInfoLog(fragment_shader2, 512, NULL, info_log);
    std::cout << "ERROR::SHADER::FRAGMENT2::COMPILATION_FAILED\n" << info_log;
  }

  // Create object shader
  unsigned int shader_program, shader_program2; 
  shader_program = glCreateProgram();

  glAttachShader(shader_program, vertex_shader);
  glAttachShader(shader_program, fragment_shader);
  glLinkProgram(shader_program);

  glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
  if(!success){
    glGetProgramInfoLog(shader_program, 512, NULL, info_log);
    std::cout << "ERROR::SHADER::VERTEX::LINKING\n" << info_log;
  }

  shader_program2 = glCreateProgram();
  glAttachShader(shader_program2, vertex_shader);
  glAttachShader(shader_program2, fragment_shader2);
  glLinkProgram(shader_program2);

  glGetProgramiv(shader_program2, GL_LINK_STATUS, &success);
  if(!success){
    glGetProgramInfoLog(shader_program2, 512, NULL, info_log);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING\n" << info_log;
  }
  // delete shaders
  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);
  glDeleteShader(fragment_shader2);

  unsigned int VBO, VAO, EBO; 
  unsigned int VBO2, VAO2;

  glGenBuffers(1, &VBO);
  glGenBuffers(1, &VBO2);
  glGenBuffers(1, &EBO);

  glGenVertexArrays(1, &VAO);
  glGenVertexArrays(1, &VAO2);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_1), vertices_1, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(VAO2);
  glBindBuffer(GL_ARRAY_BUFFER, VBO2);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_2), vertices_2, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

  glEnableVertexAttribArray(0);
  glUseProgram(shader_program);

  while(!glfwWindowShouldClose(renderer.m_window)){
    renderer.process_input();
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    //draw object
    glUseProgram(shader_program);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    
    glUseProgram(shader_program2); 
    glBindVertexArray(VAO2);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glfwSwapBuffers(renderer.m_window);
    glfwPollEvents();
  }
  return 0;
}
