#include <cstddef>
#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <array>
#include <vector>

#include "shader.h"
#include "geometry.h"

using namespace std;

struct Triangle {
  unsigned int shaderProgram;
  unsigned int shaderProgram2;
  array<unsigned int, 2> VBO;
  array<unsigned int, 2> VAO;
};

struct Polygon {
  unsigned int shaderProgram;
  unsigned int EBO;
  unsigned int VBO;
  unsigned int VAO;
};

void process_input(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
Triangle create_triangle();
Polygon create_polygon(bool wireframe);

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window = glfwCreateWindow(800, 600, "Learn OpenGL", NULL, NULL);
  if (window == NULL) {
    cout << "Failed to create GLFW Window" << endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    cout << "Failed to intialise GLAD" << endl;
    return -1;
  }

  vector<float> vertices = {
      -0.5f, -0.5f, 0.0f, // bottom left
      -0.5f, 0.5f,  0.0f, // top left
      0.5f,  0.5f,  0.0f, // top right
      0.5f,  -0.5f, 0.0f, // bottom right
  };

  vector<int> indices{
      0, 1, 2, // first
      1, 2, 3, // second
  };

  Shader shader = Shader("./shaders/basic.vs", "./shaders/basic.fs");
  Geometry square = Geometry(vertices, indices);

  while (!glfwWindowShouldClose(window)) {
    // input
    process_input(window);

    // render & draw
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shader.use();
    square.draw();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  square.clean();

  glfwTerminate();
  return 0;
}

void test() {
  float vertices[] = {
      -0.5f, -0.5f, 0.0f, // bottom left
      -0.5f, 0.5f,  0.0f, // top left
      0.5f,  0.5f,  0.0f, // top right
      0.5f,  -0.5f, 0.0f, // bottom right
  };

  vector<float> indices{
      0, 1, 2, // first
      1, 2, 3, // second
  };
}

// // First triangle
// glBindVertexArray(VAO[0]);
// glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
// glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void
// *)0); glEnableVertexAttribArray(0);
//
// // Second triangle
// glBindVertexArray(VAO[1]);
// glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
// glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void
// *)0); glEnableVertexAttribArray(0);
//
void process_input(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}
