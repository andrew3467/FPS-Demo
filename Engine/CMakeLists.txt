cmake_minimum_required(VERSION 3.27)
project(FPS_Engine)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(external/glfw)
include_directories(external/glfw/include)
add_compile_definitions(GLFW_INCLUDE_NONE)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glad)
include_directories(external/glad/include)


include_directories(src/engine)

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS src/*.h)

add_library(
        FPS_Engine
        ${SOURCES}
        ${HEADERS}
)

target_link_libraries(
        FPS_Engine
        PUBLIC
        glfw
        glad
)
