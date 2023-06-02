cmake_minimum_required(VERSION 3.2)

project(imgui)

file(GLOB_RECURSE SRC
    "*.h"
    "*.cpp"
)

set (CMAKE_CXX_FLAGS "-std=c++20")

add_library(${PROJECT_NAME} SHARED ${SRC})

target_link_libraries(${PROJECT_NAME}
    SDL2
    SDL2_image
)
