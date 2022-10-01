cmake_minimum_required(VERSION 3.21)
project (DESTRUCT CXX)

add_subdirectory(thirdparty/glad)

find_package(glfw3 CONFIG REQUIRED)
find_package(Bullet REQUIRED)

add_library(shared STATIC shared/PhysManager.cpp shared/PhysManager.h)
target_link_libraries(shared INTERFACE BulletSoftBody BulletDynamics BulletCollision Bullet3Common LinearMath)
target_include_directories(shared PRIVATE ${BULLET_INCLUDE_DIR})

add_executable(client client/main.cpp client/Model.cpp client/Model.h client/Obj.cpp client/Display.cpp client/Display.h)
target_link_libraries(client glfw shared glad) 
