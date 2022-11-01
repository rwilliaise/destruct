
#include "Display.h" 
#include "Render.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace r {
	
	Display::Display() {
		glfwWindowHint(GLFW_SAMPLES, 4);
		GLFWwindow* win = glfwCreateWindow(640, 480, "DESTRUCT", nullptr, nullptr);
		glfwMakeContextCurrent(win);
		gladLoadGL((GLADloadfunc) glfwGetProcAddress);

		glfwSetWindowUserPointer(win, this);
		glfwSetFramebufferSizeCallback(win, [](GLFWwindow* win, int width, int height) {
			Display *display = static_cast<Display*>(glfwGetWindowUserPointer(win));
			glViewport(0, 0, width, height);
			if (display->framebufferSizeCallback != nullptr) {
				display->framebufferSizeCallback(width, height);
			}
		});

		glfwSetCursorPosCallback(win, [](GLFWwindow* win, double xPos, double yPos) {
			Display *display = static_cast<Display*>(glfwGetWindowUserPointer(win));

			if (display->cursorPosCallback != nullptr) {
				display->cursorPosCallback(xPos, yPos);
			}
		});

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

