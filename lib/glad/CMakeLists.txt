cmake_minimum_required(VERSION 3.2)

project(glad)

file(GLOB_RECURSE SRC
    "include/*.h"
    "src/*.cpp"
)

include_directories("include/")

set (CMAKE_CXX_FLAGS "-std=c++20")

add_library(${PROJECT_NAME} SHARED ${SRC})
