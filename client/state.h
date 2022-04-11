#pragma once

#include <gl/glew.h>
#include <GLFW/glfw3.h>

namespace render {

    int initialize();
    void updateCallback(void (*cb)(float));
    void release();
    void loop();
}