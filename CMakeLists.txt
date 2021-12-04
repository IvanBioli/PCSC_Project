
cmake_minimum_required (VERSION 3.1)
project (PCSC_project)

set(CMAKE_CXX_STANDARD 17)

add_library(pcsc
  src/pcsc.cc
)

add_library(methods
        src/methods/AbstractEigs.cpp
        src/methods/AbstractPowerMethod.cpp
        src/methods/InvPowerMethod.cpp
        src/methods/PowerMethod.cpp
        src/methods/QRMethod.cpp
        src/methods/ShiftInvPowerMethod.cpp
        src/methods/ShiftPowerMethod.cpp
)


#add_subdirectory(googletest)
#include_directories(googletest)
include_directories(eigen)
include_directories(src/methods)

add_executable(main src/main.cc)
target_link_libraries(main pcsc)

add_executable(main_Ivan src/main_Ivan.cc)
target_link_libraries(main_Ivan methods)

#add_executable(test_pcsc test/test.cc)
#target_link_libraries(test_pcsc gtest_main gtest pthread pcsc)

add_custom_target(test ./test_pcsc DEPENDS test_pcsc)
