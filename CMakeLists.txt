cmake_minimum_required(VERSION 3.5)
project(wfcpp-project VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(IS_DEBUG_BUILD CMAKE_BUILD_TYPE STREQUAL "Debug")

# Indication to the code that this is a debug build
if (${IS_DEBUG_BUILD})
    add_compile_definitions(TEST_DEBUG)

    # find required tools
    find_program(LCOV lcov REQUIRED)
    find_program(GENHTML genhtml REQUIRED)

    set(COVERAGE_INFO_FILE ${CMAKE_SOURCE_DIR}/build/coverage.info )
    set(COVERAGE_REPORT_DIR ${CMAKE_SOURCE_DIR}/test/coverage )

    # add coverage target
    add_custom_target(coverage
        # gather data
        COMMENT "Gathering coverage data" 
        COMMAND ${LCOV} --directory ${CMAKE_SOURCE_DIR}/build --capture --output-file ${COVERAGE_INFO_FILE} && ${LCOV} -e ${COVERAGE_INFO_FILE} "*/WFCpp/*" -o ${COVERAGE_INFO_FILE} && ${LCOV} -r ${COVERAGE_INFO_FILE} "*/lib/*" -o ${COVERAGE_INFO_FILE}

        # generate report
        COMMENT "Generating report" 
        COMMAND ${GENHTML} --demangle-cpp -o ${COVERAGE_REPORT_DIR} ${COVERAGE_INFO_FILE}
    )

endif()

#very flimsy but it works so whatever
add_custom_target(run
  COMMAND ${CMAKE_SOURCE_DIR}/build/test/main.exe
  WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
)

add_subdirectory(test)
add_subdirectory(library)

