#include <stdlib.h>

#include "Stack.h"
#include "utils.h"

stack_t*
st_create(unsigned int data_size)
{
	stack_t* st = malloc(sizeof(*st));
	DIE(!st, "malloc st failed");
	st->list = ll_create(data_size);
	DIE(!st->list, "malloc list failed");

	return st;
}

unsigned int
st_get_size(stack_t* st)
{
	if (!st || !st->list)
		return 0;
	return st->list->size;
}

/*
 * Intoarce 1 daca stiva este goala si 0 in caz contrar.
 */
unsigned int
st_is_empty(stack_t* st)
{
	/* TODO */
	return !st || !st->list || !st->list->size;
}

void*
st_peek(stack_t* st)
{
	/* TODO */
	if (!st || !st->list || !st->list->size)
		return NULL;

	return st->list->head->data;
}

void
st_pop(stack_t* st)
{
	/* TODO */
	if (!st || !st->list)
		return;

	ll_remove_nth_node(st->list, 0);
}

void
st_push(stack_t* st, void* new_data)
{
	/* TODO */
	if (!st || !st->list)
		return;

	ll_add_nth_node(st->list, 0, new_data);
}

void
st_clear(stack_t* st)
{
	/* TODO */
	if (!st || !st->list)
		return;

	ll_free(&st->list);
}

void
st_free(stack_t* st)
{
	/* TODO */
	if (!st || !st->list)
		return;

	ll_free(&st->list);
	free(st);
}
