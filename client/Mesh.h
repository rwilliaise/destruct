
#ifndef DESTRUCT_MODEL_H
#define DESTRUCT_MODEL_H

#include "Render.h"

#include <glad/gl.h>
#include <glm/fwd.hpp>
#include <vector>

namespace r {
  
  /**
   * Vertex buffer management class. Does not necessarily represent the mesh
   * data of one sh::Entity - thus, it is move-only.
   */
  class Mesh {
  public:
    Mesh();
    ~Mesh();

    Mesh(const Mesh& mesh) = delete;
    Mesh(Mesh&& mesh) = default;
    Mesh& operator=(const Mesh& mesh) noexcept = delete;
    Mesh& operator=(Mesh&& mesh) noexcept = default;

    /** Loads index buffer (not an attribute). */
    void loadIndices(std::vector<int> index);

    /** Loads vertex data as a vertex buffer attribute. */
    void loadVertexData(std::vector<glm::vec3> vert);
    /** Loads normal data as a vertex buffer attribute. */
    void loadNormalData(std::vector<glm::vec3> norm);
    /** Loads UV data as a vertex buffer attribute. */
    void loadUVData(std::vector<glm::vec2> uv);

    /**
     * Loads vertex, normal, and UV data from given memory using OBJ Wavefront
     * format.
     */
    void loadFromMemory(std::vector<char> bytes);

    /** 
     * Draws mesh using glDrawArrays or glDrawElements based on loaded buffers.
     * TODO: mesh render batching, deprecation of this function
     */
    void draw() const;

    /** Binds vertex buffer and then enables constituent attributes. */
    inline void bind() const {
      glBindVertexArray(vao);

      for (auto attrib : attributes) {
        glEnableVertexAttribArray(attrib);
      }
    }

    /** Disables constituent attributes, then unbinds vertex buffer. */
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

    /** Loaded attributes. */
    std::vector<GLuint> attributes;

    /**
     * Loads GL_STATIC_DRAW data as an attribute. Generalized version of the
     * load- functions above.
     */
    template<typename T>
    void loadStaticData(const std::vector<T> &vec, int size, size_t attrib, GLenum type) const;
  };
} // r

#endif // DESTRUCT_MODEL_H
