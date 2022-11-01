
#pragma once

#include "Entity.h"
#include "Render.h"
#include <glad/gl.h>
#include <string>

namespace r {

	/** 
	 * Clear the currently used program.
	 * Not useful but is nice to have as a formality, to show the end of scope
	 * for the r::Pipelines reach.
	 */
	inline void unuse() {
		glUseProgram(0);
	}
	
	/**
	 * OpenGL program management and shader compiliation.
	 */
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

		/**
		 * Compile shader code and attach it to the current program. Must be paired
		 * with #link(). 
		 */
		void compile(std::string vert, std::string frag); 
		/**
		 * Link shaders, validate the program, then delete the shaders. Must be called
		 * after #compile().
		 */
		void link() const;

		/** Load transformation matrix, calculating it using given entity. */
		void transform(sh::Entity& ent);

		/** 
		 * Bind vertex buffer attribute to string location. Must be called before 
		 * #link().
		 * Not required except on older versions of OpenGL.
		 */
		inline void bindAttrib(GLuint loc, std::string name) const {
			glBindAttribLocation(prog, loc, name.c_str());
		}

		/**
		 * Uses the program, rendering all glDraw- operations with this pipeline.
		 */
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

