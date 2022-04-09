#include <exception>
#include <cstdio>
#include "sh_scene.h"
#include "state.h"

int main() {

    try {
        render::State state;
        Scene scene;

        state.loop();
    } catch (std::exception& e) {
        fprintf(stderr, "RUNTIME ERR: %s", e.what());
    }
}
