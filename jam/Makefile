CC = emcc

BIN = build

SRC = $(shell find . -name "*.cpp")
OBJ = $(patsubst %.cpp, $(BIN)/%.o, $(SRC))

ASSET_PATH = assets/

CFLAGS = -Wall -Wextra -Wcast-qual -Wconversion-null -Wformat-security
CFLAGS += -Wmissing-declarations -Woverlength-strings -Wpointer-arith -Wundef
CFLAGS += -Wunused-local-typedefs -Wunused-result -Wvarargs -Wvla
CFLAGS += -Wwrite-strings -DNOMINMAX -fno-omit-frame-pointer
CFLAGS += -std=c++20 -fPIC

INCFLAGS += -I../
INCFLAGS += -I../lib/
INCFLAGS += -I.


LIBS = ../build/libomega.a ../build/lib/imgui/libimgui.so

OPT = -O2

EMCCFLAGS = 
EMCCFLAGS += -s INITIAL_MEMORY=256MB
EMCCFLAGS += -s ALLOW_MEMORY_GROWTH
EMCCFLAGS += --preload-file $(ASSET_PATH)
EMCCFLAGS += -s USE_SDL=2
EMCCFLAGS += -s USE_SDL_IMAGE=2
EMCCFLAGS += -s SDL2_IMAGE_FORMATS='["png"]'
EMCCFLAGS += -s USE_SDL_MIXER=2
EMCCFLAGS += -s USE_SDL_TTF=2
EMCCFLAGS += -s FULL_ES3
EMCCFLAGS += --shell-file assets/emscripten/shell-debug.html

OUT_WEB = $(BIN)/index.html

all: dirs build-web

dirs:
	mkdir -p $(BIN)

$(BIN)/%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS) $(INCFLAGS) $(OPT)

build-web: dirs $(OBJ)
	$(CC) -o $(OUT_WEB) $(OBJ) $(LIBS) $(EMCCFLAGS)

clean:
	rm -rf $(BIN)
