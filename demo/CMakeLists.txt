cmake_minimum_required(VERSION 3.5)
project(wfcpp-demo VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(raylib)

add_executable(demo.exe 
  demo.cpp
)

target_link_libraries(demo.exe 
  wfcpp 
  raylib
)

target_include_directories(demo.exe 
  PRIVATE 
    wfcpp
    raylib
)
