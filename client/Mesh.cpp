
#include "Mesh.h"

#include <cstdlib>
#include <cstring>
#include <exception>
#include <glad/gl.h>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <vector>

namespace r {
 
  Mesh::Mesh() {
    glGenVertexArrays(1, &vao);
    glGenBuffers(4, vbo);
  }

  Mesh::~Mesh() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(4, vbo);
  }

  void Mesh::loadIndices(std::vector<int> index) {
    vertexCount = index.size();

    bind();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[3]);
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

  void Mesh::loadNormalData(std::vector<float> norm) {
    attributes.emplace_back(2);
    loadStaticData(norm, 3, 2, GL_FLOAT);
  }

  void Mesh::loadFromMemory(std::vector<char> bytes) {
    std::stringstream stream = std::stringstream(std::string(bytes.data(), bytes.size()));
    std::string line;
    std::vector<glm::vec3> verts;
    std::vector<glm::vec3> norm;
    std::vector<glm::vec2> uv;

    std::vector<int> indices;
    std::vector<float> vertOut;
    std::vector<float> normOut;
    std::vector<float> uvOut;

    float tmp[3] = { 0, 0, 0 };
    int tmpIdx[3] = { 0, 0, 0 };
    char *tmpPtr;

    bool fMode = false;
    int vertIdx, uvIdx, normIdx;
    glm::vec3 currentVertex, currentNormal;
    glm::vec2 currentUV;

    while (std::getline(stream, line, '\n')) {
      if (!line.compare(0, 2, "v ")) {
        if (fMode) { continue; }
        tmp[0] = std::strtof((char*) &line.c_str()[2], &tmpPtr);
        tmp[1] = std::strtof(tmpPtr, &tmpPtr);
        tmp[2] = std::strtof(tmpPtr, nullptr);
        verts.push_back(glm::vec3(tmp[0], tmp[1], tmp[2]));
      } else if (!line.compare(0, 3, "vt ")) {
        if (fMode) { continue; }
        tmp[0] = std::strtof((char*) &line.c_str()[3], &tmpPtr);
        tmp[1] = std::strtof(tmpPtr, nullptr);
        uv.push_back(glm::vec2(tmp[0], tmp[1]));
      } else if (!line.compare(0, 3, "vn ")) {
        if (fMode) { continue; }
        tmp[0] = std::strtof((char*) &line.c_str()[3], &tmpPtr);
        tmp[1] = std::strtof(tmpPtr, &tmpPtr);
        tmp[2] = std::strtof(tmpPtr, nullptr);
        norm.push_back(glm::vec3(tmp[0], tmp[1], tmp[2]));
      } else if (!line.compare(0, 2, "f ")) {
        if (!fMode) {
          fMode = true;
          std::cout << "DEBUG: reached fmode" << std::endl;
          vertOut.resize(verts.size() * 3);
          normOut.resize(verts.size() * 3);
          uvOut.resize(verts.size() * 2);
        }

        tmpPtr = (char*) &line.c_str()[2];
        // each vertex
        for (int i = 0; i < 3; i++) {
          std::cout << "DEBUG: vertex ptr, str: " << tmpPtr << std::endl;
          tmpIdx[0] = std::strtol(tmpPtr, &tmpPtr, 10);

          tmpIdx[1] = std::strtol(&tmpPtr[1], &tmpPtr, 10);
          tmpIdx[2] = std::strtol(&tmpPtr[1], &tmpPtr, 10);
          vertIdx = tmpIdx[0] - 1;
          uvIdx = tmpIdx[1] - 1;
          normIdx = tmpIdx[2] - 1;

          std::cout << "DEBUG: reached vertex " << vertIdx << std::endl;
          
          for (auto index : indices) {
            if (vertIdx == index) {
              std::cout << "DEBUG: dupe index " << index << ", ignoring" << std::endl;
              continue;
            }
          }
          indices.push_back(vertIdx);
          std::cout << "DEBUG: loaded index" << std::endl;

          currentVertex = verts[vertIdx];
          currentUV = uv[uvIdx];
          currentNormal = norm[normIdx];

          vertOut[vertIdx * 3] = currentVertex.x;
          vertOut[vertIdx * 3 + 1] = currentVertex.y;
          vertOut[vertIdx * 3 + 2] = currentVertex.z;
          std::cout << "DEBUG: loaded vertices" << std::endl;
          uvOut[uvIdx * 2] = currentUV.x;
          uvOut[uvIdx * 2 + 1] = currentUV.y;
          std::cout << "DEBUG: loaded uv" << std::endl;
          normOut[normIdx * 3] = currentNormal.x;
          normOut[normIdx * 3 + 1] = currentNormal.y;
          normOut[normIdx * 3 + 2] = currentNormal.z;
          std::cout << "DEBUG: loaded normal" << std::endl;
        }
      }
    }

    std::cout << "DEBUG: reached load: " << verts.size() << " vertices" << std::endl;

    loadIndices(indices);
    loadVertexData(vertOut);
    loadUVData(uvOut);
    loadNormalData(normOut);
  }
} // r


