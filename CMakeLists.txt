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
include_directories("lib")

set (CMAKE_CXX_STANDARD 20)

# dependencies
add_subdirectory(lib)

target_include_directories(${PROJECT_NAME}
    PUBLIC lib/SDL/include/
    PUBLIC lib/SDL_image/include/
    PUBLIC lib/SDL_mixer/include/
    PUBLIC lib/box2d/include/
    PUBLIC lib/glad/include/
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    lib
)

