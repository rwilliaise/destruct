
#ifndef DESTRUCT_MODEL_H
#define DESTRUCT_MODEL_H

#include <glad/gl.h>
#include <vector>
#include "Render.h"

namespace r {
  
  class Mesh {
  public:
    Mesh();
    ~Mesh();

    Mesh(const Mesh& mesh) = delete;
    Mesh(Mesh&& mesh) = default;
    Mesh& operator=(const Mesh& mesh) noexcept = delete;
    Mesh& operator=(Mesh&& mesh) noexcept = default;

    void loadIndices(std::vector<int> index);
    void loadVertexData(std::vector<float> vert);
    void loadUVData(std::vector<float> uv);

    inline void bind() const {
      glBindVertexArray(vao);

      for (auto attrib : attributes) {
        glEnableVertexAttribArray(attrib);
      }
    }

    inline void release() const {
      for (auto attrib : attributes) {
        glDisableVertexAttribArray(attrib);
      }

      glBindVertexArray(0);
    }

    inline GLsizei getVertexCount() { return vertexCount; }

  private:
    GLuint vao;
    GLuint vbo[3];
    GLsizei vertexCount = 0;

    std::vector<GLuint> attributes;

    template<typename T>
    void loadStaticData(const std::vector<T>& vec, int size, size_t attrib, GLenum type) const;
  };
} // r

#endif // DESTRUCT_MODEL_H
