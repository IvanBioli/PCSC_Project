
cmake_minimum_required (VERSION 3.1)
project (PCSC_project)

set(CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

add_library(methods
        src/methods/AbstractEigs.cpp
        src/methods/AbstractPowerMethod.cpp
        src/methods/InvPowerMethod.cpp
        src/methods/PowerMethod.cpp
        src/methods/QRMethod.cpp
        src/methods/ShiftInvPowerMethod.cpp
        src/methods/ShiftPowerMethod.cpp
)

add_library(reader
        src/reader/Reader.cpp
        src/reader/FileReader.cpp
        )

add_library(exceptions
        src/exceptions/Exceptions.cpp
        )

add_subdirectory(googletest)
include_directories(eigen)
include_directories(src/methods)
include_directories(src/reader)
include_directories(src/exceptions)

add_executable(main src/main.cc)
target_link_libraries(main methods reader exceptions)

# TESTS
add_executable(test_methods test/test_methods.cc)
target_link_libraries(test_methods gtest_main gtest pthread methods)

add_executable(test_reader test/test_reader.cc)
target_link_libraries(test_reader gtest_main gtest pthread reader)

#add_custom_target(test ./test_pcsc DEPENDS test_pcsc)
