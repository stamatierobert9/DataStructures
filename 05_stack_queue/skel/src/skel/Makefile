CC=gcc
CFLAGS=-Wall -Wextra -pedantic
DEBUG=-g -ggdb -O0 -march=native

build: Stack Queue

Stack: Stack.o

Queue: Queue.o

Queue.o: Queue.c
	$(CC) $(CFLAGS) $(DEBUG) $^ -c -o $@

Stack.o: Stack.c
	$(CC) $(CFLAGS) $(DEBUG) $^ -c -o $@

run_stack:
	./Stack

run_queue:
	./Queue

clean:
	rm -rf Stack
	rm -rf Queue
	rm -rf *.o
