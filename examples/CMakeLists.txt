include_directories(../src/common)

add_executable(main main.c)
target_link_libraries(main acllib)

####################
###Simple example###
####################
add_executable(main_qt main.c)
target_link_libraries(main_qt acl_qt)

add_executable(main_win32 main.c)
target_link_libraries(main_win32 acl_win32)

add_executable(main_gtk main.c)
target_link_libraries(main_gtk acl_gtk)

add_executable(network_qt network.c)
target_link_libraries(network_qt acl_qt)

add_executable(main_sdl main.c)
target_link_libraries(main_sdl acl_sdl)
#########################
###Mouse click example###
#########################
add_executable(mouse_click_qt mouse_click.c)
target_link_libraries(mouse_click_qt acl_qt)

add_executable(mouse_click_win32 mouse_click.c)
target_link_libraries(mouse_click_win32 acl_win32)

####################
####Clock example###
####################
add_executable(clock_sdl clock.c)
target_link_libraries(clock_sdl acl_sdl m)

add_executable(clock_win32 clock.c)
target_link_libraries(clock_win32 acl_win32)

add_executable(clock_qt clock.c)
target_link_libraries(clock_qt acl_qt)

add_executable(clock_gtk clock.c)
target_link_libraries(clock_gtk acl_gtk m)

####################
##Keyboard exampl###
####################
add_executable(keyboard_win32 keyboard.c)
target_link_libraries(keyboard_win32 acl_win32)

add_executable(keyboard_qt keyboard.c)
target_link_libraries(keyboard_qt acl_qt)

add_executable(keyboard_gtk keyboard.c)
target_link_libraries(keyboard_gtk acl_gtk)

####################
#####char exampl####
####################
add_executable(char_win32 char.c)
target_link_libraries(char_win32 acl_win32)

add_executable(char_qt char.c)
target_link_libraries(char_qt acl_qt)

add_executable(char_gtk char.c)
target_link_libraries(char_gtk acl_gtk)

####################
####image exampl####
####################
add_executable(image_win32 image.c)
target_link_libraries(image_win32 acl_win32)

add_executable(image_qt image.c)
target_link_libraries(image_qt acl_qt)

add_executable(image_gtk image.c)
target_link_libraries(image_gtk acl_gtk)

######################
##mouse_move exampl###
######################
add_executable(mouse_move_win32 mouse_move.c)
target_link_libraries(mouse_move_win32 acl_win32)

add_executable(mouse_move_qt mouse_move.c)
target_link_libraries(mouse_move_qt acl_qt)

add_executable(mouse_move_gtk mouse_move.c)
target_link_libraries(mouse_move_gtk acl_gtk)
