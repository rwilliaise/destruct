cmake_minimum_required(VERSION 3.20)
project (DESTRUCT C CXX)

set(PNG_BUILD_ZLIB ON)

include(resource.cmake)

add_resources(cloud_frag cloud.frag)
add_resources(cloud_vert cloud.vert)

add_subdirectory(thirdparty/glad)
add_subdirectory(thirdparty/glfw)
add_subdirectory(thirdparty/libpng)
add_subdirectory(thirdparty/zlib)

include_directories(${ZLIB_INCLUDE_DIRS})

find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)

if(WIN32)
	find_package(Bullet CONFIG REQUIRED)
else()
	find_package(Bullet REQUIRED)
endif()

add_library(shared STATIC shared/PhysManager.cpp shared/PhysManager.h shared/Entity.cpp shared/Entity.h shared/Util.h shared/PlayerEntity.h shared/WorldSpawnEntity.h shared/Util.cpp)
target_link_libraries(shared PRIVATE BulletSoftBody BulletDynamics BulletCollision Bullet3Common LinearMath)
target_include_directories(shared PRIVATE ${BULLET_INCLUDE_DIR})

add_executable(client ${cloud_frag} ${cloud_vert} client/Camera.cpp client/Camera.h client/main.cpp client/Mesh.cpp client/Mesh.h client/Shader.cpp client/Shader.h client/Render.h client/Display.cpp client/Display.h)
target_link_libraries(client PRIVATE OpenGL::GL glad glfw png)
target_include_directories(client PRIVATE ${BULLET_INCLUDE_DIR} shared)

if(WIN32)
  target_link_libraries(shared PRIVATE glm::glm)
  target_link_libraries(client PRIVATE glm::glm)
else()
  target_link_libraries(shared PRIVATE glm)
  target_link_libraries(client PRIVATE glm)
endif()
