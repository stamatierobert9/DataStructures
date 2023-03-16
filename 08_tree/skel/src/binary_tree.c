/**
 * SD, 2020
 *
 * Lab #8, Binary Tree
 *
 * Task #1 - Binary Tree implementation
 */

#include "binary_tree.h"

#define MAX_NODES 100

/**
 * Helper function to create a node
 * @data: the data to be added in the node
 * @data_size: data's size
 */
static b_node_t*
__b_node_create(void* data, size_t data_size)
{
    b_node_t* b_node;

    b_node = malloc(sizeof(*b_node));
    DIE(b_node == NULL, "b_node malloc");

    b_node->left = b_node->right = NULL;

    b_node->data = malloc(data_size);
    DIE(b_node->data == NULL, "b_node->data malloc");
    memcpy(b_node->data, data, data_size);

    return b_node;
}

b_tree_t*
b_tree_create(size_t data_size)
{
    b_tree_t *b_tree = malloc(sizeof(b_tree_t));

    b_tree->root = NULL;
    b_tree->data_size = data_size;

    return b_tree;
}

void
b_tree_insert(b_tree_t* b_tree, void* data)
{
    queue_t* q;
    b_node_t *b_node, *b_node_tmp;

    b_node = __b_node_create(data, b_tree->data_size);

    if (!b_tree->root) {
        b_tree->root = b_node;
        return;
    }

    q = q_create(sizeof(void*), MAX_NODES);

    q_enqueue(q, &b_tree->root);

    while(1) {
        b_node_tmp_addr = q_front(q);
        b_node_tmp = *b_node_tmp_addr;
        q_dequeue(q);

        if (b_node_tmp->left) {
            q_enqueue(q, &b_node_tmp->left);
        } else {
            b_node_tmp->left = b_node;
            q_free(q);
            return;
        }

        if (b_node_tmp->right) {
            q_enqueue(q, &b_node_tmp->right);
        } else {
            b_node_tmp->right = b_node;
            q_free(q);
            return;
        }
    }
}

static void
__b_tree_print_preorder(b_node_t* b_node, void (*print_data)(void*))
{
    if (!b_node)
        return;

    /* TODO */
    print_data(b_node->data);
    __b_tree_print_preorder(b_node->left, print_data);
    __b_tree_print_preorder(b_node->right, print_data);
}

void
b_tree_print_preorder(b_tree_t* b_tree, void (*print_data)(void*))
{
    __b_tree_print_preorder(b_tree->root, print_data);
    printf("\n");
}

static void
__b_tree_print_inorder(b_node_t* b_node, void (*print_data)(void*))
{
    if (!b_node)
        return;

    /* TODO */
    __b_tree_print_inorder(b_node->left, print_data);
    print_data(b_node->data);
    __b_tree_print_inorder(b_node->right, print_data);
}

void
b_tree_print_inorder(b_tree_t* b_tree, void (*print_data)(void*))
{
    __b_tree_print_inorder(b_tree->root, print_data);
    printf("\n");
}

static void
__b_tree_print_postorder(b_node_t* b_node, void (*print_data)(void*))
{
    if (!b_node)
        return;

    /* TODO */
    __b_tree_print_postorder(b_node->left, print_data);
    __b_tree_print_postorder(b_node->right, print_data);
    print_data(b_node->data);
}

void
b_tree_print_postorder(b_tree_t* b_tree, void (*print_data)(void*))
{
    __b_tree_print_postorder(b_tree->root, print_data);
    printf("\n");
}

/**
 * Free the left and the right subtree of a node, its data and itself
 * @b_node: the node which has to free its children and itself
 * @free_data: function used to free the data contained by a node
 */
static void
__b_tree_free(b_node_t* b_node, void (*free_data)(void*))
{
    if (!b_node)
        return;

    /* TODO */
    __b_tree_free(b_node->left, free_data);
    __b_tree_free(b_node->right, free_data);
    free_data(b_node->data);
    free(b_node);
}

void
b_tree_free(b_tree_t* b_tree, void (*free_data)(void*))
{
    __b_tree_free(b_tree->root, free_data);
    free(b_tree);
}
