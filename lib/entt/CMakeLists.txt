cmake_minimum_required(VERSION 3.2)

project(entt)

file(GLOB_RECURSE SRC
    "*.hpp"
)

set (CMAKE_CXX_FLAGS "-std=c++20")

add_library(${PROJECT_NAME} SHARED ${SRC})

set_target_properties(entt PROPERTIES LINKER_LANGUAGE CXX)
