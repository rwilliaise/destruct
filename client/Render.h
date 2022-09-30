
#ifndef DESTRUCT_RENDER_H
#define DESTRUCT_RENDER_H

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace r { 
	class VaoOwner {
	public:
		VaoOwner() {
			glGenVertexArrays(1, &vao);
		}
		~VaoOwner() {
			glDeleteVertexArrays(1, &vao);
			
			uint32_t count;
			GLuint* list = getBuffers(count);
			glDeleteBuffers(count, list);
		}

		VaoOwner(const VaoOwner& vao): vao(vao.vao) {}
		VaoOwner& operator=(const VaoOwner& vao) = delete;

		virtual GLuint* getBuffers(uint32_t& count);

		inline void bind() {
			glBindVertexArray(vao);
		}
	protected:
		GLuint vao;
	};

} // r

#endif // DESTRUCT_RENDER_H
