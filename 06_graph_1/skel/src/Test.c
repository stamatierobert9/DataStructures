#include <stdio.h>
#include <stdlib.h>

#include "ListGraph.h"
#include "MatrixGraph.h"

#define MAX_NODES 10

void
print_matrix_graph(matrix_graph_t* mg)
{
	/* TODO */
}

void
print_list_graph(list_graph_t* lg)
{
	/* TODO */
}

void
dfs_list_graph(list_graph_t* lg,
		int node,
		int* visited,
		int* t_desc,
		int* t_tin)
{
	/* TODO */
}

void
dfs_matrix_graph(matrix_graph_t* mg,
		 int node,
		 int* visited,
		 int* t_desc,
		 int* t_tin)
{
	/* TODO */
}

void
bfs_list_graph(list_graph_t* lg, int node, int* color, int* parent)
{
	/* TODO */
}

void
bfs_matrix_graph(matrix_graph_t* mg, int node, int* color, int* parent)
{
	/* TODO */
}

void
floyd_warshall(matrix_graph_t* mg)
{
	/* TODO BONUS */
}

int
main()
{
	int nodes, edges;
	int x[MAX_NODES], y[MAX_NODES];
	int visited[MAX_NODES], t_dest[MAX_NODES], t_fin[MAX_NODES];
	list_graph_t* lg = lg_create(MAX_NODES);
	matrix_graph_t* mg = mg_create(MAX_NODES);

	int numbers[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	printf("-------------------------------- Test ListGraph "
		"--------------------------------\n");
	/* Test add_edge_list_graph has_edge_list_graph */

	lg_add_edge(lg, numbers[0], numbers[1]);
	lg_add_edge(lg, numbers[3], numbers[2]);

	printf("#1:\nOutput: %d\nOutput asteptat: 1\n",
		lg_has_edge(lg, numbers[0], numbers[1]));

	printf("#2:\nOutput: %d\nOutput asteptat: 1\n",
		lg_has_edge(lg, numbers[3], numbers[2]));

	printf("#3:\nOutput: %d\nOutput asteptat: 0\n",
		lg_has_edge(lg, numbers[2], numbers[4]));

	/* Test remove_edge_list_graph */
	lg_remove_edge(lg, numbers[0], numbers[1]);
	printf("#4:\nOutput: %d\nOutput asteptat: 0\n",
		lg_has_edge(lg, numbers[0], numbers[1]));

	/* Test get_neighbours_list_graph */
	lg_add_edge(lg, numbers[0], numbers[1]);
	lg_add_edge(lg, numbers[0], numbers[2]);
	lg_add_edge(lg, numbers[0], numbers[3]);
	lg_add_edge(lg, numbers[0], numbers[4]);

	linked_list_t* l = lg_get_neighbours(lg, numbers[0]);

	printf("#5:\n");
	printf("Output: ");
	ll_print_int(l);
	printf("Output asteptat: 1 2 3 4\n");

	printf("-------------------------------- Test MatrixGraph "
		"--------------------------------\n");
	/* test add edge_matrix_graph has_edge_matrix_graph */
	mg_add_edge(mg, numbers[0], numbers[1]);
	mg_add_edge(mg, numbers[3], numbers[2]);

	printf("#1:\nOutput: %d\nOutput asteptat: 1\n",
		mg_has_edge(mg, numbers[0], numbers[1]));

	printf("#2:\nOutput: %d\nOutput asteptat: 1\n",
		mg_has_edge(mg, numbers[3], numbers[2]));

	printf("#3:\nOutput: %d\nOutput asteptat: 0\n",
		mg_has_edge(mg, numbers[2], numbers[4]));

	/* test remove_edge_matrix_graph */
	mg_remove_edge(mg, numbers[0], numbers[1]);
	printf("#4:\nOutput: %d\nOutput asteptat: 0\n",
		mg_has_edge(mg, numbers[0], numbers[1]));

	lg_free(lg);
	mg_free(mg);
	return 0;
}
