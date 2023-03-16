#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define HMAX 100
#define MAX_STRING_SIZE 64
#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define DIE(assertion, call_description)				\
	do {								\
		if (assertion) {					\
			fprintf(stderr, "(%s, %d): ", __FILE__,		\
				__LINE__);				\
			perror(call_description);			\
			exit(errno);					\
		}							\
	} while (0)

/* Helper data structures definitions */
typedef struct ll_node_t ll_node_t;
struct ll_node_t
{
	void* data;
	ll_node_t* next;
};

typedef struct linked_list_t linked_list_t;
struct linked_list_t
{
	ll_node_t* head;
	unsigned int data_size;
	unsigned int size;
};

typedef struct stack_t stack_t;
struct stack_t
{
	struct linked_list_t* list;
};

typedef struct queue_t queue_t;
struct queue_t
{
	unsigned int max_size;
	unsigned int size;
	unsigned int data_size;
	unsigned int read_idx;
	unsigned int write_idx;
	void **buff;
};

typedef struct
{
	linked_list_t** neighbors;
	int nodes;
} list_graph_t;


typedef struct info info;
struct info {
	void *key;
	void *value;
};

typedef struct hashtable_t hashtable_t;
struct hashtable_t {
	linked_list_t **buckets;
	unsigned int size;
	unsigned int hmax;
	unsigned int (*hash_function)(void*);
	int (*compare_function)(void*, void*);
};

/* Helper data structures functions */
linked_list_t*
ll_create(unsigned int data_size)
{
	linked_list_t* ll = calloc(1, sizeof(*ll));
	DIE(!ll, "calloc list");

	ll->data_size = data_size;

	return ll;
}

static ll_node_t*
get_nth_node(linked_list_t* list, unsigned int n)
{
	unsigned int len = list->size - 1;
	unsigned int i;
	ll_node_t* node = list->head;

	n = MIN(n, len);

	for (i = 0; i < n; ++i)
		node = node->next;

	return node;
}

static ll_node_t*
create_node(const void* new_data, unsigned int data_size)
{
	ll_node_t* node = calloc(1, sizeof(*node));
	DIE(!node, "calloc node");

	node->data = malloc(data_size);
	DIE(!node->data, "malloc data");

	memcpy(node->data, new_data, data_size);

	return node;
}

void
ll_add_nth_node(linked_list_t* list, unsigned int n, const void* new_data)
{
	ll_node_t *new_node, *prev_node;

	if (!list)
		return;

	new_node = create_node(new_data, list->data_size);

	if (!n || !list->size) {
		new_node->next = list->head;
		list->head = new_node;
	} else {
		prev_node = get_nth_node(list, n - 1);
		new_node->next = prev_node->next;
		prev_node->next = new_node;
	}

	++list->size;
}

ll_node_t*
ll_remove_nth_node(linked_list_t* list, unsigned int n)
{
	ll_node_t *prev_node, *removed_node;

	if (!list || !list->size)
		return NULL;

	if (!n) {
		removed_node = list->head;
		list->head = removed_node->next;
		removed_node->next = NULL;
	} else {
		prev_node = get_nth_node(list, n - 1);
		removed_node = prev_node->next;
		prev_node->next = removed_node->next;
		removed_node->next = NULL;
	}

	--list->size;

	return removed_node;
}

unsigned int
ll_get_size(linked_list_t* list)
{
	return !list ? 0 : list->size;
}

void
ll_free(linked_list_t** pp_list)
{
	ll_node_t* node;

	if (!pp_list || !*pp_list)
		return;

	while ((*pp_list)->size) {
		node = ll_remove_nth_node(*pp_list, 0);
		free(node->data);
		free(node);
	}

	free(*pp_list);
	*pp_list = NULL;
}

void
ll_print_int(linked_list_t* list)
{
	ll_node_t* node = list->head;

	for (; node; node = node->next)
		printf("%d ", *(int*)node->data);
	printf("\n");
}

void
ll_print_string(linked_list_t* list)
{
	ll_node_t* node = list->head;

	for (; node; node = node->next)
		printf("%s ", (char*)node->data);
	printf("\n");
}

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

unsigned int
st_is_empty(stack_t* st)
{
	return !st || !st->list || !st->list->size;
}

void*
st_peek(stack_t* st)
{
	if (!st || !st->list || !st->list->size)
		return NULL;

	return st->list->head->data;
}

void
st_pop(stack_t* st)
{
	ll_node_t *node;

	if (!st || !st->list)
		return;

	node = ll_remove_nth_node(st->list, 0);
	free(node->data);
	free(node);
}

void
st_push(stack_t* st, void* new_data)
{
    if (!st || !st->list)
        return;
    
    ll_add_nth_node(st->list, 0, new_data);
}

void
st_clear(stack_t* st)
{
	if (!st || !st->list)
		return;

	ll_free(&st->list);
}

void
st_free(stack_t* st)
{
	if (!st || !st->list)
		return;

	ll_free(&st->list);
	free(st);
}

queue_t *
q_create(unsigned int data_size, unsigned int max_size)
{
	queue_t *q = calloc(1, sizeof(*q));
	DIE(!q, "calloc queue failed");

	q->data_size = data_size;
	q->max_size = max_size;

	q->buff = malloc(max_size * sizeof(*q->buff));
	DIE(!q->buff, "malloc buffer failed");

	return q;
}

unsigned int
q_get_size(queue_t *q)
{
	return !q ? 0 : q->size;
}

unsigned int
q_is_empty(queue_t *q)
{
	return !q ? 1 : !q->size;
}

void *
q_front(queue_t *q)
{
	if (!q || !q->size)
		return NULL;

	return q->buff[q->read_idx];
}

int
q_dequeue(queue_t *q)
{
	if (!q || !q->size)
		return 0;

	free(q->buff[q->read_idx]);

	q->read_idx = (q->read_idx + 1) % q->max_size;
	--q->size;
	return 1;
}

int
q_enqueue(queue_t *q, void *new_data)
{
	void *data;
	if (!q || q->size == q->max_size)
		return 0;

	data = malloc(q->data_size);
	DIE(!data, "malloc data failed");
	memcpy(data, new_data, q->data_size);

	q->buff[q->write_idx] = data;
	q->write_idx = (q->write_idx + 1) % q->max_size;
	++q->size;

	return 1;
}

void
q_clear(queue_t *q)
{
	unsigned int i;
	if (!q || !q->size)
		return;

	for (i = q->read_idx; i != q->write_idx; i = (i + 1) % q->max_size)
		free(q->buff[i]);

	q->read_idx = 0;
	q->write_idx = 0;
	q->size = 0;
}

void
q_free(queue_t *q)
{
	if (!q)
		return;

	q_clear(q);
	free(q->buff);
	free(q);
}


static int is_node_in_graph(int n, int nodes)
{
	return n >= 0 && n < nodes;
}

list_graph_t*
lg_create(int nodes)
{
	int i;

	list_graph_t *g = malloc(sizeof(*g));
	DIE(!g, "malloc graph failed");

	g->neighbors = malloc(nodes * sizeof(*g->neighbors));
	DIE(!g->neighbors, "malloc neighbours failed");

	for (i = 0; i != nodes; ++i)
		g->neighbors[i] = ll_create(sizeof(int));

	g->nodes = nodes;

	return g;
}

void
lg_add_edge(list_graph_t* graph, int src, int dest)
{
	if (
		!graph || !graph->neighbors
		|| !is_node_in_graph(src, graph->nodes)
		|| !is_node_in_graph(dest, graph->nodes)
	)
		return;

	ll_add_nth_node(graph->neighbors[src], graph->neighbors[src]->size, &dest);
}

static ll_node_t *find_node(linked_list_t *ll, int node, unsigned int *pos)
{
	ll_node_t *crt = ll->head;
	unsigned int i;

	for (i = 0; i != ll->size; ++i) {
		if (node == *(int *)crt->data) {
			*pos = i;
			return crt;
		}

		crt = crt->next;
	}

	return NULL;
}

int
lg_has_edge(list_graph_t* graph, int src, int dest)
{
	unsigned int pos;

	if (
		!graph || !graph->neighbors
		|| !is_node_in_graph(src, graph->nodes)
		|| !is_node_in_graph(dest, graph->nodes)
	)
		return 0;

	return find_node(graph->neighbors[src], dest, &pos) != NULL;
}

linked_list_t*
lg_get_neighbours(list_graph_t* graph, int node)
{
	if (
		!graph || !graph->neighbors
		|| !is_node_in_graph(node, graph->nodes)
	)
		return NULL;

	return graph->neighbors[node];
}

void
lg_remove_edge(list_graph_t* graph, int src, int dest)
{
	unsigned int pos;

	if (
		!graph || !graph->neighbors
		|| !is_node_in_graph(src, graph->nodes)
		|| !is_node_in_graph(dest, graph->nodes)
	)
		return;

	if (!find_node(graph->neighbors[src], dest, &pos))
		return;

	ll_remove_nth_node(graph->neighbors[src], pos);
}

void
lg_free(list_graph_t* graph)
{
	int i;

	for (i = 0; i != graph->nodes; ++i)
		ll_free(graph->neighbors + i);
	
	free(graph->neighbors);
	free(graph);
}

int
compare_function_ints(void *a, void *b)
{
	int int_a = *((int *)a);
	int int_b = *((int *)b);

	if (int_a == int_b) {
		return 0;
	} else if (int_a < int_b) {
		return -1;
	} else {
		return 1;
	}
}

int
compare_function_strings(void *a, void *b)
{
	char *str_a = (char *)a;
	char *str_b = (char *)b;

	return strcmp(str_a, str_b);
}

unsigned int
hash_function_int(void *a)
{
	unsigned int uint_a = *((unsigned int *)a);

	uint_a = ((uint_a >> 16u) ^ uint_a) * 0x45d9f3b;
	uint_a = ((uint_a >> 16u) ^ uint_a) * 0x45d9f3b;
	uint_a = (uint_a >> 16u) ^ uint_a;
	return uint_a;
}

unsigned int
hash_function_string(void *a)
{
	unsigned char *puchar_a = (unsigned char*) a;
	unsigned long hash = 5381;
	int c;

	while ((c = *puchar_a++))
		hash = ((hash << 5u) + hash) + c; /* hash * 33 + c */

	return hash;
}

hashtable_t *
ht_create(unsigned int hmax, unsigned int (*hash_function)(void*),
		int (*compare_function)(void*, void*))
{
	if (!hash_function || !compare_function) {
        return NULL;
    }
    
    hashtable_t* map = malloc(sizeof(hashtable_t));
    DIE(!map, "Error");

    map->size = 0;
    map->hmax = hmax;
    map->hash_function = hash_function;
    map->compare_function = compare_function;
    
    map->buckets = malloc(map->hmax * sizeof(linked_list_t *));
    DIE(!map->buckets, "Error");
    for (unsigned int i = 0; i < map->hmax; ++i) {
        map->buckets[i] = ll_create(sizeof(info));
    }

    return map;
}

int
ht_has_key(hashtable_t *ht, void *key)
{
	if (!ht || !key) {
        return -1;
    }

    int hash_index = ht->hash_function(key) % ht->hmax;
    ll_node_t* node = ht->buckets[hash_index]->head;

    while (node != NULL) {
        info* data_info = (info *)node->data;
        if (!ht->compare_function(data_info->key, key)) {
            return 1;
        }
        node = node->next;
    }

	return 0;
}

void *
ht_get(hashtable_t *ht, void *key)
{
	if (!ht || !key || ht_has_key(ht, key) != 1) {
        return NULL;
    }
    
    int hash_index = ht->hash_function(key) % ht->hmax;
    ll_node_t* node = ht->buckets[hash_index]->head;

    while (node != NULL) {
        info* data_info = (info *)node->data;
        if (!ht->compare_function(data_info->key, key)) {
            return data_info->value;
        }
        node = node->next;
    }

	return NULL;
}

void
ht_put(hashtable_t *ht, void *key, unsigned int key_size,
	void *value, unsigned int value_size)
{
	if (!ht || !key || !value) {
        return;
    }

    int hash_index = ht->hash_function(key) % ht->hmax;
    
    if (ht_has_key(ht, key) == 1) {
        ll_node_t* node = ht->buckets[hash_index]->head;
        while (node != NULL) {
            info* data_info = node->data;

            if (!ht->compare_function(data_info->key, key)) {
                free(data_info->value);

                data_info->value = malloc(value_size);
                DIE(!data_info, "Error");

                memcpy(data_info->value, value, value_size);
                return;  
            }

            node = node->next;
        }
    }

    info* data_info = malloc(sizeof(info));
    DIE(!data_info, "Error");

    data_info->key = malloc(key_size);
    DIE(!data_info->key, "Error");
    data_info->value = malloc(value_size);
    DIE(!data_info->value, "Error");

    memcpy(data_info->key, key, key_size);
    memcpy(data_info->value, value, value_size);

    ll_add_nth_node(ht->buckets[hash_index], 0, data_info);
    ht->size++;

    free(data_info);

}

void
ht_remove_entry(hashtable_t *ht, void *key)
{
	if (!ht || !key || ht_has_key(ht, key) != 1) {
        return;
    }

    int hash_index = ht->hash_function(key) % ht->hmax;
    ll_node_t* node = ht->buckets[hash_index]->head;

    unsigned int node_nr = 0;

    while (node != NULL) {
        info* data_info = (info *) node->data;

        if (!ht->compare_function(data_info->key, key)) {
            free(data_info->key);
            free(data_info->value);
            free(data_info);

            ll_node_t* deleted_node = ll_remove_nth_node(ht->buckets[hash_index], node_nr);
            free(deleted_node);

            ht->size--;
            return;
        }

        node = node->next;
        node_nr++;
    }

}

void
ht_free(hashtable_t *ht)
{
	if (!ht) {
        return;
    }

    for (unsigned int i = 0; i < ht->hmax; ++i) {
        ll_node_t* node = ht->buckets[i]->head;

        while (node != NULL) {
            info* data_info = (info *)node->data;
            free(data_info->key);
            free(data_info->value);
            node = node->next;
        }

        ll_free(&ht->buckets[i]);
    }

    free(ht->buckets);
    free(ht);
}

unsigned int
ht_get_size(hashtable_t *ht)
{
	if (ht == NULL)
		return 0;

	return ht->size;
}

unsigned int
ht_get_hmax(hashtable_t *ht)
{
	if (ht == NULL)
		return 0;

	return ht->hmax;
}

/*
	Returns a list of nodes which contains the ids of subjects in topological order.

	The mapping between subjects and ids is already handled in main, you can worry only 
	about ints in this function.

	There are multiple correct topological orders, unfortunately the checker considers
	only one of them correct. To ensure you get the correct one we recommend using the DFS
	approach, as that's the one we used to generate the refs.
*/

void DFS(list_graph_t* graph, int node, int *color, linked_list_t *conected_components){
	stack_t *stack = st_create(sizeof(int));
	st_push(stack, &node);
	color[node] = 1;

	int i;
	while(!st_is_empty(stack)){
		int current_node = *((int*)st_peek(stack));
		int neighbor_exist = 0;
		ll_node_t *current = graph->neighbors[current_node]->head;

		while(current) {
			i = *((int*)current->data);
			if(color[i] == 0){
				st_push(stack, &i);
				color[i] = 1;
				neighbor_exist = 1;
				break;
			}
			current = current->next;
		}

		if(!neighbor_exist) {
			color[current_node] = 2;
			ll_add_nth_node(conected_components, conected_components->size, &current_node);
			st_pop(stack);
		}
	}

	st_free(stack);
}

linked_list_t* top_sort(list_graph_t* graph) {
	int *color;
	color = calloc(graph->nodes, sizeof(*color));
	linked_list_t *conected_components = ll_create(sizeof(int));

	for(int i = 0; i < graph->nodes; i++){
		if(color[i] == 0){
			DFS(graph, i, color, conected_components);
		}
	}
	free(color);
	return conected_components;
}

/* stupid \n workaround for lambda */
void cleanup_example_string(char* str) {
    int len = strlen(str);
    
    if(str[len-2] == '\\') {
        str[len-2] = '\0';
    }
}

int main() {
    int n, m, subject_idx = 0;

	char src[MAX_STRING_SIZE], dest[MAX_STRING_SIZE];
	char buf[256];
    list_graph_t* graph;
	hashtable_t* ht = ht_create(HMAX, hash_function_string, compare_function_strings);
	hashtable_t* ht_reverse = ht_create(HMAX, hash_function_int, compare_function_ints);
	
    // stupid fgets workaround for lambda
    fgets(buf, 256, stdin);
    sscanf(buf, "%d %d\n", &n, &m);

    graph = lg_create(n);

    for(int i = 0; i < m; ++i) {
        fgets(buf, 256, stdin);
        sscanf(buf,"%s %s\n", src, dest);
        
        cleanup_example_string(src);
        cleanup_example_string(dest);

		if(!ht_has_key(ht, src)) {
			ht_put(ht, src, MAX_STRING_SIZE, &subject_idx, sizeof(int));
			ht_put(ht_reverse, &subject_idx, sizeof(int), src, MAX_STRING_SIZE);
			subject_idx++;
		}

		if(!ht_has_key(ht, dest)) {
			ht_put(ht, dest, MAX_STRING_SIZE, &subject_idx, sizeof(int));
			ht_put(ht_reverse, &subject_idx, sizeof(int), dest, MAX_STRING_SIZE);
			subject_idx++;
		}

        lg_add_edge(graph, *((int*)ht_get(ht, src)), *((int*)ht_get(ht, dest)));
    }

    linked_list_t* sorted = top_sort(graph);
	for(ll_node_t* head = sorted->head; head; head = head->next) {
		printf("%s\n", (char*) ht_get(ht_reverse, (int*)head->data));
	}
	

	lg_free(graph);
    return 0;
}
