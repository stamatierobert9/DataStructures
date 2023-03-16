CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=c99
DEBUG=-g -ggdb -O0 -march=native

build: Test

Test: src/Test.o src/Queue.o src/Stack.o src/LinkedList.o
	$(CC) $(CFLAGS) $(DEBUG) $^ -o $@

src/Queue.o: src/Queue.c
	$(CC) $(CFLAGS) $(DEBUG) $^ -c -o $@

src/Stack.o: src/Stack.c
	$(CC) $(CFLAGS) $(DEBUG) $^ -c -o $@

src/LinkedList.o: src/LinkedList.c
	$(CC) $(CFLAGS) $(DEBUG) $^ -c -o $@

src/Test.o: src/Test.c
	$(CC) $(CFLAGS) $(DEBUG) src/Test.c -c -o src/Test.o

run:
	./Test

clean:
	rm -f src/*.o Test