CC=g++
Cflags=-g

LIBS=-lncurses

SRC=src
SRCS=$(wildcard $(SRC)/*.cpp)

OBJ=obj
OBJS=$(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRCS))

BINDIR=bin
BIN=$(BINDIR)/file

$(BIN): $(OBJS)
	$(CC) $(Cflags) $(OBJS) -o $@ $(LIBS)

$(OBJS): $(SRCS)
	$(CC) $(Cflags) -c $< -o $@

clean:
	rm $(BINDIR)/* $(OBJ)/*
