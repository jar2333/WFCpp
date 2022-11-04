cmake_minimum_required(VERSION 3.5)
project(wfcpp VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#add libraries
# add_subdirectory(external/raylib)

add_library(${PROJECT_NAME} STATIC src/main.cpp) #src/LoadingState.cpp)

#makes crawler-engine's include dir accessible to itself and outsiders (via the proj name crawler-engine)
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

