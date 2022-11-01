
#include "Shader.h"
#include "glad/gl.h"
#include <fstream>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <sstream>
#include <vector>

static GLuint compileShader(GLenum type, std::string source) {
	GLuint out = glCreateShader(type);

	const char *cSource = source.c_str();
	glShaderSource(out, 1, &cSource, nullptr);
	glCompileShader(out);
	
	int success;
	char log[512];
	glGetShaderiv(out, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE) {
		glGetShaderInfoLog(out, 512, nullptr, log);
		std::cout << "Failed to compile shader\n" << log << std::endl;
		return 0;
	}

	return out;
}

namespace r {

	void Pipeline::transform(sh::Entity &ent) {
		glm::mat4 mat = ent.toModelMatrix();
		GLint trans = getUniform("transformation");
		glUniformMatrix4fv(trans, 1, GL_FALSE, glm::value_ptr(mat));
	}
	
	void Pipeline::compile(std::string vert, std::string frag) {
		GLuint vertShader = compileShader(GL_VERTEX_SHADER, vert);
		GLuint fragShader = compileShader(GL_FRAGMENT_SHADER, frag);

		glAttachShader(prog, vertShader);
		glAttachShader(prog, fragShader);

		shaders[0] = vertShader;
		shaders[1] = fragShader;
	}

	void Pipeline::link() const {
		glLinkProgram(prog);

		int success;
		char log[512];

		glGetProgramiv(prog, GL_LINK_STATUS, &success);

		if (success == GL_FALSE) {
			glGetProgramInfoLog(prog, 512, nullptr, log);
			std::cout << "Failed to link pipeline\n" << log << std::endl;
		}

		glValidateProgram(prog);

		for (auto shader : shaders) {
			if (shader != 0) {
				glDeleteShader(shader);
			}
		}
	}
} // r
