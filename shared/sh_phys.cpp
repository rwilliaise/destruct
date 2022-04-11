
#define PVD_HOST "127.0.0.1" // default

//#if DEBUG
#define PVD_ENABLED
//#endif

#include <sh_phys.h>
#include <stdexcept>

namespace phys {
    namespace {
        PxFoundation* foundation = nullptr;
        PxPhysics* physics = nullptr;
//        PxCooking* cooking = nullptr;
        PxPvd* pvd = nullptr;
        PxPvdTransport* transport = nullptr;
        PxDefaultCpuDispatcher* dispatcher = nullptr;
        PxScene* currentScene = nullptr;
        PxSceneDesc* basicScene = nullptr;
    }

    int initialize() {
        if (foundation) {
            return -1;
        }
        static PxDefaultErrorCallback errorCallback;
        static PxDefaultAllocator allocatorCallback;

        foundation = PxCreateFoundation(PX_PHYSICS_VERSION, allocatorCallback, errorCallback);

#ifdef PVD_ENABLED
        pvd = PxCreatePvd(*foundation);
        transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
        pvd->connect(*transport, PxPvdInstrumentationFlag::eALL);
#endif

        static PxTolerancesScale scale;

        physics = PxCreatePhysics(PX_PHYSICS_VERSION, *foundation, scale, true, pvd);
//        cooking = PxCreateCooking(PX_PHYSICS_VERSION, *foundation, PxCookingParams(scale));

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

        PxShape* shape = physics->createShape(PxBoxGeometry(2.0f, 2.0f, 2.0f), *material);
        PxTransform t(PxVec3(0, 0, 0));
        for(PxU32 i=0; i<10;i++)
        {
            for(PxU32 j=0;j<10-i;j++)
            {
                PxTransform localTm(PxVec3(PxReal(j*2) - PxReal(10-i), PxReal(i*2+1), 0) * 2.0f);
                PxRigidDynamic* body = physics->createRigidDynamic(t.transform(localTm));
                body->attachShape(*shape);
                PxRigidBodyExt::updateMassAndInertia(*body, 10.0f);
                currentScene->addActor(*body);
            }
        }
        shape->release();

        return 0;
    }

    void update(float delta) {
        if (currentScene != nullptr) {
            currentScene->simulate(1.0f/60.0f);
            currentScene->fetchResults(true);
        }
    }

    void release() {
        delete basicScene;

        PX_RELEASE(currentScene);
        PX_RELEASE(dispatcher);
//        PX_RELEASE(cooking);
        PX_RELEASE(physics);
#ifdef PVD_ENABLED
        PX_RELEASE(pvd);
        PX_RELEASE(transport);
#endif
        PX_RELEASE(foundation);
    }
}
