#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"
#include "utils.h"

#define MIN(x, y) ((x) < (y) ? (x) : (y))

linked_list_t*
ll_create(unsigned int data_size)
{
    /* TODO */
    linked_list_t* ll = calloc(1, sizeof(*ll));
    DIE(!ll, "calloc list");

    ll->data_size = data_size;

    return ll;
}

static ll_node_t* get_nth_node(linked_list_t* list, unsigned int n)
{
    unsigned int len = list->size - 1;
    unsigned int i;
    ll_node_t* node = list->head;

    n = MIN(n, len);

    for (i = 0; i < n; ++i)
        node = node->next;

    return node;
}

static ll_node_t* create_node(const void* new_data, unsigned int data_size)
{
    ll_node_t* node = calloc(1, sizeof(*node));
    DIE(!node, "calloc node");

    node->data = malloc(data_size);
    DIE(!node->data, "malloc data");

    memcpy(node->data, new_data, data_size);

    return node;
}

/*
 * Pe baza datelor trimise prin pointerul new_data, se creeaza un nou nod care e
 * adaugat pe pozitia n a listei reprezentata de pointerul list. Pozitiile din
 * lista sunt indexate incepand cu 0 (i.e. primul nod din lista se afla pe
 * pozitia n=0). Daca n >= nr_noduri, noul nod se adauga la finalul listei. Daca
 * n < 0, eroare.
 */
void
ll_add_nth_node(linked_list_t* list, unsigned int n, const void* new_data)
{
    /* TODO */
    ll_node_t *new_node, *prev_node;

    if (!list)
        return;

    new_node = create_node(new_data, list->data_size);

    if (!n || !list->size) {
        new_node->next = list->head;
        list->head = new_node;
    } else {
        prev_node = get_nth_node(list, n - 1);
        new_node->next = prev_node->next;
        prev_node->next = new_node;
    }

    ++list->size;
}

/*
 * Elimina nodul de pe pozitia n din lista al carei pointer este trimis ca
 * parametru. Pozitiile din lista se indexeaza de la 0 (i.e. primul nod din
 * lista se afla pe pozitia n=0). Daca n >= nr_noduri - 1, se elimina nodul de
 * la finalul listei. Daca n < 0, eroare. Functia intoarce un pointer spre acest
 * nod proaspat eliminat din lista. Este responsabilitatea apelantului sa
 * elibereze memoria acestui nod.
 */
ll_node_t*
ll_remove_nth_node(linked_list_t* list, unsigned int n)
{
    /* TODO */
    ll_node_t *prev_node, *removed_node;

    if (!list || !list->size)
        return NULL;

    if (!n) {
        removed_node = list->head;
        list->head = removed_node->next;
        removed_node->next = NULL;
    } else {
        prev_node = get_nth_node(list, n - 1);
        removed_node = prev_node->next;
        prev_node->next = removed_node->next;
        removed_node->next = NULL;
    }

    --list->size;

    return removed_node;
}

/*
 * Functia intoarce numarul de noduri din lista al carei pointer este trimis ca
 * parametru.
 */
unsigned int
ll_get_size(linked_list_t* list)
{
    /* TODO */
    return !list ? 0 : list->size;
}

/*
 * Procedura elibereaza memoria folosita de toate nodurile din lista, iar la
 * sfarsit, elibereaza memoria folosita de structura lista si actualizeaza la
 * NULL valoarea pointerului la care pointeaza argumentul (argumentul este un
 * pointer la un pointer).
 */
void
ll_free(linked_list_t** pp_list)
{
    /* TODO */
    ll_node_t *node;

    if (!pp_list || !*pp_list)
        return;

    while ((*pp_list)->size) {
        node = ll_remove_nth_node(*pp_list, 0);
        free(node->data);
        free(node);
    }

    free (*pp_list);
    *pp_list = NULL;
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM
 * ca stocheaza int-uri. Functia afiseaza toate valorile int stocate in nodurile
 * din lista inlantuita separate printr-un spatiu.
 */
void
ll_print_int(linked_list_t* list)
{
    /* TODO */
    ll_node_t *node = list->head;

    for (; node; node = node->next)
        printf("%d ", *(int*)node->data);
    printf("\n");
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM
 * ca stocheaza string-uri. Functia afiseaza toate string-urile stocate in
 * nodurile din lista inlantuita, separate printr-un spatiu.
 */
void
ll_print_string(linked_list_t* list)
{
    /* TODO */
    ll_node_t *node = list->head;

    for (; node; node = node->next)
        printf("%s ", (char*)node->data);
    printf("\n");
}
