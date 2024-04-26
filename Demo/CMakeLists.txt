cmake_minimum_required(VERSION 3.27)
project(Demo)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(../Engine ../bin)
include_directories(../Engine/src)

include_directories(src/demo)

include_directories(../Engine/external/glad/include)

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS src/*.h)

add_library(
        Demo
        ${SOURCES}
        ${HEADERS}
)

target_link_libraries(
        Demo
        PUBLIC
        FPS_Engine
)
