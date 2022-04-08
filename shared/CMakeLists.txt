
add_library (destruct_sh sh_scene.cpp sh_scene.h shared.h)

target_include_directories (destruct_sh PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
