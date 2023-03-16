/**
 * SD, 2020
 *
 * Lab #8, Binary Tree
 *
 * Binary Tree structure and function definitions
 */

#ifndef BINARY_TREE_H__
#define BINARY_TREE_H__

#include <string.h>

#include "Queue.h"
#include "utils.h"

typedef struct b_node_t b_node_t;
struct b_node_t
{
    /* left child */
    b_node_t* left;
    /* right child */
    b_node_t* right;

    /* data contained by the node */
    void* data;
};

typedef struct b_tree_t b_tree_t;
struct b_tree_t
{
    /* root of the tree */
    b_node_t* root;

    /* size of the data contained by the nodes */
    size_t data_size;
};

/**
 * Creates a new binary tree
 * @data_size: size of the data contained by the tree's nodes
 * @return: pointer to the newly created tree
 */
b_tree_t*
b_tree_create(size_t data_size);

/**
 * Creates a new node with the specific data and adds it to the binary tree
 * @b_tree: the tree where the value is going to be inserted
 * @data: the data to insert in the tree
 */
void
b_tree_insert(b_tree_t* b_tree, void* data);

/**
 * Print a binary tree - preorder traversal
 * @b_tree: the binary tree to be printed
 * @print_data: function used to print node's data
 */
void
b_tree_print_preorder(b_tree_t* b_tree, void (*print_data)(void*));

/**
 * Print a binary tree - inorder traversal
 * @b_tree: the binary tree to be printed
 * @print_data: function used to print node's data
 */
void
b_tree_print_inorder(b_tree_t* b_tree, void (*print_data)(void*));

/**
 * Print a binary tree - postorder traversal
 * @b_tree: the binary tree to be printed
 * @print_data: function used to print node's data
 */
void
b_tree_print_postorder(b_tree_t* b_tree, void (*print_data)(void*));

/**
 * Clear the whole memory used by the tree and its nodes
 * @b_tree: the binary tree to be freed
 * @free_data: function used to free the data contained by a node
 */
void
b_tree_free(b_tree_t* b_tree, void (*free_data)(void*));

#endif /* BINARY_TREE_H__ */
