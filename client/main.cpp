
#include "Render.h"
#include "Display.h"

int main() {
	if (glfwInit() == GLFW_FALSE) {
		return -1;
	}

   	r::Display display = r::Display();

	while (!display.shouldClose()) {
		glClearColor(1.f, 0.f, 0.f, 1.f);
		display.poll();
	}

	glfwTerminate();
}
