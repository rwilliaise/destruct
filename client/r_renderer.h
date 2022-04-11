#pragma once

#include "sh_scene.h"

class Renderer {
public:
    explicit Renderer(Scene &scene): scene(scene) {}

    void update(float delta);

    inline Scene &getScene() {
        return scene;
    }
private:
    Scene &scene;
};