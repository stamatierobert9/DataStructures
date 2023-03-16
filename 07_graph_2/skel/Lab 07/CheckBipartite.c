#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define MAX_NODES 100
#define EVEN 0
#define ODD 1

#define MIN(x, y) ((x) < (y) ? (x) : (y))

#define DIE(assertion, call_description)            \
    do                                              \
    {                                               \
        if (assertion)                              \
        {                                           \
            fprintf(stderr, "(%s, %d): ", __FILE__, \
                    __LINE__);                      \
            perror(call_description);               \
            exit(errno);                            \
        }                                           \
    } while (0)

/* Helper data structures definitions */
typedef struct ll_node_t ll_node_t;
struct ll_node_t
{
    void *data;
    ll_node_t *next;
};

typedef struct linked_list_t linked_list_t;
struct linked_list_t
{
    ll_node_t *head;
    unsigned int data_size;
    unsigned int size;
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
    linked_list_t **neighbors;
    int nodes;
} list_graph_t;

/* Helper data structures functions */
linked_list_t *
ll_create(unsigned int data_size)
{
    linked_list_t *ll = calloc(1, sizeof(*ll));
    DIE(!ll, "calloc list");

    ll->data_size = data_size;

    return ll;
}

static ll_node_t *
get_nth_node(linked_list_t *list, unsigned int n)
{
    unsigned int len = list->size - 1;
    unsigned int i;
    ll_node_t *node = list->head;

    n = MIN(n, len);

    for (i = 0; i < n; ++i)
        node = node->next;

    return node;
}

static ll_node_t *
create_node(const void *new_data, unsigned int data_size)
{
    ll_node_t *node = calloc(1, sizeof(*node));
    DIE(!node, "calloc node");

    node->data = malloc(data_size);
    DIE(!node->data, "malloc data");

    memcpy(node->data, new_data, data_size);

    return node;
}

void ll_add_nth_node(linked_list_t *list, unsigned int n, const void *new_data)
{
    ll_node_t *new_node, *prev_node;

    if (!list)
        return;

    new_node = create_node(new_data, list->data_size);

    if (!n || !list->size)
    {
        new_node->next = list->head;
        list->head = new_node;
    }
    else
    {
        prev_node = get_nth_node(list, n - 1);
        new_node->next = prev_node->next;
        prev_node->next = new_node;
    }

    ++list->size;
}

ll_node_t *
ll_remove_nth_node(linked_list_t *list, unsigned int n)
{
    ll_node_t *prev_node, *removed_node;

    if (!list || !list->size)
        return NULL;

    if (!n)
    {
        removed_node = list->head;
        list->head = removed_node->next;
        removed_node->next = NULL;
    }
    else
    {
        prev_node = get_nth_node(list, n - 1);
        removed_node = prev_node->next;
        prev_node->next = removed_node->next;
        removed_node->next = NULL;
    }

    --list->size;

    return removed_node;
}

unsigned int
ll_get_size(linked_list_t *list)
{
    return !list ? 0 : list->size;
}

void ll_free(linked_list_t **pp_list)
{
    ll_node_t *node;

    if (!pp_list || !*pp_list)
        return;

    while ((*pp_list)->size)
    {
        node = ll_remove_nth_node(*pp_list, 0);
        free(node->data);
        free(node);
    }

    free(*pp_list);
    *pp_list = NULL;
}

void ll_print_int(linked_list_t *list)
{
    ll_node_t *node = list->head;

    for (; node; node = node->next)
        printf("%d ", *(int *)node->data);
    printf("\n");
}

void ll_print_string(linked_list_t *list)
{
    ll_node_t *node = list->head;

    for (; node; node = node->next)
        printf("%s ", (char *)node->data);
    printf("\n");
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

int q_dequeue(queue_t *q)
{
    if (!q || !q->size)
        return 0;

    free(q->buff[q->read_idx]);

    q->read_idx = (q->read_idx + 1) % q->max_size;
    --q->size;
    return 1;
}

int q_enqueue(queue_t *q, void *new_data)
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

void q_clear(queue_t *q)
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

void q_free(queue_t *q)
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

list_graph_t *
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

void lg_add_edge(list_graph_t *graph, int src, int dest)
{
    if (
        !graph || !graph->neighbors || !is_node_in_graph(src, graph->nodes) || !is_node_in_graph(dest, graph->nodes))
        return;

    ll_add_nth_node(graph->neighbors[src], graph->neighbors[src]->size, &dest);
}

static ll_node_t *find_node(linked_list_t *ll, int node, unsigned int *pos)
{
    ll_node_t *crt = ll->head;
    unsigned int i;

    for (i = 0; i != ll->size; ++i)
    {
        if (node == *(int *)crt->data)
        {
            *pos = i;
            return crt;
        }

        crt = crt->next;
    }

    return NULL;
}

int lg_has_edge(list_graph_t *graph, int src, int dest)
{
    unsigned int pos;

    if (
        !graph || !graph->neighbors || !is_node_in_graph(src, graph->nodes) || !is_node_in_graph(dest, graph->nodes))
        return 0;

    return find_node(graph->neighbors[src], dest, &pos) != NULL;
}

linked_list_t *
lg_get_neighbours(list_graph_t *graph, int node)
{
    if (
        !graph || !graph->neighbors || !is_node_in_graph(node, graph->nodes))
        return NULL;

    return graph->neighbors[node];
}

void lg_remove_edge(list_graph_t *graph, int src, int dest)
{
    unsigned int pos;

    if (
        !graph || !graph->neighbors || !is_node_in_graph(src, graph->nodes) || !is_node_in_graph(dest, graph->nodes))
        return;

    if (!find_node(graph->neighbors[src], dest, &pos))
        return;

    ll_remove_nth_node(graph->neighbors[src], pos);
}

void lg_free(list_graph_t *graph)
{
    int i;

    for (i = 0; i != graph->nodes; ++i)
        ll_free(graph->neighbors + i);

    free(graph->neighbors);
    free(graph);
}

/*
    TODO

    Prints the two bipartite sets (A and B) making up the graph.

    Output format:

    a1 a2 a3 ... ak
    b1 b2 b3 ... bl

    where

    {a1, a2, a3 ... ak} make up the set A
    {b1, b2, b3 ... bk} make up the set B

    and

    a1 < a2 < a3 < ... < ak
    b1 < b2 < b3 < ... < al

    Note:

    For this exercise, we will consider that the graph will be
    divided in two sets, A and B, where:

    A will contain the EVEN nodes
    B will contain the ODD nodes

    For the purpose of finding bipartite graphs, the given graph
    can be either oriented or unoriented. For this exercise, the graph
    is unoriented.
*/

int
BFS(list_graph_t *lg, int node, int *level)
{
    if (!lg->neighbors[node]->size) {
        return 0;
    }

	queue_t *q = q_create(sizeof(int), lg->nodes - 1);
	q_enqueue(q, &node);
	level[node] = EVEN;

	while (!q_is_empty(q)) {
		int curr_node = *((int *)q_front(q));
		q_dequeue(q);

		ll_node_t *curr_neighbor = lg->neighbors[curr_node]->head;
		while (curr_neighbor) {
			int data = *((int *)curr_neighbor->data);
			if (level[data] == -1) {
                level[data] = (level[curr_node] == EVEN) ? ODD : EVEN;
                q_enqueue(q, &data);
            } else if (level[data] == level[curr_node]) {
                q_free(q);
                return 0;
            }
			
			curr_neighbor = curr_neighbor->next;
		}
	}

	q_free(q);
    return 1;
}

void print_bipartite(list_graph_t *graph)
{
    int *level = malloc(graph->nodes * sizeof(int));
    for (int i = 0; i < graph->nodes; i++)
        level[i] = -1;

    int bipartit;
    for (int i = 0; i < graph->nodes; i++)
        if (level[i] == -1) {
            bipartit = BFS(graph, i, level);
            if (!bipartit) {
                free(level);
                printf("Graph is not bipartite\n");
                return;
            }
        }

    for (int i = 0; i < graph->nodes; i++)
        if (level[i] == EVEN)
            printf("%d ", i);
    printf("\n");
    for (int i = 0; i < graph->nodes; i++)
        if (level[i] == ODD)
            printf("%d ", i);
    printf("\n");

    free(level);
}

int main()
{
    int n, m, src, dest;
    list_graph_t *graph;
    char buf[256];

    // stupid fgets workaround for lambda
    fgets(buf, 256, stdin);
    sscanf(buf, "%d %d\n", &n, &m);

    graph = lg_create(n);

    for (int i = 0; i < m; ++i)
    {
        fgets(buf, 256, stdin);
        sscanf(buf,"%d %d\n", &src, &dest);
        lg_add_edge(graph, src, dest);
        lg_add_edge(graph, dest, src);
    }

    print_bipartite(graph);
    lg_free(graph);
    return 0;
}