cmake_minimum_required(VERSION 3.5)
project(wfcpp-test VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#wcfpp-test.exe
add_executable(main.exe src/main.cpp)

if (CMAKE_BUILD_TYPE MATCHES "^[Dd]ebug")
  # set compiler flags
  set(CMAKE_CXX_FLAGS "-O0 -coverage -Wall")

  # find required tools
  find_program(LCOV lcov REQUIRED)
  find_program(GENHTML genhtml REQUIRED)

  # add coverage target
  add_custom_target(coverage
    # gather data
    COMMAND ${LCOV} --directory . --capture --output-file coverage.info
    # generate report
    COMMAND ${GENHTML} --demangle-cpp -o coverage ../coverage.info
    )

  target_link_libraries(main.exe wfcpp -coverage)

else()
  # set compiler flags
  set(CMAKE_CXX_FLAGS "-O2")
  target_link_libraries(main.exe wfcpp)
endif()


target_link_libraries(main.exe wfcpp)

target_include_directories(main.exe PRIVATE wfcpp)
