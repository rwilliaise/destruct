
#define PVD_HOST "localhost" // default
#define PVD_ENABLED
#include <sh_phys.h>
#include <stdexcept>

namespace phys {
    PxFoundation* foundation = nullptr;
    PxPhysics* physics = nullptr;
    PxCooking* cooking = nullptr;
#ifdef PVD_ENABLED
    PxPvd* pvd = nullptr;
    PxPvdTransport* transport = nullptr;
#endif

    PxDefaultCpuDispatcher* dispatcher = nullptr;
    PxScene* currentScene = nullptr;
    PxSceneDesc* basicScene = nullptr;

    void initialize() {
        if (foundation != nullptr) {
            throw std::runtime_error("Already init physics.");
        }
        static PxDefaultErrorCallback errorCallback;
        static PxDefaultAllocator allocatorCallback;

        foundation = PxCreateFoundation(PX_PHYSICS_VERSION, allocatorCallback, errorCallback);

#ifdef PVD_ENABLED
        pvd = PxCreatePvd(*foundation);
        transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
        pvd->connect(*transport, PxPvdInstrumentationFlag::eALL);
#endif

        PxTolerancesScale scale;

        physics = PxCreatePhysics(PX_PHYSICS_VERSION, *foundation, scale, true);
        cooking = PxCreateCooking(PX_PHYSICS_VERSION, *foundation, PxCookingParams(scale));

        basicScene = new PxSceneDesc(scale);
        basicScene->gravity = PxVec3(0, -9.81f, 0);

        dispatcher = PxDefaultCpuDispatcherCreate(2);

        basicScene->cpuDispatcher = dispatcher;
        basicScene->filterShader = PxDefaultSimulationFilterShader;

        currentScene = physics->createScene(*basicScene);
        PxMaterial* material = physics->createMaterial(0.5f, 0.5f, 0.6f);

        PxPvdSceneClient* pvdClient = currentScene->getScenePvdClient();
        if (pvdClient) {
            pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
            pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
            pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
        }

        PxRigidStatic* groundPlane = PxCreatePlane(*physics, PxPlane(0,1,0,0), *material);
        currentScene->addActor(*groundPlane);

    }

    void update(float delta) {
        printf("%f\n", 1/delta);
        if (currentScene != nullptr) {
            currentScene->simulate(delta);
            currentScene->fetchResults(true);
        }
    }

    void release() {
        PX_RELEASE(currentScene);
        PX_RELEASE(physics);
        PX_RELEASE(pvd);
        PX_RELEASE(transport);
        PX_RELEASE(foundation);

        delete basicScene;
    }
}
