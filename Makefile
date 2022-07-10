CC = g++
CFLAGS = -g -Wall -Wextra -Wcast-qual -Wconversion-null -Wformat-security -Wmissing-declarations -Woverlength-strings -Wpointer-arith -Wundef -Wunused-local-typedefs -Wunused-result -Wvarargs -Wvla -Wwrite-strings -DNOMINMAX -Werror -fno-omit-frame-pointer -std=c++17 -fPIC
PROFILE_FLAGS= -pg
LDFLAGS = -g
INCLUDE = -I/usr/include/SDL2/ -I.
LIBS = -lGL -lGLU -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -ltinyxml2 -lBox2D
MACROS = -DGL_GLEXT_PROTOTYPES
OPT = -O3

BIN = bin
SRC = ${wildcard omega/*.cpp} ${wildcard omega/**/*.cpp} ${wildcard omega/**/**/*.cpp}
OBJ = $(patsubst %.cpp, $(BIN)/%.o, $(SRC)) # (from, to, string)

# < is first dep, ^ is all dependencies, @ is left of colon

.PHONY: all clean

all: dirs lib

dirs:
	mkdir -p $(BIN)
	mkdir -p $(BIN)/static
	cp -R omega/ $(BIN)/
	find ./bin/ -name *.cpp* | xargs rm
	find ./bin/ -name *.h* | xargs rm
	find ./bin/ -name *BUILD* | xargs rm

lib: $(OBJ)
	$(CC) -o $(BIN)/libomega.so -shared $^ $(LIBS) $(OPT)
	ar rcs  $(BIN)/static/libomega.a $(BIN)/libomega.so

$(BIN)/%.o: %.cpp %.h
	$(CC) -o $@ -c $< $(CFLAGS) $(INCLUDE) $(MACROS) $(OPT)

clean:
	rm -rf $(BIN)
