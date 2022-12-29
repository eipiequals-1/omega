CC = clang++
CFLAGS = -g -Wall -Wextra -Wcast-qual -Wconversion-null -Wformat-security -Wmissing-declarations -Woverlength-strings -Wpointer-arith -Wundef -Wunused-local-typedefs -Wunused-result -Wvarargs -Wvla -Wwrite-strings -DNOMINMAX -Werror -fno-omit-frame-pointer -std=c++17
INCLUDE = -I../ -I/usr/include/SDL2/
#LIBS = ../bin/static/libomega.a
LDPATH = ../bin/static/
MACROS = -DGL_GLEXT_PROTOTYPES

SRC = ${wildcard *.cpp} ${wildcard panels/*.cpp}
OBJ = $(SRC:.cpp=.o)

.PHONY: all clean

all: editor

editor: $(OBJ)
	$(CC) -o $@ $^ -L $(LDPATH) -lomega -lGL -lGLU -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -ltinyxml2 -lbox2d -lassimp -ldl $(MACROS)

%.o: %.cpp
	$(CC) -o $@ -c $< $(INCLUDE) $(CFLAGS) $(MACROS)

clean:
	rm -rf $(OBJ) editor
