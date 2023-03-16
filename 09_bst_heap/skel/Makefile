CC := gcc
CFLAGS := -std=c99 -g -Wall -Wextra

TASKS := task1 task2
SRCDIR := src

ALL_SRCS := $(wildcard $(SRCDIR)/*.c)
OBJFILES := $(patsubst $(SRCDIR)/%.c,%.o,$(ALL_SRCS))

.PHONY: build clean

build: $(TASKS)

run_task1: task1
	./task1

run_task2: task2
	./task2

task1: bst.o task1.o
	$(CC) $(CFLAGS) -o $@ $^

task2: heap.o task2.o
	$(CC) $(CFLAGS) -o $@ $^

%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJFILES) $(TASKS)
