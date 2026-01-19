#include "../include/app.hpp"
namespace Precision{

constexpr unsigned int SCREEN_WIDTH  = 800; 
constexpr unsigned int SCREEN_HEIGHT = 600;
constexpr std::string  WINDOW_NAME   = "I love Clairo";

const char *vertex_path   = "./shaders/vertex.glsl";
const char *fragment_path = "./shaders/fragment.glsl";

void draw_n_cubes(const unsigned int n, Renderer &r);
void handle_input(glm::vec3 &camera_pos, glm::vec3 &camera_front, glm::vec3 &camera_up, Renderer &r, const float &delta_t);

void App::run(){
  Renderer renderer {};
  renderer.init_window(WINDOW_NAME.c_str(), SCREEN_WIDTH, SCREEN_HEIGHT);
  renderer.init_shader(vertex_path, fragment_path);
  renderer.init_vao();
  renderer.init_vbo(cube, sizeof(cube), GL_STATIC_DRAW, sizeof(float) * 5, cube_data);
  //renderer.init_ebo(square_indices, sizeof(square_indices), GL_STATIC_DRAW); 
  renderer.m_shader.gen_texture("./img/clairo.jpg", 0, "texture1");
  
  // 3D stuff
  // model matrix
  glm::mat4 model = glm::mat4(1.0f);

  model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0, 0.0, 0.0));

  // view matrix
  glm::vec3 camera_pos   = glm::vec3(0.0f, 0.0f, 3.0f);
  glm::vec3 camera_front = glm::vec3(0.0f, 0.0f, -1.0f);
  glm::vec3 camera_up    = glm::vec3(0.0f, 1.0f, 0.0f);

  glm::mat4 view = glm::mat4(1.0f);
  view = glm::lookAt(camera_pos, camera_pos + camera_front, camera_up);

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
  glEnable(GL_DEPTH_TEST);

  float cam_x {0.0}, 
        cam_z {3.0};
  float delta_time { 0 }, 
        last_frame { 0 };

  while(!glfwWindowShouldClose(renderer.m_window.get_window())){
    float curr_frame = glfwGetTime();
    glClearColor(0.5f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //model = glm::rotate(model, glm::radians(0.5f), glm::vec3(1.0, 1.0, 1.0));
    //renderer.m_shader.set_mat4fv("model", model);
    handle_input(camera_pos, camera_front, camera_up, renderer, delta_time);
    view = glm::lookAt(camera_pos, camera_pos + camera_front, camera_up);
    renderer.m_shader.set_mat4fv("view", view);

    draw_n_cubes(10, renderer);
    //renderer.draw_vbo(GL_TRIANGLES, 0, 36);
    glfwPollEvents();
    glfwSwapBuffers(renderer.m_window.get_window());
    
    delta_time = curr_frame - last_frame;
    last_frame = curr_frame;
  }
}

void draw_n_cubes(const unsigned int n, Renderer &r){
  for(int i = 0; i < n; ++i){
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, cubePositions[i]);
    float angle = 10.0f * i+1;
    model = glm::rotate(model, glm::radians((float)glfwGetTime() * angle), glm::vec3(1.0f, 0.3f, 0.5f));
    r.m_shader.set_mat4fv("model", model);
    r.draw_vbo(GL_TRIANGLES, 0, 36);
  }
}

void handle_input(glm::vec3 &camera_pos, glm::vec3 &camera_front, glm::vec3 &camera_up, Renderer &r, const float &delta_t){
  float speed = 2.5f * delta_t;
  if(glfwGetKey(r.m_window.get_window(), GLFW_KEY_W))
    camera_pos += speed * camera_front;
  if(glfwGetKey(r.m_window.get_window(), GLFW_KEY_S))
    camera_pos -= speed * camera_front;
  if(glfwGetKey(r.m_window.get_window(), GLFW_KEY_D))
    camera_pos -= glm::normalize(glm::cross(camera_up, camera_front)) * speed;
  if(glfwGetKey(r.m_window.get_window(), GLFW_KEY_A))
    camera_pos += glm::normalize(glm::cross(camera_up, camera_front)) * speed;
}


}; // namespace Precision
