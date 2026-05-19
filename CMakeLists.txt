cmake_minimum_required(VERSION 3.20)
project(gl-playground)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_subdirectory(external/glad)

add_executable(gl-playground main.cpp)
target_link_libraries(gl-playground PRIVATE OpenGL::GL glad glfw)
