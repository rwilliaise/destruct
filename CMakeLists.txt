cmake_minimum_required(VERSION 3.20)
project (DESTRUCT C CXX)

set(VCPKG_TARGET_TRIPLET x64-windows-static)

include(resource.cmake)

add_resources(cloud_frag cloud.frag)
add_resources(cloud_vert cloud.vert)

add_subdirectory(thirdparty/glad)
add_subdirectory(thirdparty/glfw)

find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)

if(WIN32)
	find_package(Bullet CONFIG REQUIRED)
else()
	find_package(Bullet REQUIRED)
endif()

add_library(shared STATIC shared/PhysManager.cpp shared/PhysManager.h shared/Entity.cpp shared/Entity.h shared/Util.h shared/PlayerEntity.h shared/WorldSpawnEntity.h shared/Util.cpp)
target_link_libraries(shared PRIVATE BulletSoftBody BulletDynamics BulletCollision glm Bullet3Common LinearMath)
target_include_directories(shared PRIVATE ${GLM_INCLUDE_DIRS} ${BULLET_INCLUDE_DIR})

add_executable(client ${cloud_frag} ${cloud_vert} client/Camera.cpp client/Camera.h client/main.cpp client/Mesh.cpp client/Mesh.h client/Shader.cpp client/Shader.h client/Render.h client/Display.cpp client/Display.h)
target_link_libraries(client PRIVATE OpenGL::GL glad glm glfw)
target_include_directories(client PRIVATE ${BULLET_INCLUDE_DIR} shared)

