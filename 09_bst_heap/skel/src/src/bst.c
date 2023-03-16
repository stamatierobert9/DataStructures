/**
 * SD, 2022
 * 
 * Lab 09 - BST & Heap
 * 
 * Binary Search Tree implementation
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

/* stupid workaround for lambdachecker input from example */
void cleanup_example_string(char *str) {
	int len = strlen(str);

	if(str[len-2] == '\\') {
		str[len-2] = '\0';
	}
}

/* useful macro for handling error codes */
#define DIE(assertion, call_description)				\
	do {								\
		if (assertion) {					\
			fprintf(stderr, "(%s, %d): ",			\
					__FILE__, __LINE__);		\
			perror(call_description);			\
			exit(errno);					\
		}							\
	} while (0)


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
 * Helper function to create a node
 * @data: the data to be added in the node
 * @data_size: data's size
 */
static bst_node_t *__bst_node_create(void *data, size_t data_size)
{
	bst_node_t *bst_node;  

	bst_node = malloc(sizeof(*bst_node));

	DIE(bst_node == NULL, "bst_node malloc");

	bst_node->left = bst_node->right = NULL;

	bst_node->data = malloc(data_size);
	DIE(bst_node->data == NULL, "bst_node->data malloc");
	memcpy(bst_node->data, data, data_size);

	return bst_node;
}

/**
 * Alloc memory for a new BST
 * @data_size: size of the data contained by the BST's nodes
 * @cmp_f: pointer to a function used for sorting
 * @return: pointer to the newly created BST
 */
bst_tree_t *bst_tree_create(size_t data_size,
	int (*cmp_f)(const void *, const void *))
{
	bst_tree_t *bst_tree;

	bst_tree = malloc(sizeof(*bst_tree));
	DIE(bst_tree == NULL, "bst_tree malloc");

	bst_tree->root  = NULL;
	bst_tree->data_size = data_size;
	bst_tree->cmp   = cmp_f;

	return bst_tree;
}

/**
 * Insert a new element in a BST
 * @bst_tree: the BST where to insert the new element
 * @data: the data to be inserted in BST
 */
void bst_tree_insert(bst_tree_t *bst_tree, void *data)
{
	int rc;
	bst_node_t *root	= bst_tree->root;
	bst_node_t *parent	= NULL;
	bst_node_t *node	= __bst_node_create(data, bst_tree->data_size);

	/* TODO */
	if(root == NULL){
		bst_tree->root = node;
		return;
	}

	while (root) {
		parent = root;

		rc = bst_tree->cmp(data, root->data);
		if (rc < 0) {
			root = root->left;

			if (!root) {
				parent->left = node;
			}
		} else {
			root = root->right;

			if(!root) {
				parent->right = node;
			}
		}

	}

}

/**
 * Helper function to remove an element from a BST
 * @bst_node: the binary search subtree's root where to remove the element from
 * @data: the data that is contained by the node which has to be removed
 * @data_size: data size
 * @cmp: function used to compare the data contained by two nodes
 */
static bst_node_t *__bst_tree_remove(bst_node_t *bst_node,
	void *data, size_t data_size,
	int (*cmp)(const void *, const void *))
{
	int rc;
	bst_node_t *tmp;

	if (!bst_node)
		return NULL;

	rc = cmp(data, bst_node->data);

	if (rc < 0) {
		bst_node->left = __bst_tree_remove(bst_node->left, data, data_size, cmp);
	} else if (rc > 0) {
		bst_node->right = __bst_tree_remove(bst_node->right, data, data_size, cmp);
	} else if (!bst_node->left) {
		tmp = bst_node->right;

		free(bst_node->data);
		free(bst_node);

		return tmp;
	} else if (!bst_node->right) {
		tmp = bst_node->left;

		free(bst_node->data);
		free(bst_node);

		return tmp;
	} else {
		tmp = bst_node->left;

		while (tmp->right)
			tmp = tmp->right;

		memcpy(bst_node->data, tmp->data, data_size);
		__bst_tree_remove(tmp, tmp->data, data_size, cmp);
	}

	return bst_node;
}

/**
 * Remove an element from a BST
 * @bst_tree: the BST where to remove the element from
 * @data: the data that is contained by the node which has to be removed
 */
void bst_tree_remove(bst_tree_t *bst_tree, void *data)
{
	bst_tree->root = __bst_tree_remove(bst_tree->root, data,
		bst_tree->data_size, bst_tree->cmp);
}

/**
 * Free the left and the right subtree of a node, its data and itself
 * @b_node: the node which has to free its children and itself
 * @free_data: function used to free the data contained by a node
 */
static void __bst_tree_free(bst_node_t *bst_node, void (*free_data)(void *))
{
	if (!bst_node)
		return;

	/* TODO */
	__bst_tree_free(bst_node->left, free_data);
    __bst_tree_free(bst_node->right, free_data);
    free_data(bst_node->data);
    free(bst_node);
}

/**
 * Free a BST
 * @bst_tree: the BST to be freed
 * @free_data: function used to free the data contained by a node
 */
void bst_tree_free(bst_tree_t *bst_tree, void (*free_data)(void *))
{
	__bst_tree_free(bst_tree->root, free_data);
	free(bst_tree);
}

static void __bst_tree_print_inorder(bst_node_t* bst_node,
	void (*print_data)(void*))
{
	if (!bst_node)
		return;
		
	__bst_tree_print_inorder(bst_node->left, print_data);
	print_data(bst_node->data);
	__bst_tree_print_inorder(bst_node->right, print_data);
}

/**
 * Print inorder a BST
 * @bst_tree: the BST to be printed
 * @print_data: function used to print the data contained by a node 
 */
void bst_tree_print_inorder(bst_tree_t* bst_tree, void (*print_data)(void*))
{
	__bst_tree_print_inorder(bst_tree->root, print_data);
}

/* --- TEST CODE BEGINS HERE --- */

/* don't change this */
#define MAX_STRING_SIZE 49

char to_lower(char c)
{
	if ('A' <= c && c <= 'Z')
		return c + 0x20;
	return c;
}

int bst_cmp_str_lexicographically(const void *key1, const void *key2)
{
	int rc, i, len;
	char *str1 = (char *)key1;
	char *str2 = (char *)key2;
	int len1 = strlen(str1);
	int len2 = strlen(str2);

	len = len1 < len2 ? len1 : len2;
	for (i = 0; i < len; ++i) {
		rc = to_lower(str1[i]) - to_lower(str2[i]);

		if (rc == 0)
			continue;
		return rc;
	}

	rc = to_lower(str1[i]) - to_lower(str2[i]);
	return rc;
}

void print_data(void *data)
{
	printf("%s\n", (char*)data);
}

int main(void)
{
	bst_tree_t *bst;
	int N = 0, task;
	char str[BUFSIZ];
	char buf[256];
	
	fgets(buf, 256, stdin);
	sscanf(buf, "%d\n", &N);
	fflush(stdout);

	bst = bst_tree_create(MAX_STRING_SIZE, bst_cmp_str_lexicographically);

	while (N--) {
		fgets(buf, 256, stdin);
		sscanf(buf, "%d", &task);
		memset(str, 0, BUFSIZ);

		switch (task) {
		case 1:
			sscanf(buf + 2, "%s\n", str);
			cleanup_example_string(str);
			bst_tree_insert(bst, str);
			break;
		case 2:
			sscanf(buf + 2, "%s\n", str);
			cleanup_example_string(str);
			bst_tree_remove(bst, str);
			break;
		case 3:
			bst_tree_print_inorder(bst, print_data);
			break;
		default:
			perror("Invalid task!");
		}
	}

	bst_tree_free(bst, free);

	return 0;
}
