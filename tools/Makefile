CC = g++
CFLAGS = -g -Wall -Wextra -Wcast-qual -Wconversion-null -Wformat-security -Wmissing-declarations -Woverlength-strings -Wpointer-arith -Wundef -Wunused-local-typedefs -Wunused-result -Wvarargs -Wvla -Wwrite-strings -DNOMINMAX -Werror -fno-omit-frame-pointer -std=c++17
LIB_FLAGS = -lSDL2 -lSDL2_image
INCLUDE = -I/usr/include/SDL2/
SRC = texture_packer.cc

BIN = bin

.PHONY: all clean

dirs:
	mkdir -p $(BIN)

texture_packer: texture_packer.cc dirs
	$(CC) -o $(BIN)/texture_packer texture_packer.cc $(LIB_FLAGS) $(INCLUDE) $(CFLAGS)

clean:
	rm -rf $(BIN)