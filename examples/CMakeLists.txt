add_executable(main main.c)

include_directories(../src/common)
target_link_libraries(main acllib)

add_executable(main_qt main.c)
target_link_libraries(main_qt acl_qt)

add_executable(main_win32 main.c)
target_link_libraries(main_win32 acl_win32)

add_executable(main_gtk main.c)
target_link_libraries(main_gtk acl_gtk)

add_executable(network_qt network.c)
target_link_libraries(network_qt acl_qt)
