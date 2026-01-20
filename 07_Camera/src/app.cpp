#include "../include/app.hpp"
namespace Precision{

constexpr unsigned int SCREEN_WIDTH  = 800; 
constexpr unsigned int SCREEN_HEIGHT = 600;
constexpr std::string  WINDOW_NAME   = "I love Clairo";

const char *vertex_path   = "./shaders/vertex.glsl";
const char *fragment_path = "./shaders/fragment.glsl";

void draw_n_cubes(const unsigned int n, Renderer &r);
void handle_input(glm::vec3 &camera_pos, glm::vec3 &camera_front, glm::vec3 &camera_up, Renderer &r, const float &delta_t);
void mouse_callback(GLFWwindow *window, double x_pos, double y_pos);
void handle_mouse_input(float &last_x, float &last_y, float &sensitivity);

bool first_mouse { true };
float last_x { 400.0f }, 
last_y { 300.0f },
yaw    { -90.0f }, 
pitch  {  0.0f  };

// view matrix
glm::vec3 camera_pos   = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 camera_front = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 camera_up    = glm::vec3(0.0f, 1.0f, 0.0f);


void App::run(){

  Renderer renderer {};
  renderer.init_window(WINDOW_NAME.c_str(), SCREEN_WIDTH, SCREEN_HEIGHT);
  glfwSetInputMode(renderer.m_window.get_window(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetCursorPosCallback(renderer.m_window.get_window(), mouse_callback);

  renderer.init_shader(vertex_path, fragment_path);
  renderer.init_vao();
  renderer.init_vbo(cube, sizeof(cube), GL_STATIC_DRAW, sizeof(float) * 5, cube_data);
  //renderer.init_ebo(square_indices, sizeof(square_indices), GL_STATIC_DRAW); 
  renderer.m_shader.gen_texture("./img/clairo.jpg", 0, "texture1");

  // 3D stuff
  // model matrix
  glm::mat4 model = glm::mat4(1.0f);

  model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0, 0.0, 0.0));

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
    delta_time = curr_frame - last_frame;
    last_frame = curr_frame;

    glClearColor(0.5f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //model = glm::rotate(model, glm::radians(0.5f), glm::vec3(1.0, 1.0, 1.0));
    //renderer.m_shader.set_mat4fv("model", model);
    handle_input(camera_pos, camera_front, camera_up, renderer, delta_time);
    view = glm::lookAt(camera_pos, camera_pos + camera_front, camera_up);
    renderer.m_shader.set_mat4fv("view", view);

    draw_n_cubes(10, renderer);
    //renderer.draw_vbo(GL_TRIANGLES, 0, 36);
    glfwSwapBuffers(renderer.m_window.get_window());
    glfwPollEvents();
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
  if(glfwGetKey(r.m_window.get_window(), GLFW_KEY_W) == GLFW_PRESS)
    camera_pos += speed * camera_front;
  if(glfwGetKey(r.m_window.get_window(), GLFW_KEY_S) == GLFW_PRESS)
    camera_pos -= speed * camera_front;
  if(glfwGetKey(r.m_window.get_window(), GLFW_KEY_D) == GLFW_PRESS)
    camera_pos -= glm::normalize(glm::cross(camera_up, camera_front)) * speed;
  if(glfwGetKey(r.m_window.get_window(), GLFW_KEY_A) == GLFW_PRESS)
    camera_pos += glm::normalize(glm::cross(camera_up, camera_front)) * speed;
}

void mouse_callback(GLFWwindow *window, double x_pos_in, double y_pos_in){
  float x_pos = static_cast<float>(x_pos_in);
  float y_pos = static_cast<float>(y_pos_in);
  
  if(first_mouse){
    last_x = x_pos; 
    last_y = y_pos; 
    first_mouse = false; 
  }  

  float x_offset = x_pos - last_x;
  float y_offset = last_y - y_pos; // reversed since we go from bottom to top
  last_x = x_pos; 
  last_y = y_pos;

  float sensitivity = 0.01f;
  x_offset *= sensitivity; 
  y_offset *= sensitivity; 

  yaw   += x_offset; 
  pitch += y_offset;

  if(pitch > 89.0f)
    pitch = 89.0f;
  if(pitch < -89.0f)
    pitch = -89.0f;

  glm::vec3 direction; 
  direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  direction.y = sin(glm::radians(pitch));
  direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
  camera_front = glm::normalize(direction);
}

}; // namespace Precision
