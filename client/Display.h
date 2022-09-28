
#ifndef DESTRUCT_DISPLAY_H
#define DESTRUCT_DISPLAY_H

#include <memory>
#include <GLFW/glfw3.h>

namespace r {

	class Display {
	public:
		Display();
		
		inline bool shouldClose() {
			return glfwWindowShouldClose(this->win.get());
		}

		void poll();
	private:
		std::shared_ptr<GLFWwindow> win;
	};

}

#endif // DESTRUCT_DISPLAY_H
