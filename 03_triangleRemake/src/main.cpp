#include "../include/renderer.hpp"

int main(){
    Prec::Renderer renderer;
    renderer.init("my window");
    
    while (!glfwWindowShouldClose(renderer.m_window)){
      renderer.process_input();
      glfwSwapBuffers(renderer.m_window);
      glfwPollEvents();
    }

    return 0;
}
