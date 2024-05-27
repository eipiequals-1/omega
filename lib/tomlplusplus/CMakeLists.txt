cmake_minimum_required(VERSION 3.2)

project(tomlplusplus)

file(GLOB_RECURSE SRC
    "*.hpp"
    "*.cpp"
)

set (CMAKE_CXX_FLAGS "-std=c++20")

add_library(${PROJECT_NAME} SHARED ${SRC})
