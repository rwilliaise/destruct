
add_executable (destruct_cl main.c)

target_link_libraries (destruct_cl LINK_PUBLIC destruct_sh)
