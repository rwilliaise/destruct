cmake_minimum_required(VERSION 3.21)
project (DESTRUCT CXX)

set(VCPKG_TARGET_TRIPLET x64-windows-static)

add_subdirectory(thirdparty/glad)

find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
if(WIN32)
	find_package(Bullet CONFIG REQUIRED)
else()
	find_package(Bullet REQUIRED)
endif()

add_library(shared STATIC shared/PhysManager.cpp shared/PhysManager.h shared/Entity.cpp shared/Entity.h shared/Util.h shared/PlayerEntity.h shared/WorldSpawnEntity.h shared/Util.cpp)
target_link_libraries(shared BulletSoftBody BulletDynamics BulletCollision glm::glm Bullet3Common LinearMath glm::glm)
target_include_directories(shared PRIVATE ${GLM_INCLUDE_DIRS} ${BULLET_INCLUDE_DIR})

add_executable(client client/main.cpp client/Model.cpp client/Model.h client/Obj.cpp client/Display.cpp client/Display.h)
target_link_libraries(client glfw shared glad glm::glm) 
target_include_directories(client PRIVATE ${GLAD_INCLUDE_DIRS})
