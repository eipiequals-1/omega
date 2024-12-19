SET (CMAKE_CXX_FLAGS "-Wall -Wextra -Wcast-qual -Wconversion-null -Wformat-security \
-Wmissing-declarations -Woverlength-strings -Wpointer-arith -Wundef \
-Wunused-local-typedefs -Wunused-result -Wvarargs -Wvla \
-Wwrite-strings -DNOMINMAX -fno-omit-frame-pointer \
-std=c++20 -fPIC")
target_compile_options(${PROJECT_NAME} INTERFACE ${CMAKE_CXX_FLAGS})
