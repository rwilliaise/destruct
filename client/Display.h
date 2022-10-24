
#ifndef DESTRUCT_DISPLAY_H
#define DESTRUCT_DISPLAY_H

#include <memory>
#include <functional>
#include "Render.h"
#include "GLFW/glfw3.h"

namespace r {


	class Display {
	public:
    using FramebufferSizeCallback = std::function<void (int, int)>;

		Display();
		
		inline bool shouldClose() {
			return glfwWindowShouldClose(this->win.get());
		}

		inline bool getKey(int key) {
			return glfwGetKey(win.get(), key);
		}

    inline float getAspect() {
      int width, height;
      glfwGetFramebufferSize(win.get(), &width, &height);
      return (float) width / height;
    }

		void poll();

    inline void setFramebufferSizeCallback(FramebufferSizeCallback callback) {
      cb = callback;
    }
	private:
		std::shared_ptr<GLFWwindow> win;
    FramebufferSizeCallback cb = nullptr;
	};

}

#endif // DESTRUCT_DISPLAY_H
