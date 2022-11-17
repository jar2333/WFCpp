cmake_minimum_required(VERSION 3.5)
project(wfcpp-project VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(IS_DEBUG_BUILD CMAKE_BUILD_TYPE STREQUAL "Debug")

# Indication to the code that this is a debug build
if (${IS_DEBUG_BUILD})
    add_compile_definitions(TEST_DEBUG)
endif ()

add_subdirectory(test)
add_subdirectory(library)