CC = g++
# CC = clang++
CFLAGS = -g -Wall -Wextra -Wcast-qual -Wconversion-null -Wformat-security -Wmissing-declarations -Woverlength-strings -Wpointer-arith -Wundef -Wunused-local-typedefs -Wunused-result -Wvarargs -Wvla -Wwrite-strings -DNOMINMAX -Werror -fno-omit-frame-pointer -std=c++17
PROFILE_FLAGS= -pg
LDFLAGS = -g
IFLAGS = -I/usr/include/SDL2/ -Isrc/
LIBS = -lGL -lGLU -lSDL2 -lSDL2_image -lSDL2_ttf
MACROS = -DGL_GLEXT_PROTOTYPES
#ASAN_FLAGS = -fsanitize=memory -fno-omit-frame-pointer -fsanitize-recover=memory

SRC = ${wildcard src/*.cc} ${wildcard src/**/*.cc} ${wildcard src/**/**/*.cc} ${wildcard src/**/**/**/*.cc}
OBJ = $(SRC:.cc=.o)
BIN = bin

.PHONY: all clean

run: all
	$(BIN)/game

all: dirs game

dirs:
	mkdir -p $(BIN)

game: $(OBJ)
	$(CC) $(LDFLAGS) $(ASAN_FLAGS) -o $(BIN)/game $^ $(LIBS)

%.o: %.cc
	$(CC) -o $@ -c $< $(CFLAGS) $(IFLAGS) $(MACROS)

clean:
	rm -rf $(OBJ) $(BIN)
