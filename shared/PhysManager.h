
#pragma once

#include <btBulletDynamicsCommon.h>
#include <memory>

namespace sh {

		class PhysManager {
		public:
//				PhysManager();

				void step(float delta);

		private:
				btDefaultCollisionConfiguration colConfig = btDefaultCollisionConfiguration();
				btCollisionDispatcher colDispatch = btCollisionDispatcher(&this->colConfig);
				std::unique_ptr<btBroadphaseInterface> broadphase = std::make_unique<btDbvtBroadphase>();
				btSequentialImpulseConstraintSolver solver;
				btDiscreteDynamicsWorld world = btDiscreteDynamicsWorld(
								&colDispatch,
								broadphase.get(),
								&solver,
								&colConfig
				);
		};

} // sh

