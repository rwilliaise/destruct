
#ifndef DESTRUCT_MODEL_H
#define DESTRUCT_MODEL_H

#include "Render.h"

#include <glad/gl.h>
#include <glm/fwd.hpp>
#include <vector>

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
    void loadVertexData(std::vector<glm::vec3> vert);
    void loadNormalData(std::vector<glm::vec3> norm);
    void loadUVData(std::vector<glm::vec2> uv);

    void loadFromMemory(std::vector<char> bytes);

    void draw() const;

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
    GLuint vao = 0;
    GLuint vbo[4];
    GLsizei vertexCount = 0;

    bool useIndexBuffer = false;

    std::vector<GLuint> attributes;

    template<typename T>
    void loadStaticData(const std::vector<T>& vec, int size, size_t attrib, GLenum type) const;
  };
} // r

#endif // DESTRUCT_MODEL_H
