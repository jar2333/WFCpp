cmake_minimum_required(VERSION 3.5)
project(wfcpp VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#add libraries
# add_subdirectory(external/raylib)

# add a target to generate API documentation with Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
# set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    add_custom_target(doc ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen" 
        VERBATIM
    )
endif(DOXYGEN_FOUND)

add_library(${PROJECT_NAME} 
    STATIC src/Extractor.cpp src/Solver.cpp src/Synthesizer.cpp
    )

#makes wfcpp's include dir accessible to itself and outsiders (via the proj name wfcpp)
target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
    #library names
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC

    PRIVATE
    #library names
)

