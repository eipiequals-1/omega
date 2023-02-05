CC = clang++
CFLAGS = -g -Wall -Wextra -Wcast-qual -Wconversion-null -Wformat-security -Wmissing-declarations -Woverlength-strings -Wpointer-arith -Wundef -Wunused-local-typedefs -Wunused-result -Wvarargs -Wvla -Wwrite-strings -DNOMINMAX -Werror -fno-omit-frame-pointer -std=c++20 -fPIC
PROFILE_FLAGS= -pg
LDFLAGS = -g
INCLUDE = -I/usr/include/SDL2/ -I. -I./lib/glad/include
LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -ltinyxml2 -lbox2d -lassimp
MACROS = 
OPT = -O3

BIN = bin
SRC = ${wildcard omega/*.cpp} ${wildcard omega/**/*.cpp} ${wildcard omega/**/**/*.cpp}
OBJ = $(patsubst %.cpp, $(BIN)/%.o, $(SRC)) # (from, to, string)
DLIB = $(BIN)/libomega.so
SLIB = $(BIN)/static/libomega.a
# < is first dep, ^ is all dependencies, @ is left of colon
LIBS += lib/imgui/bin/libimgui.so lib/map/bin/libtmxparser.so lib/stb/bin/libstb.so lib/glad/bin/libglad.so

.PHONY: clean

all:
	@echo "Available targets:"
	@echo "clean                 Clean all intermediate files."
	@echo "static_lib            Build - static library"
	@echo "lib                   Build - shared object file"

static_lib: deps $(SLIB)
lib: deps $(DLIB)

deps:
	cd lib/imgui/ && make
	cd lib/map/ && make
	cd lib/stb/ && make
	cd lib/glad/ && make

$(SLIB): $(OBJ)
	mkdir -p $(@D)
	ar rcs $@ $(OBJ)

$(DLIB): $(OBJ)
	mkdir -p $(@D)
	$(CC) -o $@ -shared $^ $(LIBS) $(OPT) $(LIBS)

$(BIN)/%.o: %.cpp
	mkdir -p $(@D)
	$(CC) -o $@ -c $< $(CFLAGS) $(INCLUDE) $(MACROS) $(OPT)

clean:
	rm -rf $(BIN)
