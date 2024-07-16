cmake_minimum_required(VERSION 3.5)

project(libtmx-parser)

file(GLOB_RECURSE SRC
    "*.h"
    "*.cpp"
)

set (CMAKE_CXX_FLAGS "-std=c++20")

add_library(${PROJECT_NAME} SHARED ${SRC})
