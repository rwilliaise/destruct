cmake_minimum_required(VERSION 3.21)
project (DESTRUCT C CXX)

include(resource.cmake)

add_resources(diffuse_frag diffuse.frag)
add_resources(diffuse_vert diffuse.vert)

add_resources(gregolan_txt gregolan.png)
add_resources(gregolan gregolan.obj)
add_resources(gregolan_jr_txt gregolan_jr.png)
add_resources(gregolan_jr gregolan_jr.obj)

set(CLIENT_RESOURCES
  # shaders
  ${diffuse_frag}
  ${diffuse_vert}

  # textures 
  ${gregolan_txt}
  ${gregolan_jr_txt}

  # models
  ${gregolan}
  ${gregolan_jr}
)

add_subdirectory(thirdparty/glad)
add_subdirectory(thirdparty/glfw)

find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)

if(WIN32)
  message(STATUS "Using system installation (did you configure vcpkg?)")
	find_package(Bullet CONFIG REQUIRED)
  find_package(libpng REQUIRED)
else()
	find_package(Bullet REQUIRED)
  find_package(PNG REQUIRED)
endif()

add_library(shared STATIC shared/PhysManager.cpp shared/PhysManager.h shared/Entity.cpp shared/Entity.h shared/Util.h shared/PlayerEntity.h shared/WorldSpawnEntity.h shared/Util.cpp)
target_link_libraries(shared PRIVATE BulletSoftBody BulletDynamics BulletCollision Bullet3Common LinearMath)
target_include_directories(shared PRIVATE ${BULLET_INCLUDE_DIR})

add_executable(client ${CLIENT_RESOURCES} client/Camera.cpp client/Camera.h client/Texture.cpp client/Texture.h client/main.cpp client/Mesh.cpp client/Mesh.h client/Shader.cpp client/Shader.h client/Render.h client/Display.cpp client/Display.h)
target_link_libraries(client PRIVATE OpenGL::GL glad glfw)
target_include_directories(client PRIVATE ${BULLET_INCLUDE_DIR} ${libpng_public_hdrs} shared)

if(WIN32)
  target_link_libraries(shared PRIVATE glm::glm png_static)
  target_link_libraries(client PRIVATE glm::glm png_static)
else()
  target_link_libraries(shared PRIVATE glm PNG::PNG)
  target_link_libraries(client PRIVATE glm PNG::PNG)
endif()
