
#include "Texture.h"

#include <glad/gl.h>
#include <iostream>
#include <png.h>

namespace r {
  
  Texture::Texture() {
    glGenTextures(1, &id);
  }

  Texture::~Texture() {
    glDeleteTextures(1, &id);
  }

  void Texture::loadFromBytes(std::vector<uint8_t> bytes) {
    png_image image{ .opaque = nullptr, .version = PNG_IMAGE_VERSION, };
    bool success = png_image_begin_read_from_memory(&image, bytes.data(), bytes.size() * sizeof(char));

    if (!success) { 
      std::cerr << "libpng error: " << image.message << std::endl;
      return;
    }

    image.format = PNG_FORMAT_RGB;
    
    uint8_t buff[PNG_IMAGE_SIZE(image)];
    success = png_image_finish_read(&image, nullptr, buff, 0, nullptr);

    if (!success) {
      png_image_free(&image);
      return;
    }

    bind();
    std::cout << image.width << " x " << image.height << std::endl;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.width, image.height, 0, GL_RGB, GL_UNSIGNED_BYTE, buff);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    release();
  }
} // r
