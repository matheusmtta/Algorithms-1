CC=g++
CFLAGS=-Wall -Wextra
EXEC=./tp1
TMPOUT=tp1.testresult

.PHONY: all build test clean

all: build test clean

build:
	$(CC) $(CFLAGS) -c src/list.cpp -o list.o
	$(CC) $(CFLAGS) -c src/measures.cpp -o measures.o
	$(CC) $(CFLAGS) src/main.cpp list.o measures.o -o $(EXEC)

test: $(build)
	@bash run_tests.sh $(EXEC) $(TMPOUT)

clean:
	rm -rf list.o node.o
