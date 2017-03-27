IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    # Linux specific code
    SET(OperatingSystem "Linux")


ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")


#if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
#    # Linux specific code
#    set(OperatingSystem "Linux")
#
#endif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")

set(ACL_HEADERS
        ${CMAKE_CURRENT_LIST_DIR}/common/acllib.h
        ${CMAKE_CURRENT_LIST_DIR}/common/platform.h
        ${CMAKE_CURRENT_LIST_DIR}/common/functionalities/audio.h
        ${CMAKE_CURRENT_LIST_DIR}/common/functionalities/image.h
        ${CMAKE_CURRENT_LIST_DIR}/common/functionalities/events.h
        ${CMAKE_CURRENT_LIST_DIR}/common/functionalities/window.h
        )

include_directories(common)
add_subdirectory(gtk)
add_subdirectory(qt)
add_subdirectory(win32)
add_subdirectory(sdl)
