add_executable(basicTestRunner basic.cpp)
target_link_libraries(basicTestRunner gtest gtest_main)

target_include_directories(basicTestRunner PRIVATE ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
target_include_directories(basicTestRunner PRIVATE ../../src)

if (CMAKE_BUILD_TYPE STREQUAL "Coverage")
#  set(LCOV_REMOVE_EXTRA "include/*")
  setup_target_for_coverage(basicTestRunner_coverage basicTestRunner coverage)

  SET(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
  SET(CMAKE_C_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
endif() #CMAKE_BUILD_TYPE STREQUAL "Coverage"
