/**
 * SD, 2021
 * 
 * Lab #9, BST & Heap
 * 
 * Heap structure and function definitions
 */

#ifndef __HEAP_H_
#define __HEAP_H_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define TEAM_NAME_LEN   30

#define GO_UP(x)        (((x) - 1) >> 1)
#define GO_LEFT(x)      (((x) << 1) + 1)
#define GO_RIGHT(x)     (((x) << 1) + 2)

typedef struct team_t team_t;
struct team_t {
    char        *name;
    int         score;
};

typedef struct heap_t heap_t;
struct heap_t {
    /* heap elements */
    team_t **arr;

    int size, capacity;

    /* function used for sorting the keys */
    int	(*cmp)(const team_t *key1, const team_t *key2);
};

/**
 * Alloc memory for a new heap
 * @cmp_f: pointer to a function used for sorting
 * @return: pointer to the newly created heap
 */
heap_t *heap_create(int (*cmp_f) (const team_t *, const team_t *));

/**
 * Insert a new element in a heap
 * @heap: the heap where to insert the new element
 * @team: the team to be inserted in heap
 */
void heap_insert(heap_t *heap, team_t *team);

/**
 * Get the top element
 * @heap: the heap where to search for the top element
 * @return: the top element
 */
team_t *heap_top(heap_t *heap);

/**
 * Remove the top element
 */
void heap_pop(heap_t *heap);

/**
 * Check if the heap is empty
 * @heap: the heap to be checked
 * @return: 1 if the heap is empty else 0
 */
int heap_empty(heap_t *heap);

/**
 * Free a heap
 * @heap: the heap to be freed
 */
void heap_free(heap_t *heap);

#endif
