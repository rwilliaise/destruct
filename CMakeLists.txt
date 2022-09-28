cmake_minimum_required(VERSION 3.21)
project (DESTRUCT CXX)

find_package(glfw3 CONFIG REQUIRED)
find_package(Bullet CONFIG REQUIRED)

add_library(shared STATIC shared/PhysManager.cpp shared/PhysManager.h)
target_link_libraries(shared LinearMath Bullet3Common BulletDynamics BulletSoftBody)

message(STATUS "Bullet found: " ${BULLET_FOUND})

message(STATUS ${BULLET_INCLUDE_DIRS})
target_include_directories(shared PRIVATE ${BULLET_INCLUDE_DIRS})

add_executable(client client/main.cpp client/Display.cpp client/Display.h)
target_link_libraries(client glfw shared) 
