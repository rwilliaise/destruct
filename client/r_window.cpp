
#include "r_window.h"
#include "shared.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <exception>

r_State::r_State() {
    if (glfwInit() != 0) {
        throw sh_Error::VIDEO_INIT_FAILURE;
    }

    window = glfwCreateWindow(640, 480, "destruct", nullptr, nullptr);
}

r_State::~r_State() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void r_State::loop() {
    GLenum err = glewInit();

    if (GLEW_OK != err) {
        throw sh_Error::VIDEO_INIT_FAILURE;
    }

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        // TODO: renderer

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
