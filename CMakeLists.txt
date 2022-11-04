cmake_minimum_required(VERSION 3.5)
project(wfcpp-project VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(test)
add_subdirectory(library)