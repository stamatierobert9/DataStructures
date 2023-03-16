/**
 * SD, 2021
 * 
 * Lab #9, BST & Heap
 * 
 * Task #1 - Test BST Implementation
 */

#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

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

    scanf("%d", &N);
    fflush(stdout);

    bst = bst_tree_create(MAX_STRING_SIZE, bst_cmp_str_lexicographically);

    while (N--) {
        scanf("%d", &task);
        memset(str, 0, BUFSIZ);

        switch (task) {
        case 1:
            scanf("%s", str);
            bst_tree_insert(bst, str);
            break;
        case 2:
            scanf("%s", str);
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
