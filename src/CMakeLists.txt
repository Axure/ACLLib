IF (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    # Linux specific code
    SET(OperatingSystem "Linux")
ENDIF (${CMAKE_SYSTEM_NAME} MATCHES "Linux")


FIND_PACKAGE(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTK3 gtk+-3.0)

INCLUDE_DIRECTORIES(${GTK3_INCLUDE_DIRS})
LINK_DIRECTORIES(${GTK3_LIBRARY_DIRS})

ADD_DEFINITIONS(${GTK3_CFLAGS_OTHER})

add_library(acl_gtk common/acllib.h gtk/acllib.c)
add_library(acl_win32 common/acllib.h win32/acllib.c)

target_include_directories(acl_win32 PUBLIC mingw-headers)
target_link_libraries(acl_win32 gdi32 ole32 oleaut32 uuid winmm msimg32)
add_library(acllib ALIAS acl_gtk)

TARGET_LINK_LIBRARIES(acl_gtk ${GTK3_LIBRARIES})

add_library(acl_qt common/acllib.h qt/acllib.cpp)
set_target_properties(acl_qt PROPERTIES CXX_VERSION 14)
set_target_properties(acl_qt PROPERTIES CXX_STANDARD 14)

set(CMAKE_INCLUDE_CURRENT_DIR OFF)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC OFF)

# Find the QtWidgets library
find_package(Qt5Widgets)

target_link_libraries(acl_qt Qt5::Widgets)
