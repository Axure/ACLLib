if (CMAKE_BUILD_TYPE STREQUAL "Coverage")
  list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules")
  include(CodeCoverage)
#  set(LCOV_REMOVE_EXTRA "'include/gtest/*'") # TODO: Fix this
endif ()

add_subdirectory(googletest)
add_subdirectory(basic)
