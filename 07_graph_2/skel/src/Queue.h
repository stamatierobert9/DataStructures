#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdbool.h>

typedef struct queue_t queue_t;
struct queue_t
{
	/* Dimensiunea maxima a cozii */
	unsigned int max_size;
	/* Dimensiunea cozii */
	unsigned int size;
	/* Dimensiunea in octeti a tipului de date stocat in coada */
	unsigned int data_size;
	/* Indexul de la care se vor efectua operatiile de front si dequeue */
	unsigned int read_idx;
	/* Indexul de la care se vor efectua operatiile de enqueue */
	unsigned int write_idx;
	/* Bufferul ce stocheaza elementele cozii */
	void **buff;
};

queue_t *
q_create(unsigned int data_size, unsigned int max_size);

unsigned int
q_get_size(queue_t *q);

unsigned int
q_is_empty(queue_t *q);

void *
q_front(queue_t *q);

bool
q_dequeue(queue_t *q);

bool
q_enqueue(queue_t *q, void *new_data);

void
q_clear(queue_t *q);

void
q_free(queue_t *q);

#endif  /* QUEUE_H_ */
