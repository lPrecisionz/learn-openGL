#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define LOCAL_VERSION 3
#define WIDTH  800
#define HEIGHT 600
#define WINDOW_NAME "LearnOpenGL"

void framebuffer_size_callback(GLFWwindow *window, int width, int height){
  glViewport(0,0, width, height);
}

void process_input(GLFWwindow *window){
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

int main(){
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, LOCAL_VERSION);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, LOCAL_VERSION);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, WINDOW_NAME, NULL, NULL);
  if(window==NULL){
    std::cout << "Failed to create GLFW window." << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  glViewport(0, 0, WIDTH, HEIGHT);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  while(!glfwWindowShouldClose(window)){
    process_input(window);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
