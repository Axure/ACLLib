

add_library(acl_sdl acllib_gl.c)

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

target_link_libraries(acl_sdl ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES})

set_target_properties(acl_sdl PROPERTIES C_STANDARD 99)
