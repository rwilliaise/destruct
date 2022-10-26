
#ifndef DESTRUCT_TEXTURE_H
#define DESTRUCT_TEXTURE_H

#include "Render.h"

#include <vector>

namespace r {
  
  class Texture {
  public:
    Texture();
    ~Texture();

    Texture(const Texture&) = delete;
    Texture(Texture&&) = default;
    Texture& operator=(const Texture&) noexcept = delete;
    Texture& operator=(Texture&&) noexcept = default;
    
    void loadFromBytes(std::vector<uint8_t> bytes);

  private:
    GLuint id;
  };
}

#endif // DESTRUCT_TEXTURE_H

