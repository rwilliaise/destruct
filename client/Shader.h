
#ifndef DESTRUCT_SHADER_H
#define DESTRUCT_SHADER_H

#include "Render.h"
#include <glad/gl.h>
#include <string>

namespace r {

  inline void unuse() {
    glUseProgram(0);
  }
  
  class Pipeline {
  public:
    Pipeline(): prog(glCreateProgram()) {};
    ~Pipeline() {
      glDeleteProgram(prog);
    }

    Pipeline(const Pipeline&) = delete;
    Pipeline(Pipeline&&) = default;
    Pipeline& operator=(const Pipeline&) noexcept = delete;
    Pipeline& operator=(Pipeline&&) noexcept = default;

    void compile(std::string vert, std::string frag); 
    void link() const;

    inline void bindAttrib(GLuint loc, std::string name) const {
      glBindAttribLocation(prog, loc, name.c_str());
    }

    inline void use() const {
      glUseProgram(prog);
    }

    inline GLint getUniform(std::string str) const {
      return glGetUniformLocation(prog, str.c_str());
    }

  private:
    GLuint prog;
    GLuint shaders[2];
  };
} // r

#endif // DESTRUCT_SHADER_H
