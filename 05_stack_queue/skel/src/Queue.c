#include <stdlib.h>

#include "Queue.h"
#include "utils.h"

queue_t *
q_create(unsigned int data_size, unsigned int max_size)
{
	/* TODO */
	return NULL;
}

unsigned int
q_get_size(queue_t *q)
{
	/* TODO */
	return 0;
}

/*
 * Intoarce 1 daca stiva este goala si 0 in caz contrar.
 */
unsigned int
q_is_empty(queue_t *q)
{
	/* TODO */
	return 0;
}

void *
q_front(queue_t *q)
{
	/* TODO */
	return NULL;
}

/* Functia intoarce true daca operatia s-a efectuat si false in caz contrar */
bool
q_dequeue(queue_t *q)
{
	/* TODO */
	return false;
}

/* Functia intoarce true daca operatia s-a efectuat si false in caz contrar */
bool
q_enqueue(queue_t *q, void *new_data)
{
	/* TODO */
	return false;
}

void
q_clear(queue_t *q)
{
	/* TODO */
}

void
q_free(queue_t *q)
{
	/* TODO */
}
