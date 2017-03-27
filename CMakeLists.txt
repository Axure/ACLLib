CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
project(ACLLib)

#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -Werror -Wextra")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra")
set(ACL_INCLUDE_DIR src/common)
set(ACL_LIB_DIR build)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(examples)
