
#include "r_state.h"
#include <stdexcept>
#include "shared.h"
#include "r_renderer.h"

namespace render {
    namespace {
        struct GLFWwindow *window;
        Renderer *renderer;

        void (*genericCb)(float) = nullptr;
    }

    int initialize(Renderer& r) {
        if (glfwInit() != GLFW_TRUE) {
            return SH_VIDEO_INIT_FAILURE;
        }

        renderer = &r;
        window = glfwCreateWindow(640, 480, "destruct", nullptr, nullptr);
        return 0;
    }

    void updateCallback(void (*cb)(float)) {
        genericCb = cb;
    }

    void release() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void loop() {
        glfwMakeContextCurrent(window);

        GLenum err = glewInit();

        if (GLEW_OK != err) {
            throw std::runtime_error("Failed glew init.");
        }

        double last = glfwGetTime();
        double delta;

        while (!glfwWindowShouldClose(window)) {
            glClear(GL_COLOR_BUFFER_BIT);


            delta = glfwGetTime() - last;

            renderer->update((float) delta);

            if (genericCb != nullptr) {
                genericCb((float) delta);
            }

            last = glfwGetTime();

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }
}
