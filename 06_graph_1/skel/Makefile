CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=c99
DEBUG=-g -ggdb -O0 -march=native

build: Test

Test: src/Test.o src/Queue.o src/Stack.o src/LinkedList.o src/MatrixGraph.o src/ListGraph.o
	$(CC) $(CFLAGS) $(DEBUG) $^ -o $@


src/MatrixGraph.o: src/MatrixGraph.c src/MatrixGraph.h
	$(CC) $(CFLAGS) $(DEBUG) -c $< -o $@

src/ListGraph.o: src/ListGraph.c src/ListGraph.h
	$(CC) $(CFLAGS) $(DEBUG) -c $< -o $@

src/Queue.o: src/Queue.c src/Queue.h
	$(CC) $(CFLAGS) $(DEBUG) -c $< -o $@

src/Stack.o: src/Stack.c src/Stack.h
	$(CC) $(CFLAGS) $(DEBUG) -c $< -o $@

src/LinkedList.o: src/LinkedList.c src/LinkedList.h
	$(CC) $(CFLAGS) $(DEBUG) -c $< -o $@

src/Test.o: src/Test.c
	$(CC) $(CFLAGS) $(DEBUG) -c $^ -o $@

run:
	./Test

clean:
	rm -f src/*.o Test
