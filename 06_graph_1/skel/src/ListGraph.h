#ifndef __LISTGRAPH_H__
#define __LISTGRAPH_H__

#include "LinkedList.h"

typedef struct
{
	linked_list_t** neighbors; /* Listele de adiacenta ale grafului */
	int nodes;                 /* Numarul de noduri din graf. */
} list_graph_t;

list_graph_t*
lg_create(int nodes);

void
lg_add_edge(list_graph_t* graph, int src, int dest);

int
lg_has_edge(list_graph_t* graph, int src, int dest);

linked_list_t*
lg_get_neighbours(list_graph_t* graph, int node);

void
lg_remove_edge(list_graph_t* graph, int src, int dest);

void
lg_free(list_graph_t* graph);

#endif /* __LISTGRAPH_H__ */