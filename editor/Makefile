CC = clang++
CFLAGS = -g -Wall -Wextra -Wcast-qual -Wconversion-null -Wformat-security -Wmissing-declarations -Woverlength-strings -Wpointer-arith -Wundef -Wunused-local-typedefs -Wunused-result -Wvarargs -Wvla -Wwrite-strings -DNOMINMAX -Werror -fno-omit-frame-pointer -std=c++17
INCLUDE = -I../ -I/usr/include/SDL2/
LIBS = -lomega -L../bin/static/

SRC = ${wildcard *.cpp}
OBJ = $(SRC:.cpp=.o)

.PHONY: all clean

all: $(OBJ)
	$(CC) -o editor $^ $(LIBS)

%.o: %.cpp
	$(CC) -o $@ -c $< $(INCLUDE) $(CFLAGS)

clean:
	rm -rf $(OBJ) editor
