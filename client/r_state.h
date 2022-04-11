#pragma once

#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include "r_renderer.h"

namespace render {

    int initialize(Renderer& r);
    void updateCallback(void (*cb)(float));
    void release();
    void loop();
}