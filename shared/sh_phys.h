#pragma once

#define PX_RELEASE(obj) obj->release(); obj = nullptr

#include <PxPhysicsAPI.h>

using namespace physx;

namespace phys {
    void initialize();
    void update(float delta);
    void release();
}
