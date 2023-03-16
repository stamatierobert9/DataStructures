#include <stdio.h>
#include <string.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STRING_SIZE    256
typedef struct
{
    int** matrix; /* Matricea de adiacenta a grafului */
    int nodes;    /* Numarul de noduri din graf. */
} matrix_graph_t;

/**
 * Initializeaza graful cu numarul de noduri primit ca parametru si aloca
 * memorie pentru matricea de adiacenta a grafului.
 */

/* Graful este NEORIENTAT */

/* Nodurile sunt indexate de la 0.*/

matrix_graph_t*
mg_create(int nodes)
{
    matrix_graph_t* graph = malloc(sizeof(matrix_graph_t*));

    graph->matrix = malloc(nodes * sizeof(*graph->matrix));

    for (int i = 0; i < nodes; i++){
        graph->matrix[i] = calloc(nodes, sizeof(**graph->matrix));
    }

    graph->nodes = nodes;
    return graph;
}

/* Adauga o muchie intre nodurile sursa si destinatie */
void
mg_add_edge(matrix_graph_t* graph, int src, int dest)
{
    if (!graph){
        return;
    }
    if (!graph->matrix){
        return;
    }
    if (src < 0 || src >= graph->nodes || dest < 0 || dest >= graph->nodes){
        return;
    }
    if (!graph->matrix[src] || !graph->matrix[dest]){
        return;
    }

    graph->matrix[src][dest] = 1;
    graph->matrix[dest][src] = 1;
}

/* Returneaza 1 daca exista muchie intre cele doua noduri, 0 in caz contrar */
int
mg_has_edge(matrix_graph_t* graph, int src, int dest)
{
    if (!graph){
        return 0;
    }
    if (!graph->matrix){
        return 0;
    }
    if (src < 0 || src >= graph->nodes || dest < 0 || dest >= graph->nodes){
        return 0;
    }
    if (!graph->matrix[src] || !graph->matrix[dest]){
        return 0;
    }

    return graph->matrix[src][dest];
}

/* Elimina muchia dintre nodurile sursa si destinatie */
void
mg_remove_edge(matrix_graph_t* graph, int src, int dest)
{
    if (!graph){
        return;
    }
    if (!graph->matrix){
        return;
    }
    if (src < 0 || src >= graph->nodes || dest < 0 || dest >= graph->nodes) {
        return;        
    }
    if (!graph->matrix[src] || !graph->matrix[dest]) {
        return;
    }

    graph->matrix[src][dest] = 0;
    graph->matrix[dest][src] = 0;
}

/* Elibereaza memoria folosita de matricea de adiacenta a grafului */
void
mg_free(matrix_graph_t* graph)
{
    if (!graph)
        return;
    if (!graph->matrix) {
        free(graph);
        return;
    }
    
    for (int i = 0; i < graph->nodes; i++)
        if (graph->matrix[i])
            free(graph->matrix[i]);
    free(graph->matrix);
    free(graph);
}

void
print_matrix_graph(matrix_graph_t* mg)
{
    if (!mg){
        return;
    }
    if (!mg->matrix){
        return;
    }

    for (int i = 0; i < mg->nodes; i++){
        for (int j = 0; j < mg->nodes; j++){
            printf("%d", mg->matrix[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    
    matrix_graph_t *mg = NULL;
    
    while (1) {
        char command[MAX_STRING_SIZE];
        int nr1, nr2;
        int nr_nodes;
        
        scanf("%s", command);
        
        if (strncmp(command, "create_mg", 9) == 0) {
            scanf("%d", &nr_nodes);
            mg = mg_create(nr_nodes);
        }
        
        if (strncmp(command, "add_edge", 8) == 0) {
            if (mg != NULL) {
                scanf("%d %d", &nr1, &nr2);
                mg_add_edge(mg, nr1, nr2);
            } else {
                printf("Create a graph first!\n");
                exit(0);
            }
        }
        
        if (strncmp(command, "remove_edge", 11) == 0) {
            if (mg != NULL) {
                scanf("%d %d", &nr1, &nr2);
                mg_remove_edge(mg, nr1, nr2);
            } else {
                printf("Create a graph first!\n");
                exit(0);
            }
        }
        
        if (strncmp(command, "print_graph", 11) == 0) {
            if (mg != NULL) {
                print_matrix_graph(mg);
            } else {
                printf("Create a graph first!\n");
                exit(0);
            }
        }
        
        if (strncmp(command, "has_edge", 8) == 0) {
            if (mg != NULL) {
                int flag;
                scanf("%d %d", &nr1, &nr2);
                flag = mg_has_edge(mg, nr1, nr2);
                if (flag == 1) {
                    printf("Has edge\n");
                }
                else if (flag == 0) {
                    printf("No edge\n");
                }
            } else {
                printf("Create a graph first!\n");
                exit(0);
            }
        }
        
        if (strncmp(command, "free", 4) == 0) {
            if (mg != NULL) {
                mg_free(mg);
            } else {
                printf("Create a graph first!\n");
                exit(0);
            }
            break;
        }
    }
    
    return 0;
}
