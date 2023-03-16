/**
 * SD, 2020
 * 
 * Lab #8, Binary Tree
 * 
 * Task #1 - Binary Tree implementation (test file)
 */

#include "binary_tree.h"

void read_tree(b_tree_t *b_tree)
{
    int i, N, data;

    scanf("%d\n", &N);

    for (i = 0; i < N; ++i) {
        scanf("%d ", &data);
        b_tree_insert(b_tree, &data);
    }
}

void print_data(void *data)
{
    printf("%d ", *(int *) data);
}

int main(void)
{
    b_tree_t *binary_tree;

    binary_tree = b_tree_create(sizeof(int));

    read_tree(binary_tree);

    b_tree_print_preorder(binary_tree, print_data);
    b_tree_print_inorder(binary_tree, print_data);
    b_tree_print_postorder(binary_tree, print_data);

    b_tree_free(binary_tree, free);

    return 0;
}
