
add_executable (destruct_cl main.cpp state.cpp state.h)

find_package (glfw3 CONFIG REQUIRED)
find_package (GLEW REQUIRED)
find_package (OpenGL REQUIRED)

target_include_directories (destruct_cl PUBLIC ${GLFW_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})

target_link_libraries (destruct_cl PRIVATE destruct_sh ${GLFW_LIBRARIES} ${OPENGL_gl_LIBRARY} ${GLEW_LIBRARIES} glfw)
