
#include "Display.h" 
#include "Render.h"
#include "glad/gl.h"
#include <GLFW/glfw3.h>

namespace r {
	
	Display::Display() {
		GLFWwindow* win = glfwCreateWindow(640, 480, "DESTRUCT", nullptr, nullptr);
		glfwMakeContextCurrent(win);
		gladLoadGL((GLADloadfunc) glfwGetProcAddress);

		this->win = std::shared_ptr<GLFWwindow>(win, [](GLFWwindow* ptr) {
			glfwDestroyWindow(ptr);		
		});
	}

	void Display::poll() {
		GLFWwindow* ptr = this->win.get();
		glfwSwapBuffers(ptr);
		glfwPollEvents();
	}
}

