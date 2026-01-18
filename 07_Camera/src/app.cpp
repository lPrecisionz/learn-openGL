#include "../include/app.hpp"
namespace Precision{

constexpr unsigned int SCREEN_WIDTH  = 800; 
constexpr unsigned int SCREEN_HEIGHT = 600;
constexpr std::string  WINDOW_NAME   = "I love Clairo";

const char *vertex_path   = "./shaders/vertex.glsl";
const char *fragment_path = "./shaders/fragment.glsl";

void App::run(){
  Renderer renderer {};
  renderer.init_window(WINDOW_NAME.c_str(), SCREEN_WIDTH, SCREEN_HEIGHT);
  renderer.init_shader(vertex_path, fragment_path);
  renderer.init_vao();
  renderer.init_vbo(cube, sizeof(cube), GL_STATIC_DRAW, sizeof(float) * 6, cube_data);
  //renderer.init_ebo(square_indices, sizeof(square_indices), GL_STATIC_DRAW); 
  renderer.m_shader.gen_texture("./img/clairo.jpg", 0, "texture1");
  
  // 3D stuff
  // model matrix
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0, 0.0, 0.0));

  // view matrix
  glm::mat4 view = glm::mat4(1.0f);
  view = glm::translate(view, glm::vec3(0.0, 0.0, -3.0));

  // perspective matrix
  float fov = glm::radians(45.0f), 
        ratio = 800.0 / 600.0, 
        near_distance = 0.1f, 
        far_distance = 100.0f;
  glm::mat4 projection = glm::mat4(1.0f);
  projection = glm::perspective(fov, ratio , near_distance, far_distance);

  renderer.m_shader.set_mat4fv("model", model);
  renderer.m_shader.set_mat4fv("view", view);
  renderer.m_shader.set_mat4fv("projection", projection);

  while(!glfwWindowShouldClose(renderer.m_window.get_window())){
    glClearColor(0.5f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    renderer.draw_vbo(GL_TRIANGLES, 0, 36);
    glfwPollEvents();
    glfwSwapBuffers(renderer.m_window.get_window());
  }
}

}; // namespace Precision
