CC = clang++

CFLAGS = -Wall -Wextra -Wcast-qual -Wconversion-null -Wformat-security
CFLAGS += -Wmissing-declarations -Woverlength-strings -Wpointer-arith -Wundef
CFLAGS += -Wunused-local-typedefs -Wunused-result -Wvarargs -Wvla
CFLAGS += -Wwrite-strings -DNOMINMAX -Werror -fno-omit-frame-pointer
CFLAGS += -std=c++20 -fPIC

OPT = -O3

LDFLAGS = -g
INCLUDE = -I./include/ -I../../

BIN = bin
SRC = src/glad.cpp
OBJ = $(patsubst %.cpp, $(BIN)/%.o, $(SRC)) # (from, to, string)
DLIB = $(BIN)/libglad.so
# < is first dep, ^ is all dependencies, @ is left of colon

.PHONY: all clean

all: lib 

lib: $(DLIB)

$(DLIB): $(OBJ)
	mkdir -p $(@D)
	$(CC) -o $@ -shared $^ $(LIBS) $(OPT)

$(BIN)/%.o: %.cpp
	mkdir -p $(@D)
	$(CC) -o $@ -c $< $(CFLAGS) $(INCLUDE) $(MACROS) $(OPT)

clean:
	rm -rf $(BIN)
