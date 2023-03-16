#ifndef __MATRIXGRAPH_H__
#define __MATRIXGRAPH_H__

typedef struct
{
	int** matrix; /* Matricea de adiacenta a grafului */
	int nodes;    /* Numarul de noduri din graf. */
} matrix_graph_t;

matrix_graph_t*
mg_create(int nodes);

void
mg_add_edge(matrix_graph_t* graph, int src, int dest);

int
mg_has_edge(matrix_graph_t* graph, int src, int dest);

void
mg_remove_edge(matrix_graph_t* graph, int src, int dest);

void
mg_free(matrix_graph_t* graph);

#endif /* __MATRIXGRAPH_H__ */