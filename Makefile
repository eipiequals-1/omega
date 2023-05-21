CC = clang++

EMCC = emcc
EMCCFLAGS = -s USE_SDL=2
EMCCFLAGS += -s USE_SDL_IMAGE=2
EMCCFLAGS += -s SDL2_IMAGE_FORMATS='["png"]'
EMCCFLAGS += -s USE_SDL_MIXER=2
EMCCFLAGS += -s USE_SDL_TTF=2

CFLAGS = -Wall -Wextra -Wcast-qual -Wconversion-null -Wformat-security
CFLAGS += -Wmissing-declarations -Woverlength-strings -Wpointer-arith -Wundef
CFLAGS += -Wunused-local-typedefs -Wunused-result -Wvarargs -Wvla
CFLAGS += -Wwrite-strings -DNOMINMAX -Werror -fno-omit-frame-pointer
CFLAGS += -std=c++20 -fPIC

OPT = -O3

PROFILE_FLAGS= -pg
LDFLAGS = -g

INCLUDE = -I/usr/include/SDL2/ -I. -I./lib/glad/include

LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
LIBS += -ltinyxml2 -lbox2d -lassimp
LIBS += lib/imgui/bin/libimgui.so lib/map/bin/libtmxparser.so lib/stb/bin/libstb.so lib/glad/bin/libglad.so

BIN = bin
SRC = ${wildcard omega/*.cpp} ${wildcard omega/**/*.cpp} ${wildcard omega/**/**/*.cpp}
OBJ = $(patsubst %.cpp, $(BIN)/%.o, $(SRC)) # (from, to, string)

DLIB = $(BIN)/libomega.so
SLIB = $(BIN)/static/libomega.a
# < is first dep, ^ is all dependencies, @ is left of colon

.PHONY: clean

all:
	@echo "Available targets:"
	@echo "linux                 Build - shared and static object files"
	@echo "wasm                  Build - static emscripten compiled library"

linux: deps $(SLIB) $(DLIB)

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
	cd lib/imgui/ && make clean
	cd lib/map/ && make clean
	cd lib/stb/ && make clean
	cd lib/glad/ && make clean

