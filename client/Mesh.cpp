
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

  void Mesh::loadVertexData(std::vector<float> vert) {
    vertexCount = vert.size() / 3;

    attributes.push_back(0);
    bind();
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, vert.size() * sizeof(float), vert.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

} // r


