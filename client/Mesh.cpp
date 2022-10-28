
#include "Mesh.h"
#include "Util.h"

#include <cstdlib>
#include <cstring>
#include <exception>
#include <glad/gl.h>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/gtx/string_cast.hpp>
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

  void Mesh::loadVertexData(std::vector<glm::vec3> vert) {
    attributes.emplace_back(0);
    loadStaticData(vert, 3, 0, GL_FLOAT);
  }

  void Mesh::loadUVData(std::vector<glm::vec2> uv) {
    attributes.emplace_back(1);
    loadStaticData(uv, 2, 1, GL_FLOAT);
  }

  void Mesh::loadNormalData(std::vector<glm::vec3> norm) {
    attributes.emplace_back(2);
    loadStaticData(norm, 3, 2, GL_FLOAT);
  }

  void Mesh::loadFromMemory(std::vector<char> bytes) {
    std::stringstream stream = std::stringstream(std::string(bytes.data(), bytes.size()));
    std::string line;

    std::vector<int> indices;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> uvs;

    std::vector<int> elements;

    while (std::getline(stream, line)) {
      if (line.compare(0, 2, "v ") == 0) {
        glm::vec3 vert;
        std::istringstream stream(line.substr(2));

        stream >> vert.x; stream >> vert.y; stream >> vert.z;

        vertices.push_back(vert);
      } else if (line.compare(0, 3, "vn ") == 0) {
        glm::vec3 norm;
        std::istringstream stream(line.substr(3));

        stream >> norm.x; stream >> norm.y; stream >> norm.z;

        normals.push_back(norm);
      } else if (line.compare(0, 3, "vt ") == 0) {
        glm::vec2 uv;
        std::istringstream stream(line.substr(3));

        stream >> uv.x; stream >> uv.y;
        uv.x = 1 - uv.x;
        uv.y = 1 - uv.y;

        uvs.push_back(uv);
      } else if (line.compare(0, 2, "f ") == 0) {
        std::istringstream stream(line.substr(2));
        
        for (int i = 0; i < 3; i++) {
          int vIdx, uvIdx, nIdx;
          stream >> vIdx;
          stream.ignore();
          stream >> uvIdx;
          stream.ignore();
          stream >> nIdx;

          vIdx--; uvIdx--; nIdx--;

          elements.push_back(vIdx);
          elements.push_back(uvIdx);
          elements.push_back(nIdx);
        }
      }
    }

    std::cout << "DEBUG: vertices size: " << vertices.size() << std::endl;
    std::vector<glm::vec2> uvOut(vertices.size());
    std::vector<glm::vec3> normalOut(vertices.size());
    for (int i = 0; i < elements.size(); i += 3) { 
      GLuint vIdx = elements[i];
      GLuint uvIdx = elements[i + 1];
      GLuint nIdx = elements[i + 2];
      std::cout << "DEBUG: vIdx = " << vIdx << std::endl;
      
      indices.push_back(vIdx);
      std::cout << "DEBUG: loaded index" << std::endl;
      uvOut[vIdx] = uvs[uvIdx];
      std::cout << "DEBUG: loaded uv" << std::endl;
      normalOut[vIdx] = normals[nIdx];
      std::cout << "DEBUG: loaded normals" << std::endl;
    }
    
    loadIndices(indices);
    loadVertexData(vertices);
    loadUVData(uvOut);
    loadNormalData(normalOut);
  }
} // r


