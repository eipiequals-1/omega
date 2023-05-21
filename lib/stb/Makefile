CC = emcc
CFLAGS = -std=c++20 -fPIC
OPT = -O3

BIN = bin
SRC = ${wildcard *.cpp}
OBJ = $(patsubst %.cpp, $(BIN)/%.o, $(SRC)) # (from, to, string)
DLIB = $(BIN)/libstb.so
# < is first dep, ^ is all dependencies, @ is left of colon

.PHONY: all clean

all: lib

lib: $(DLIB)

$(DLIB): $(OBJ)
	mkdir -p $(@D)
	$(CC) -o $@ -shared $^ $(LIBS) $(OPT)

$(BIN)/%.o: %.cpp
	mkdir -p $(@D)
	$(CC) -o $@ -c $< $(CFLAGS) $(INCLUDE) $(OPT)

clean:
	rm -rf $(BIN)
