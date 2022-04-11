#include <exception>
#include <cstdio>
#include "sh_scene.h"
#include "sh_phys.h"
#include "state.h"

int main() {

    try {
        render::initialize();
        phys::initialize();

        render::updateCallback(phys::update);

        render::loop();

        render::release();
        phys::release();

    } catch (std::exception& e) {
        fprintf(stderr, "RUNTIME ERR: %s", e.what());
    }
}
