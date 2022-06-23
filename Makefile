CC = g++
CFLAGS = -g -Wall -Wextra -Wcast-qual -Wconversion-null -Wformat-security -Wmissing-declarations -Woverlength-strings -Wpointer-arith -Wundef -Wunused-local-typedefs -Wunused-result -Wvarargs -Wvla -Wwrite-strings -DNOMINMAX -Werror -fno-omit-frame-pointer -std=c++17 -fPIC
PROFILE_FLAGS= -pg
LDFLAGS = -g
INCLUDE = -I/usr/include/SDL2/ -I.
LIBS = -lGL -lGLU -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -ltinyxml2
MACROS = -DGL_GLEXT_PROTOTYPES
OPT = -O3

SRC = ${wildcard libGL2D/*.cc} ${wildcard libGL2D/**/*.cc} ${wildcard libGL2D/**/**/*.cc}
OBJ = $(SRC:.cc=.o)
BIN = bin

# < is first dep, ^ is all dependencies, @ is left of colon

.PHONY: all clean

all: dirs lib

dirs:
	mkdir -p $(BIN)
	mkdir -p $(BIN)/static

lib: $(OBJ)
	$(CC) -o $(BIN)/libGL2D.so -shared $^ $(LIBS) $(OPT)
	ar rcs  $(BIN)/static/libGL2D.a $(BIN)/libGL2D.so

%.o: %.cc %.h
	$(CC) -o $@ -c $< $(CFLAGS) $(INCLUDE) $(MACROS) $(OPT)

clean:
	rm -rf $(OBJ) $(BIN)
