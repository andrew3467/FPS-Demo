cmake_minimum_required(VERSION 3.27)
project(Application)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(Demo)
include_directories(Demo/src)

add_executable(Application main.cpp)


target_link_libraries(
        Application
        PRIVATE
        Demo
)