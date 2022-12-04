cmake_minimum_required(VERSION 3.5)
project(wfcpp-test VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#wcfpp-test.exe
add_executable(main.exe src/main.cpp)

if (CMAKE_BUILD_TYPE MATCHES "^[Dd]ebug")
  # set compiler flags
  set(CMAKE_CXX_FLAGS "-O0 -Wall -fprofile-arcs -ftest-coverage")
 
  add_compile_options("-coverage")
  link_libraries("-coverage")

else()
  # set compiler flags
  set(CMAKE_CXX_FLAGS "-O2")

endif()


target_link_libraries(main.exe wfcpp)

target_include_directories(main.exe PRIVATE wfcpp)
