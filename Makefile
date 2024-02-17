#!/bin/sh

CFLAGS = --target=wasm32 -fno-builtin --no-standard-libraries -std=c++17 -Wall -Wextra -Wshadow -pedantic
LDFLAGS = --no-entry --export-all --allow-undefined
CC := clang
LD := wasm-ld

SRC = src/main.cc src/gl.cc
OBJ = src/main.o src/gl.o
INC = src/u.hh src/gl.hh
BIN = index.wasm

.PHONY: all
all: $(BIN)

%.o: %.cc
	$(CC) $(CFLAGS) -c -o $@ $<

$(BIN): $(OBJ) $(INC)
	$(LD) $(LDFLAGS) $(OBJ) -o $(BIN)

.PHONY: clean
clean:
	rm $(BIN) $(OBJ)
