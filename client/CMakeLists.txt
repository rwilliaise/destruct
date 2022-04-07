
add_executable (destruct_cl main.c r_window.c r_window.h r_shared.h)

find_package (GLEW REQUIRED)
find_package (OpenGL REQUIRED)
find_package (FreeGLUT REQUIRED)

find_package (SDL2 REQUIRED)
target_include_directories (destruct_cl PUBLIC ${SDL2_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

target_link_libraries (destruct_cl LINK_PUBLIC destruct_sh ${SDL2_LIBRARIES} ${OPENGL_gl_LIBRARY} ${GLEW_LIBRARIES} FreeGLUT::freeglut)