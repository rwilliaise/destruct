#include <exception>
#include <cstdio>
#include "sh_scene.h"
#include "sh_phys.h"
#include "r_renderer.h"
#include "r_state.h"

int main() {

    try {
        Scene scene;
        Renderer renderer(scene);

        auto ent = scene.addEntity();

        scene.addComponent(ent, (void*)"Test", ComponentType::RigidBody);

        phys::initialize();
        render::initialize(renderer);

        render::updateCallback([](float delta) {
            phys::update(delta);
        });

        render::loop();

        render::release();
        phys::release();

    } catch (std::exception& e) {
        fprintf(stderr, "RUNTIME ERR: %s", e.what());
    }
}
