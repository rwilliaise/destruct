#pragma once

#include <gl/glew.h>
#include <GLFW/glfw3.h>

namespace render {
    class State {
    public:
        State();
        ~State();

        void loop();

    private:
        struct GLFWwindow *window;
    };
}