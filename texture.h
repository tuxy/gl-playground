#ifndef TEXTURE_H
#define TEXTURE_H

#define STB_IMAGE_IMPLEMENTATION
#include <glad/glad.h>
#include <iostream>
#include "stb_image.h"

class Texture {
public:
  unsigned int ID;
  Texture(const char *texturePath, GLenum format) {
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data =
        stbi_load(texturePath, &width, &height, &nrChannels, 0);

    if (data) {
      glGenTextures(1, &ID);
      glBindTexture(GL_TEXTURE_2D, ID);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

      glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
                   GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
    } else {
      std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
  }

  void use() { glBindTexture(GL_TEXTURE_2D, ID); }
  void clean() { glDeleteTextures(1, &ID); }
};

#endif // !TEXTURE_H
