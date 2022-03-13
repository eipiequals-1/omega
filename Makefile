CC = g++
CFLAGS = -Wall -Wextra -Wcast-qual -Wconversion-null -Wformat-security -Wmissing-declarations -Woverlength-strings -Wpointer-arith -Wundef -Wunused-local-typedefs -Wunused-result -Wvarargs -Wvla -Wwrite-strings -DNOMINMAX -fno-omit-frame-pointer -std=c++17 -fPIC -Werror
PROFILE_FLAGS= -pg
LDFLAGS = -g
IFLAGS = -I/usr/include/SDL2/ -Isrc/
LIBS = -lGL -lGLU -lSDL2 -lSDL2_image -lSDL2_ttf
MACROS = -DGL_GLEXT_PROTOTYPES
#ASAN_FLAGS = -fsanitize=memory -fno-omit-frame-pointer -fsanitize-recover=memory
