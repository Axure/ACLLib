add_library(acl_qt
        verdigris/src/wobjectimpl.h
        verdigris/src/wobjectdefs.h
        ${ACL_HEADERS}
        functionalities/acllib.cpp
        window.cpp window.h
        components/IntTimer.cpp components/IntTimer.h
        components/PaintArea.cpp components/PaintArea.h
        components/KeyboardTranslator.cpp components/KeyboardTranslator.h components/MouseTranslator.cpp components/MouseTranslator.h)

set(CMAKE_INCLUDE_CURRENT_DIR OFF)
set(CMAKE_AUTOMOC OFF)

find_package(Qt5Widgets)

target_link_libraries(acl_qt Qt5::Widgets)
set_target_properties(acl_qt PROPERTIES CXX_STANDARD 14)
