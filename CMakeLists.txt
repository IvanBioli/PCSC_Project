
cmake_minimum_required (VERSION 3.1)
project (PCSC_project)

set(CMAKE_CXX_STANDARD 17)

add_library(pcsc
  src/pcsc.cc
)

#add_subdirectory(googletest)
include_directories(googletest)
include_directories(eigen)

add_executable(main src/main.cc)
target_link_libraries(main pcsc)

add_executable(test_pcsc test/test.cc)
target_link_libraries(test_pcsc gtest_main gtest pthread pcsc)

add_custom_target(test ./test_pcsc DEPENDS test_pcsc)
