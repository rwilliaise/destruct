
#include "PhysManager.h"

namespace sh {
    void PhysManager::step(float delta) {
        world.stepSimulation(delta, 4);
    }
} // sh