CC=gcc
CFLAGS=-Wall -Wextra -pedantic
DEBUG=-g -ggdb -O0 -march=native

build: ListGraphImplementation MatrixGraphImplementation ListGraphBFS MatrixGraphDFS

ListGraphImplementation: ListGraphImplementation.o

ListGraphBFS: ListGraphBFS.o

MatrixGraphImplementation: MatrixGraphImplementation.o

MatrixGraphDFS: MatrixGraphDFS.o

ListGraphImplementation.o: ListGraphImplementation.c
	$(CC) $(CFLAGS) $(DEBUG) $^ -c -o $@

MatrixGraphImplementation.o: MatrixGraphImplementation.c
	$(CC) $(CFLAGS) $(DEBUG) $^ -c -o $@

ListGraphBFS.o: ListGraphBFS.c
	$(CC) $(CFLAGS) $(DEBUG) $^ -c -o $@

MatrixGraphDFS.o: MatrixGraphDFS.c
	$(CC) $(CFLAGS) $(DEBUG) $^ -c -o $@

run_lg_implementation:
	./ListGraphImplementation

run_mg_implementation:
	./MatrixGraphImplementation

run_lg_bfs:
	./ListGraphBFS

run_mg_dfs:
	./MatrixGraphImplementation

clean:
	rm -rf ListGraphImplementation
	rm -rf MatrixGraphImplementation
	rm -rf ListGraphBFS
	rm -rf MatrixGraphDFS
	rm -rf *.o
