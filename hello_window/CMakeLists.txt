cmake_minimum_required(VERSION 3.16)
project(hello_window LANGUAGES CXX)

set(CMAKE_CXX STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
  hello_window src/main.cpp
)

#OpenGL target (provides OpenGL::GL)
find_package(OpenGL REQUIRED) # :contentReference]oaicite"2]{index=2}"

#GLFW (preferred)
find_package(glfw3 3.3 QUIET)

if(glfw3_FOUND)
  target_link_libraries(hello_window PRIVATE glfw OpenGL::GL)
else()
  # Fallback : pkg-config
  find_package(PkgConfig REQUIRED)
  pkg_check_modules(GLFW REQUIRED glfw3)
  target_include_directories(hello_window PRIVATE ${GLFW_INCLUDE_DIRS})
  target_link_libraries(hello_window PRIVATE ${GLFW_LIBRARIES} OpenGL::GL)
  target_link_directories(hello_glfw PRIVATE ${GLFW_LIBRARY_DIRS})
endif()
