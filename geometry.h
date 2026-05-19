#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <glad/glad.h>
#include <vector>
#include <iostream>

// This structure enforces the creation and management of single states
class Geometry {
public:
  unsigned int vao;       // VAO config state
  unsigned int positions; // VBO vertices
  unsigned int indices;   // EBO indices
  uint32_t indexCount;
  uint32_t vertexCount;

  Geometry(std::vector<float> vertices_arr, std::vector<int> indices_arr) {

    indexCount = indices_arr.size();
    vertexCount = vertices_arr.size();

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &positions);
    glGenBuffers(1, &indices);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, positions); // vbo
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices_arr.size(),
                 vertices_arr.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices); // ebo
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices_arr.size(),
                 indices_arr.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);
  }

  void draw() {
    // glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
  }

  void clean() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &positions);
    glDeleteBuffers(1, &indices);
  }

  // implement:
  // - setter to update items
};

#endif
