#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/quaternion_geometric.hpp>
#include <glm/fwd.hpp>
#include <glm/geometric.hpp>
#include <glm/trigonometric.hpp>
#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <array>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "shader.h"
#include "geometry.h"
#include "texture.h"
#include "ui.h"

const int HEIGHT = 1080;
const int WIDTH = 1920;

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

  GLFWwindow *window =
      glfwCreateWindow(WIDTH, HEIGHT, "Learn OpenGL", NULL, NULL);
  if (window == NULL) {
    cout << "Failed to create GLFW Window" << endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    cout << "Failed to intialise GLAD" << endl;
    return -1;
  }

  glEnable(GL_DEPTH_TEST);

  ProgramParams params = ProgramParams{0.0f, 0.0f, -3.0f};
  TestController controller = TestController{params};
  controller.init(window);

  vector<glm::vec3> cubePositions = {
      glm::vec3(0.0f, 0.0f, 0.0f),    glm::vec3(2.0f, 5.0f, -15.0f),
      glm::vec3(-1.5f, -2.2f, -2.5f), glm::vec3(-3.8f, -2.0f, -12.3f),
      glm::vec3(2.4f, -0.4f, -3.5f),  glm::vec3(-1.7f, 3.0f, -7.5f),
      glm::vec3(1.3f, -2.0f, -2.5f),  glm::vec3(1.5f, 2.0f, -2.5f),
      glm::vec3(1.5f, 0.2f, -1.5f),   glm::vec3(-1.3f, 1.0f, -1.5f)};

  vector<float> vertices_cube = {
      -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 0.0f,
      0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
      -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

      -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
      -0.5f, 0.5f,  0.5f,  0.0f, 1.0f, -0.5f, -0.5f, 0.5f,  0.0f, 0.0f,

      -0.5f, 0.5f,  0.5f,  1.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f,
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
      -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  0.5f,  1.0f, 0.0f,

      0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
      0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 0.0f, 1.0f,
      0.5f,  -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 1.0f,
      0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
      -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

      -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
      -0.5f, 0.5f,  0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f};

  Shader shader = Shader("./shaders/coordinate-systems.vs",
                         "./shaders/coordinate-systems.fs");

  Texture texture1 = Texture("./textures/awesomeface.png", GL_RGBA);
  Texture texture2 = Texture("./textures/container.jpg", GL_RGB);

  glm::mat4 proj = glm::mat4(1.0f); // View properties (fov, clip space)
  proj = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT,
                          0.1f, 1000.0f);
  shader.use();
  shader.setInt("texture1", 0);
  shader.setInt("texture2", 1);

  // cube (Geometry class doesn't have non-ebo logic yet)
  unsigned int vao, vbo;
  glGenBuffers(1, &vbo);
  glGenVertexArrays(1, &vao);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBindVertexArray(vao);

  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices_cube.size(),
               vertices_cube.data(), GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  // End cube

  while (!glfwWindowShouldClose(window)) {
    // input
    process_input(window);

    controller.create_frame();

    // render & draw
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 cameraInverseDirection = glm::normalize(cameraPos - cameraTarget);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 cameraRight =
        glm::normalize(glm::cross(up, cameraInverseDirection));

    glm::vec3 cameraUp = glm::cross(cameraInverseDirection, cameraRight);

    // Remember that: V_clip = M_proj * M_view * M_model * V_local
    // glm::mat4 model = glm::mat4(1.0f); // Position in global space
    glm::mat4 view = glm::mat4(1.0f); // View location (camera location)
    float camX = sin(glfwGetTime()) * 10.0f;
    float camZ = cos(glfwGetTime()) * 10.0f;
    view = glm::lookAt(glm::vec3(camX, 0.0f, camZ), cameraTarget, cameraUp);
    view = glm::translate(view, glm::vec3(controller.params.camX,
                                          controller.params.camY,
                                          controller.params.camZ));
    view = glm::rotate(view, glm::radians(controller.params.camRotX),
                       glm::vec3(1.0f, 0.0f, 0.0f));
    view = glm::rotate(view, glm::radians(controller.params.camRotY),
                       glm::vec3(0.0f, 1.0f, 0.0f));
    view = glm::rotate(view, glm::radians(controller.params.camRotZ),
                       glm::vec3(0.0f, 0.0f, 1.0f));

    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(0.0f, 0.0f, -0.25f));

    // set transformation
    shader.setMatrix("transform", glm::value_ptr(transform));
    shader.setMatrix("view", glm::value_ptr(view));
    shader.setMatrix("proj", glm::value_ptr(proj));

    glActiveTexture(GL_TEXTURE0);
    texture1.use();
    glActiveTexture(GL_TEXTURE1);
    texture2.use();

    shader.setInt("texture1", 0);
    shader.setInt("texture2", 1);

    glBindVertexArray(vao);
    for (int i = 0; i < cubePositions.size(); i++) {
      glm::mat4 model = glm::mat4(1.0f);
      float angle = 20.0f * i;
      model = glm::translate(model, cubePositions.at(i));
      model =
          glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
      shader.setMatrix("model", glm::value_ptr(model));
      shader.use();
      glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    controller.render();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwTerminate();
  return 0;
}

void process_input(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}
