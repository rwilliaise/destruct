cmake_minimum_required(VERSION 3.21)
project (DESTRUCT CXX)

find_package(glfw3 CONFIG REQUIRED)
find_package(Bullet CONFIG REQUIRED)

add_library(shared STATIC shared/PhysManager.cpp shared/PhysManager.h)
target_link_libraries(shared LinearMath Bullet3Common BulletDynamics BulletSoftBody glfw)

add_executable(client client/main.cpp)
