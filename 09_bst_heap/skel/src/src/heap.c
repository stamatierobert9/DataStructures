/**
 * SD, 2022
 * 
 * Lab 09 - BST & Heap
 * 
 * Heap implementation
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

/* stupid workaround for lambdachecker input from example */
void cleanup_example_string(char *str) {
	int len = strlen(str);

	if(str[len-2] == '\\') {
		str[len-2] = '\0';
	}
}

/* useful macro for handling error codes */
#define DIE(assertion, call_description)				\
	do {								\
		if (assertion) {					\
			fprintf(stderr, "(%s, %d): ",			\
					__FILE__, __LINE__);		\
			perror(call_description);			\
			exit(errno);					\
		}							\
	} while (0)

#define TEAM_NAME_LEN		30

#define GO_UP(x)		(((x) - 1) >> 1)
#define GO_LEFT(x)		(((x) << 1) + 1)
#define GO_RIGHT(x)		(((x) << 1) + 2)

typedef struct team_t team_t;
struct team_t {
	char *name;
	int score;
};

typedef struct heap_t heap_t;
struct heap_t {
	/* heap elements */
	team_t **arr;

	int size;
	int capacity;

	/* function used for sorting the keys */
	int (*cmp)(const team_t *key1, const team_t *key2);
};

/**
 * Alloc memory for a new heap
 * @cmp_f: pointer to a function used for sorting
 * @return: pointer to the newly created heap
 */
heap_t *heap_create(int (*cmp_f)(const team_t *, const team_t *))
{
	heap_t *heap;

	heap = malloc(sizeof(*heap));
	DIE(heap == NULL, "heap malloc");

	heap->cmp	= cmp_f;
	heap->size	= 0;
	heap->capacity	= 2;
	heap->arr	= malloc(heap->capacity * sizeof(*heap->arr));
	DIE(heap->arr == NULL, "heap->arr malloc");

	return heap;
}

/**
 * Make sure the constraints in the heap are fulfilled at all times during
 * the insertion process.
 * i.e.: You have the place the team in the right position according to
 * the score.
 */
static void __heap_insert_fix(heap_t *heap, int pos)
{
	team_t *tmp_team;
	int p = GO_UP(pos);

	/* TODO */
	if (pos == 0) {
		return;
	}

	if (heap->cmp(heap->arr[pos], heap->arr[p]) < 0) {
		tmp_team = heap->arr[pos];
		heap->arr[pos] = heap->arr[p];
		heap->arr[p] = tmp_team;

		__heap_insert_fix(heap, p);
	}
	
}

/**
 * Insert a new element in a heap
 * @heap: the heap where to insert the new element
 * @team: the team to be inserted in heap
 */
void heap_insert(heap_t *heap, team_t *team)
{
	char *rc;

	heap->arr[heap->size] = malloc(sizeof(**heap->arr));
	DIE(heap->arr[heap->size] == NULL, "heap_insert malloc");

	heap->arr[heap->size]->name = calloc(TEAM_NAME_LEN,
			sizeof(*heap->arr[heap->size]->name));
	DIE(heap->arr[heap->size]->name == NULL, "heap_insert name calloc");

	rc = strncpy(heap->arr[heap->size]->name, team->name,
			TEAM_NAME_LEN - 1);
	DIE(rc != heap->arr[heap->size]->name, "heap_insert name strncpy");
	heap->arr[heap->size]->score = team->score;

	__heap_insert_fix(heap, heap->size);

	heap->size++;
	if (heap->size == heap->capacity) {
		heap->capacity *= 2;

		heap->arr = realloc(heap->arr,
				heap->capacity * sizeof(*heap->arr));
		DIE(heap->arr == NULL, "heap->arr realloc");
	}
}

/**
 * Get the top element
 * @heap: the heap where to search for the top element
 * @return: the top element
 */
team_t *heap_top(heap_t *heap)
{
	/* TODO */
	return heap->arr[0];
}

/**
 * Rebalance and/or reorder if needed.
 */
static void __heap_pop_fix(heap_t *heap, int pos)
{
	team_t *tmp_team;
	int p = pos;
	int l = GO_LEFT(pos);
	int r = GO_RIGHT(pos);

	/* TODO */
	if ( l >= heap->size || r >= heap->size) {
		return;
	}

	int max = heap->cmp(heap->arr[l], heap->arr[r]) < 0 ? l : r; 

	if (heap->cmp(heap->arr[max], heap->arr[p]) < 0) {
		tmp_team = heap->arr[max];
		heap->arr[max] = heap->arr[p];
		heap->arr[p] = tmp_team;

		__heap_pop_fix(heap, l);
		return;
	}
}

/**
 * Remove the top element
 */
void heap_pop(heap_t *heap)
{
	free(heap->arr[0]->name);
	free(heap->arr[0]);

	heap->arr[0] = heap->arr[heap->size - 1];
	heap->size--;

	__heap_pop_fix(heap, 0);
}

/**
 * Check if the heap is empty
 * @heap: the heap to be checked
 * @return: 1 if the heap is empty else 0
 */
int heap_empty(heap_t *heap)
{
	return heap->size <= 0;
}

/**
 * Free a heap
 * @heap: the heap to be freed
 */
void heap_free(heap_t *heap)
{
	/* TODO */
		while (!heap_empty(heap)){
		heap_pop(heap);
	}

	free(heap->arr);
	free(heap);
}

/* --- TEST CODE BEGINS HERE --- */

char to_lower(char c)
{
	if ('A' <= c && c <= 'Z')
		return c + 0x20;
	return c;
}

int heap_cmp_str_lexicographically(const char *key1, const char *key2)
{
	int rc, i, len;

	len = strlen(key1) < strlen(key2) ? strlen(key1) : strlen(key2);
	for (i = 0; i < len; ++i) {
		rc = to_lower(key1[i]) - to_lower(key2[i]);

		if (rc == 0)
			continue;
		return rc;
	}

	rc = to_lower(key1[i]) - to_lower(key2[i]);
	return rc;
}

int heap_cmp_teams(const team_t *key1, const team_t *key2)
{
	int score_diff = key2->score - key1->score;

	if (score_diff != 0)
		return score_diff;

	return heap_cmp_str_lexicographically(key1->name, key2->name);
}

int main(void)
{
	heap_t *heap;
	team_t *team, *tmp_team;
	int N = 0, task;
	char buf[256];
	char temp_name[BUFSIZ];

	heap = heap_create(heap_cmp_teams);

	team = malloc(sizeof(*team));
	DIE(!team, "team malloc");
	team->name = malloc(BUFSIZ * sizeof(*team->name));
	DIE(!team->name, "team->name malloc");

	fgets(buf, 256, stdin);
	sscanf(buf, "%d\n", &N);
	fflush(stdout);

	while (N--) {
		fgets(buf, 256, stdin);
		sscanf(buf, "%d", &task);
	
		switch (task) {
		case 1:
			memset(team->name, 0, BUFSIZ);
			memset(temp_name, 0, BUFSIZ);
			sscanf(buf + 2, "%s %d\n", temp_name, &team->score);
			cleanup_example_string(temp_name);
			memcpy(team->name, temp_name, strlen(temp_name));
			heap_insert(heap, team);
			break;
		case 2:
			if (!heap_empty(heap)) {
				tmp_team = heap_top(heap);
				printf("%s %d\n", tmp_team->name, tmp_team->score);
			}
			break;
		case 3:
			if (!heap_empty(heap)) {
				heap_pop(heap);
			}
			break;
		default:
			perror("Invalid task!");
		}
	}

	/* TODO: Print teams in leaderboard order */
	while(!heap_empty(heap)) {
		printf("%s %d\n", heap->arr[0]->name, heap->arr[0]->score);
		heap_pop(heap);
	}

	free(team->name);
	free(team);
	heap_free(heap);

	return 0;
}
