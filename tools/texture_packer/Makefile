CC = g++
CFLAGS = -Wall -Wextra -Wcast-qual -Wconversion-null -Wformat-security -Wmissing-declarations -Woverlength-strings -Wpointer-arith -Wundef -Wunused-local-typedefs -Wunused-result -Wvarargs -Wvla -Wwrite-strings -DNOMINMAX -Werror -fno-omit-frame-pointer -std=c++17
LIB_FLAGS = -lSDL2 -lSDL2_image
INCLUDE = -I/usr/include/SDL2/ -I..
SRC = ${wildcard *.cc}
OBJ = $(SRC:.cc=.o)
BIN = bin


.PHONY: all clean

run: all
	$(BIN)/texture_packer

dirs:
	mkdir -p $(BIN)

all: dirs texture_packer

texture_packer: $(OBJ)
	$(CC) -o $(BIN)/texture_packer $^ $(LIB_FLAGS) $(INCLUDE) $(CFLAGS)

%.o: %.cc
	$(CC) -o $@ -c $< $(CFLAGS) $(INCLUDE)

clean:
	rm -rf $(BIN) $(OBJ)