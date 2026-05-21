#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <glad/glad.h>
#include <vector>
#include <iostream>

struct Attribute {              // Float by default
  std::vector<size_t> vec_size; // Size of stored vector, by each section
  size_t attribute_count; // Number of stored items (position, normal, color,
                          // etc...)
};

// This structure enforces the creation and management of single states
class Geometry {
public:
  unsigned int vao;       // VAO config state
  unsigned int positions; // VBO vertices
  unsigned int indices;   // EBO indices
  uint32_t indexCount;
  uint32_t vertexCount;

  Geometry(std::vector<float> vertices_arr, std::vector<int> indices_arr,
           Attribute attribute) {
    indexCount = indices_arr.size();
    vertexCount = vertices_arr.size(); // unused

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

    if (attribute.vec_size.size() != attribute.attribute_count) {
      std::cout << "Geometry input mismatch!" << std::endl;
    }

    size_t stride = 0; // Take the sum of vec_size and multiply by sizeof(float)
                       // for stride (each "section" size)
    for (size_t i : attribute.vec_size)
      stride += i;
    stride *= sizeof(float);

    size_t offset = 0;
    for (size_t i = 0; i < attribute.attribute_count; i++) {
      glVertexAttribPointer(i, attribute.vec_size.at(i), GL_FLOAT, GL_FALSE,
                            stride, (void *)offset);
      glEnableVertexAttribArray(i);
      offset += attribute.vec_size.at(i) * sizeof(float);
    }
  }

  void draw() {
    glBindVertexArray(vao);
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
