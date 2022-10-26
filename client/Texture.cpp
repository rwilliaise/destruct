
#include "Texture.h"
#include <glad/gl.h>
#include <png.h>

namespace r {
  
  Texture::Texture() {
    glGenTextures(1, &id);
  }

  Texture::~Texture() {
    glDeleteTextures(1, &id);
  }

  void Texture::loadFromBytes(std::vector<uint8_t> bytes) {
    png_image image;
    image.format = PNG_FORMAT_RGBA;

    png_image_begin_read_from_memory(&image, bytes.data(), bytes.size() * sizeof(char));

    auto width = image.width;
    auto height = image.height;

    uint8_t imageData[width][height];
    
    for (int i = 0; i < height; i++) {
      auto row = imageData[i];

      // png_read_row(&image, row, 0);
    }

    glBindTexture(GL_TEXTURE_2D, id);

    glBindTexture(GL_TEXTURE_2D, 0);
  }
} // r
