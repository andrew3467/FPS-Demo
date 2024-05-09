cmake_minimum_required(VERSION 3.27)
project(Engine)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(external/glfw)
include_directories(external/glfw/include)
add_compile_definitions(GLFW_INCLUDE_NONE)

set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glad)
include_directories(external/glad/include)

add_subdirectory(external/glm)
include_directories(external/glm)

#stb image
file(GLOB_RECURSE STB_SRC external/stbimage/*)
include_directories(external/stbimage/include)

# assimp
add_subdirectory(external/assimp)
include_directories(external/assimp/include)
set(ASSIMP_BUILD_TESTS OFF)

# ImGui
add_subdirectory(external/imgui)
include_directories(external/imgui)


include_directories(src/Engine)

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS src/*.h)

add_library(
        Engine
        ${SOURCES}
        ${HEADERS}
        ${STB_SRC}
)

target_link_libraries(
        Engine
        PUBLIC
        glfw
        glad
        glm
        assimp
        ImGui
)
