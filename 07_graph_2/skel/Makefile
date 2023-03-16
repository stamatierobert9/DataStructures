CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=c99
DEBUG=-g -ggdb -O0 -march=native

build: Test

Test: src/Test.o src/Queue.o src/LinkedList.o src/ListGraph.o src/Stack.o
	$(CC) $(CFLAGS) $(DEBUG) $^ -o $@

src/ListGraph.o: src/ListGraph.c
	$(CC) $(CFLAGS) $(DEBUG) $^ -c -o $@

src/LinkedList.o: src/LinkedList.c
	$(CC) $(CFLAGS) $(DEBUG) $^ -c -o $@

src/Queue.o: src/Queue.c
	$(CC) $(CFLAGS) $(DEBUG)  $^ -c -o $@

src/Stack.o: src/Stack.c
	$(CC) $(CFLAGS) $(DEBUG)  $^ -c -o $@

src/Test.o: src/Test.c
	$(CC) $(CFLAGS) $(DEBUG)  $^ -c -o $@

run: Test
	./$<

clean:
	rm -f src/*.o Test