
#ifndef DESTRUCT_DISPLAY_H
#define DESTRUCT_DISPLAY_H

#include <memory>
#include "Render.h"

namespace r {

	class Display {
	public:
		Display();
		
		inline bool shouldClose() {
			return glfwWindowShouldClose(this->win.get());
		}

		inline bool getKey(int key) {
			return glfwGetKey(win.get(), key);
		}

		void poll();
	private:
		std::shared_ptr<GLFWwindow> win;
	};

}

#endif // DESTRUCT_DISPLAY_H
