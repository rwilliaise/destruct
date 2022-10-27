
#include "Mesh.h"
#include <glad/gl.h>

namespace r {
 
  Mesh::Mesh() {
    glGenVertexArrays(1, &vao);
    glGenBuffers(3, vbo);
  }

  Mesh::~Mesh() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(3, vbo);
  }

  void Mesh::loadIndices(std::vector<int> index) {
    vertexCount = index.size();

    bind();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index.size() * sizeof(float), index.data(), GL_STATIC_DRAW);
    release();
  }

  template<typename T>
  void Mesh::loadStaticData(const std::vector<T>& vec, int size, size_t vboIdx, GLenum type) const {
    bind();
    glBindBuffer(GL_ARRAY_BUFFER, vbo[vboIdx]);
    glBufferData(GL_ARRAY_BUFFER, vec.size() * sizeof(T), vec.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(vboIdx, size, type, GL_FALSE, 0, nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    release();
  }

  void Mesh::loadVertexData(std::vector<float> vert) {
    attributes.emplace_back(0);
    loadStaticData(vert, 3, 0, GL_FLOAT);
  }

  void Mesh::loadUVData(std::vector<float> uv) {
    attributes.emplace_back(1);
    loadStaticData(uv, 2, 1, GL_FLOAT);
  }
} // r


