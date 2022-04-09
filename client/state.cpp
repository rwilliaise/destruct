
#include "state.h"
#include <stdexcept>

namespace render {
    State::State() {
        if (glfwInit() != GLFW_TRUE) {
            throw std::runtime_error("Failed glfw init.");
        }

        window = glfwCreateWindow(640, 480, "destruct", nullptr, nullptr);
    }

    State::~State() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void State::loop() {
        glfwMakeContextCurrent(window);

        GLenum err = glewInit();

        if (GLEW_OK != err) {
            throw std::runtime_error("Failed glew init.");
        }

        while (!glfwWindowShouldClose(window)) {
            glClear(GL_COLOR_BUFFER_BIT);

            // TODO: renderer

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }
}
