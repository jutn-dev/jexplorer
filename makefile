CC=g++
Cflags=-g -I include -Wall -lncurses

SRC=src
SRCS=$(wildcard $(SRC)/*.cpp)

OBJ=obj
OBJS=$(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRCS))

BINDIR=bin
BIN=$(BINDIR)/jexplorer


all: $(BIN)

$(BIN): $(OBJS)
	$(CC)  $(OBJS) -o $@ $(Cflags)

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CC) -c $< -o $@  $(Cflags)

clean:
	rm $(OBJ)/* $(BIN)
install:
	mkdir bin
	mkdir obj
	make
	cp $(BIN) /usr/local/bin
	chmod +x /usr/local/bin/jexplorer

