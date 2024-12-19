cmake_minimum_required(VERSION 3.5)

project(omega)

file(GLOB_RECURSE SRC
     "omega/*.hpp"
     "omega/*.cpp"
)

add_library(${PROJECT_NAME} SHARED ${SRC})

include(cmake/CompilerWarnings.cmake)

SET (CMAKE_CXX_FLAGS_DEBUG          "-g")
SET (CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELEASE        "-O4 -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")

include_directories(".")

set (CMAKE_CXX_STANDARD 20)


# dependencies
find_package(SDL2 REQUIRED)

add_subdirectory(lib/box2d)
add_subdirectory(lib/imgui)
add_subdirectory(lib/glad)
add_subdirectory(lib/stb)
add_subdirectory(lib/libtmx-parser)
add_subdirectory(lib/tomlplusplus)

target_include_directories(${PROJECT_NAME}
    PUBLIC lib/box2d/include/
    PUBLIC lib/glad/include/
    PUBLIC lib/sol2/include/
    PUBLIC lib/tomlplusplus/
    PUBLIC lib/lua/src/
    PUBLIC lib/
)

target_link_libraries(${PROJECT_NAME}
    SDL2
    SDL2_image
    SDL2_ttf
    SDL2_mixer
    box2d
    imgui
    glad
    stb
    libtmx-parser
    tomlplusplus
)
target_link_directories(${PROJECT_NAME}
    PUBLIC lib/box2d/bin/
    PUBLIC lib/imgui/
    PUBLIC lib/glad/
    PUBLIC lib/stb/
    PUBLIC lib/libtmx-parser/
    PUBLIC lib/tomlplusplus/
)
