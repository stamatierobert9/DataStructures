#include <stdio.h>
#include <stdlib.h>

#include "ListGraph.h"
#include "utils.h"

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

	ll_add_nth_node(graph->neighbors[src], 0, &dest);
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
