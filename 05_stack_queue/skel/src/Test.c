#include <stdio.h>
#include <stdlib.h>

#include "Queue.h"
#include "Stack.h"

int
main(void)
{
	queue_t *q;
	stack_t *st = st_create(sizeof(int));
	int numbers[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int crt_val;

	printf("-------------------------------- Test stack --------------------------------\n");
	st_push(st, &numbers[10]);

	/* Test push & size */
	printf(
		"#1:\nOutput: size: %d\nOutput asteptat: size: 1\n",
		st_get_size(st)
	);

	/* Test peek */
	crt_val = *(int *)st_peek(st);
	printf("#2:\nOutput: %d\nOutput asteptat: 10\n", crt_val);

	/* Test pop */
	crt_val = *(int *)st_peek(st);
	st_pop(st);
	printf(
		"#3:\nOutput: value: %d size: %d\nOutput asteptat: value: 10 size: 0\n",
		crt_val,
		st_get_size(st)
	);

	st_push(st, &numbers[9]);
	st_push(st, &numbers[8]);
	st_push(st, &numbers[7]);

	/* Test multiple pushes */
	printf(
		"#4:\nOutput: size: %d top elem: %d\nOutput asteptat: size: 3 top elem: 7\n",
		st_get_size(st),
		*(int *)st_peek(st)
	);

	/* Test multiple pops */
	printf("#5:\nOutput: ");
	while (!st_is_empty(st)) {
		printf("%d ", *(int *)st_peek(st));
		st_pop(st);
	}
	printf("size: %d", st_get_size(st));
	printf("\nOutput asteptat: 7 8 9 size: 0\n");

	st_free(st);

	printf("\n\n-------------------------------- Test queue --------------------------------\n");
	q = q_create(sizeof(int), 3);
	q_enqueue(q, &numbers[5]);

	/* Test q_enqueue & size */
	printf(
		"#1:\nOutput: size: %d\nOutput asteptat: size: 1\n",
		q_get_size(q)
	);

	/* Test q_front */
	crt_val = *(int *)q_front(q);
	printf("#2:\nOutput: %d\nOutput asteptat: 5\n", crt_val);

	/* Test q_dequeue */
	crt_val = *(int *)q_front(q);
	q_dequeue(q);
	printf(
		"#3:\nOutput: value: %d size: %d\nOutput asteptat: value: 5 size: 0\n",
		crt_val,
		q_get_size(q)
	);

	q_enqueue(q, &numbers[2]);
	q_enqueue(q, &numbers[3]);
	q_enqueue(q, &numbers[4]);

	/* Test multiple pushes */
	printf(
		"#4:\nOutput: size: %d top elem: %d\nOutput asteptat: size: 3 q_front elem: 2\n",
		q_get_size(q),
		*(int *)q_front(q)
	);

	/* Test enqueue above limit */
	printf(
		"#5\nOutput: q_enqueue result: %d\nOutput asteptat: q_enqueue result: 0\n",
		q_enqueue(q, &numbers[5])
	);

	/* Test multiple pops */
	printf("#6:\nOutput: ");
	while (!q_is_empty(q)) {
		printf("%d ", *(int *)q_front(q));
		q_dequeue(q);
	}
	printf("size: %d", q_get_size(q));
	printf("\nOutput asteptat: 2 3 4 size: 0\n");

	/* Test dequeue when size is 0 */
	printf(
		"#7\nOutput: q_dequeue result: %d\nOutput asteptat: q_dequeue result: 0\n",
		q_dequeue(q)
	);

	q_free(q);
	return 0;
}
