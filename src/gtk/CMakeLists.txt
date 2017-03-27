find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})

add_library(acl_gtk ../common/acllib.h acllib.c)
target_link_libraries(acl_gtk ${GTK3_LIBRARIES})

add_library(acllib ALIAS acl_gtk)

set_target_properties(acl_gtk PROPERTIES C_STANDARD 99)
