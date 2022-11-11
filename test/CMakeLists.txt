cmake_minimum_required(VERSION 3.5)
project(wfcpp-test VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(ENABLE_COVERAGE)
  # set compiler flags
  set(CMAKE_CXX_FLAGS "-O0 -coverage")

  # find required tools
  find_program(LCOV lcov REQUIRED)
  find_program(GENHTML genhtml REQUIRED)

  # add coverage target
  add_custom_target(coverage
    # gather data
    COMMAND ${LCOV} --directory . --capture --output-file coverage.info
    # generate report
    COMMAND ${GENHTML} --demangle-cpp -o coverage coverage.info
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

else()
  # set compiler flags
  set(CMAKE_CXX_FLAGS "-O2")
endif()

#wcfpp-test.exe
add_executable(${PROJECT_NAME} src/TestApp.cpp)

target_link_libraries(${PROJECT_NAME} wfcpp)

target_include_directories(${PROJECT_NAME} PRIVATE wfcpp)
