cmake_minimum_required(VERSION 3.27)
project(FPS_Demo)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(Demo)
include_directories(Demo/src)

add_executable(FPS_Demo main.cpp)


target_link_libraries(
        FPS_Demo
        PRIVATE
        Demo
)