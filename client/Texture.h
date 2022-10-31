
#ifndef DESTRUCT_TEXTURE_H
#define DESTRUCT_TEXTURE_H

#include "Render.h"

#include <glad/gl.h>
#include <vector>

namespace r {
  
  /**
   * OpenGL texture management and PNG loading.
   */
  class Texture {
  public:
    Texture();
    ~Texture();

    Texture(const Texture&) = delete;
    Texture(Texture&&) = default;
    Texture& operator=(const Texture&) noexcept = delete;
    Texture& operator=(Texture&&) noexcept = default;
    
    /** Load image as a PNG from given bytes */
    void loadFromBytes(std::vector<uint8_t> bytes);

    inline void bind() const {
      glBindTexture(GL_TEXTURE_2D, id);
    }

    inline void release() const {
      glBindTexture(GL_TEXTURE_2D, 0);
    }

  private:
    GLuint id;
  };
}

#endif // DESTRUCT_TEXTURE_H

