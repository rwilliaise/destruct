
#ifndef DESTRUCT_DISPLAY_H
#define DESTRUCT_DISPLAY_H

#include <memory>
#include <functional>
#include "Render.h"
#include "GLFW/glfw3.h"

namespace r {

	/**
	 * Smart pointer wrapper for GLFWwindow *.
	 */
	class Display {
	public:
		using FramebufferSizeCallback = std::function<void (int, int)>;
		using CursorPosCallback = std::function<void (double x, double y)>;

		/** Initializes smart pointer and callbacks. */
		Display();

		inline GLFWwindow *get() {
			return win.get();
		}
		
		inline bool shouldClose() {
			return glfwWindowShouldClose(this->win.get());
		}

		inline bool getKey(int key) {
			return glfwGetKey(win.get(), key);
		}

		inline bool getMouseButton(int mouseButton) {
			return glfwGetMouseButton(win.get(), mouseButton);
		}

		/** Calculate aspect ratio of current frame buffer. */
		inline float getAspect() {
			int width, height;
			glfwGetFramebufferSize(win.get(), &width, &height);
			return (float) width / height;
		}

		/** Poll window events and flush frame buffer. */
		void poll();

		inline void setFramebufferSizeCallback(FramebufferSizeCallback callback) {
			framebufferSizeCallback = callback;
		}

		inline void setCursorPosCallback(CursorPosCallback callback) {
			cursorPosCallback = callback;
		}
	private:
		std::shared_ptr<GLFWwindow> win;

		FramebufferSizeCallback framebufferSizeCallback = nullptr;
		CursorPosCallback cursorPosCallback = nullptr;
	};

}

#endif // DESTRUCT_DISPLAY_H
