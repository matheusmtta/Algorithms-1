CC=g++
CFLAGS=-Wall -Wextra
EXEC=./tp1
TMPOUT=tp1.testresult

.PHONY: all build test clean

all: build test clean

build:
	$(CC) $(CFLAGS) -c src/game.cpp -o game.o
	$(CC) $(CFLAGS) src/main.cpp game.o -o $(EXEC)

clean:
	rm -rf game.o
