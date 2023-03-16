/**
 * SD, 2021
 * 
 * Lab #9, BST & Heap
 * 
 * Binary Search Tree structure and function definitions
 */

#ifndef __BST_H_
#define __BST_H_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct bst_node_t bst_node_t;
struct  bst_node_t {
    /* left child */
    bst_node_t *left;

    /* right child */
    bst_node_t *right;

    /* data contained by the node */
    void *data;
};

typedef struct bst_tree_t bst_tree_t;
struct bst_tree_t {
    /* root of the tree */
    bst_node_t  *root;

     /* size of the data contained by the nodes */
    size_t data_size;

    /* function used for sorting the keys */
    int	(*cmp)(const void *key1, const void *key2);
};

/**
 * Alloc memory for a new BST
 * @data_size: size of the data contained by the BST's nodes
 * @cmp_f: pointer to a function used for sorting
 * @return: pointer to the newly created BST
 */
bst_tree_t *bst_tree_create(size_t data_size,
                            int (*cmp_f)(const void *, const void *));

/**
 * Insert a new element in a BST
 * @bst_tree: the BST where to insert the new element
 * @data: the data to be inserted in BST
 */
void bst_tree_insert(bst_tree_t *bst_tree, void *data);

/**
 * Remove an element from a BST
 * @bst_tree: the BST where to remove the element from
 * @data: the data that is contained by the node which has to be removed
 */
void bst_tree_remove(bst_tree_t *bst_tree, void *data);

/**
 * Free a BST
 * @bst_tree: the BST to be freed
 * @free_data: function used to free the data contained by a node
 */
void bst_tree_free(bst_tree_t *bst_tree, void (*free_data)(void *));

/**
 * Print inorder a BST
 * @bst_tree: the BST to be printed
 * @print_data: function used to print the data contained by a node 
 */
void bst_tree_print_inorder(bst_tree_t* bst_tree, void (*print_data)(void*));

#endif
