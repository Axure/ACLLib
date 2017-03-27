
add_library(acl_win32
        ${ACL_HEADERS}
        functionalities/audio.c
        functionalities/events.c
        functionalities/image.c
        functionalities/paint.c
        functionalities/window.c
        functionalities/window.h
        global.h
        )

target_include_directories(acl_win32 PUBLIC mingw-headers)
target_link_libraries(acl_win32 gdi32 ole32 oleaut32 uuid winmm msimg32)

set_target_properties(acl_win32 PROPERTIES C_STANDARD 99)
