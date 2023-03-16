#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CircularDoublyLinkedList.h"
#include "utils.h"

#define MAX_STRING_SIZE 64

/*
 * Functie care trebuie apelata pentru alocarea si initializarea unei liste.
 * (Setare valori initiale pentru campurile specifice structurii LinkedList).
 */
doubly_linked_list_t*
dll_create(unsigned int data_size)
{
    doubly_linked_list_t* dll;

    dll = malloc(sizeof(*dll));
    DIE(dll == NULL, "doubly_linked_list malloc");

    dll->head = NULL;
    dll->data_size = data_size;
    dll->size = 0;

    return dll;
}

/*
 * Functia intoarce un pointer la nodul de pe pozitia n din lista.
 * Pozitiile din lista sunt indexate incepand cu 0 (i.e. primul nod din lista se
 * afla pe pozitia n=0). Daca n >= nr_noduri, atunci se intoarce nodul de pe
 * pozitia rezultata daca am "cicla" (posibil de mai multe ori) pe lista si am
 * trece de la ultimul nod, inapoi la primul si am continua de acolo. Cum putem
 * afla pozitia dorita fara sa simulam intreaga parcurgere?
 */
dll_node_t*
dll_get_nth_node(doubly_linked_list_t* list, unsigned int n)
{
    if (!list){
        return NULL;
    }
    if (!list->head){
        return NULL;
    }
    if (list->size == 0){
        return list->head;
    }

    dll_node_t* current = list->head;
    for (int i = 0; i < n % list->size; i++){
        current = current->next;
    }

    return current;
}

/*
 * Pe baza datelor trimise prin pointerul new_data, se creeaza un nou nod care e
 * adaugat pe pozitia n a listei reprezentata de pointerul list. Pozitiile din
 * lista sunt indexate incepand cu 0 (i.e. primul nod din lista se afla pe
 * pozitia n=0). Cand indexam pozitiile nu "ciclam" pe lista circulara ca la
 * get, ci consideram nodurile in ordinea de la head la ultimul (adica acel nod
 * care pointeaza la head ca nod urmator in lista). Daca n >= nr_noduri, atunci
 * adaugam nodul nou la finalul listei.
 */

void
dll_add_nth_node(doubly_linked_list_t* list, unsigned int n, const void* new_data)
{
    dll_node_t* current;
    dll_node_t* new_node;

    if(list == NULL){
        return;
    }

    if(n > list->size){
        n = list->size;
    }
    
    new_node = malloc(sizeof(*new_node));
    DIE(new_node == NULL, "new_node malloc");
    new_node->data = malloc(list->data_size);
    DIE(new_node->data == NULL, "new_node->data malloc");
    memcpy(new_node->data, new_data, list->data_size);

    list->size++;

    if(list->head == NULL) {
        list->head = new_node;
        new_node->next = new_node;
        new_node->prev = new_node;
        return;
    }

    if(n == 0){
        if (list->size == 1) {
            current = dll_get_nth_node(list, 0);
        } else 
            current = dll_get_nth_node(list, list->size - 2);
            list->head = new_node;
    } else {
        current = dll_get_nth_node(list, n - 1);
    }

    new_node->next = current->next;
    new_node->prev = current;
    current->next = new_node;
    new_node->next->prev = new_node;

}

/*
 * Elimina nodul de pe pozitia n din lista al carei pointer este trimis ca
 * parametru. Pozitiile din lista se indexeaza de la 0 (i.e. primul nod din
 * lista se afla pe pozitia n=0). Functia intoarce un pointer spre acest nod
 * proaspat eliminat din lista. Daca n >= nr_noduri - 1, se elimina nodul de la
 * finalul listei. Este responsabilitatea apelantului sa elibereze memoria
 * acestui nod.
 */
dll_node_t*
dll_remove_nth_node(doubly_linked_list_t* list, unsigned int n)
{
    dll_node_t* current;
    dll_node_t* remove;

    if(list == NULL) {
        return NULL;
    }

    if(list->head == NULL) {
        return NULL;
    }
    if(n > list->size - 1){
        n = list->size;
    }

    list->size--;

    if(n == 0) {
        if (list->size == 0){
            current = dll_get_nth_node(list, 0);
        } else {
            current = dll_get_nth_node(list, list->size - 1);
            list->head = list->head->next;
        }
    } else {
        current = dll_get_nth_node(list, n - 1);
    }

    remove = current->next;
    current->next = remove->next;
    remove->next->prev = current;
    return remove;
}

/*
 * Functia intoarce numarul de noduri din lista al carei pointer este trimis ca
 * parametru.
 */
unsigned int
dll_get_size(doubly_linked_list_t* list)
{
    if(list == NULL){
        return -1;
    }

    return list->size;
}

/*
 * Procedura elibereaza memoria folosita de toate nodurile din lista, iar la
 * sfarsit, elibereaza memoria folosita de structura lista.
 */
void
dll_free(doubly_linked_list_t** pp_list)
{
    dll_node_t* current_node;

    if(pp_list == NULL || *pp_list == NULL){
        return;
    }

    while (dll_get_size(*pp_list) > 0) {
        current_node = dll_remove_nth_node(*pp_list, 0);
        free(current_node->data);
        free(current_node);
    }

    free(*pp_list);
    *pp_list = NULL;
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM
 * ca stocheaza int-uri. Functia afiseaza o singura data toate valorile int
 * stocate in nodurile din lista, separate printr-un spatiu, incepand de la
 * nodul dat ca parametru si continuand la dreapta in lista dublu inlantuita
 * circulara, pana cand sunt afisate valorile tuturor nodurilor.
 */
void
dll_print_ints_right_circular(dll_node_t* start)
{
    dll_node_t* current = start;
    do{
        printf("%d ", *((int *)current->data));
        current = current->next;
    } while(current != start);

    printf("\n");
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM
 * ca stocheaza int-uri. Functia afiseaza toate valorile int stocate in nodurile
 * din lista separate printr-un spatiu, incepand de la primul nod din lista.
 */
void
dll_print_int_list(doubly_linked_list_t* list)
{
    dll_node_t* current;

    if(list == NULL){
        return;
    }

    current = list->head;
    for (int i = 0; i < list->size; i++){
        printf("%d ", *((int*)current->data));
        current = current->next;
    }

    printf("\n");
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM
 * ca stocheaza string-uri. Functia afiseaza o singura data toate valorile string
 * stocate in nodurile din lista, separate printr-un spatiu, incepand de la
 * nodul dat ca parametru si continuand la stanga in lista dublu inlantuita
 * circulara, pana cand sunt afisate valorile tuturor nodurilor.
 */
void
dll_print_strings_left_circular(dll_node_t* start)
{
    dll_node_t* current = start;
    do{
        printf("%s ", (char *)current->data);
        current = current->prev;
    } while(current != start);

    printf("\n");
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM
 * ca stocheaza string-uri. Functia afiseaza toate string-urile stocate in
 * nodurile din lista separate printr-un spatiu, incepand de la primul nod din
 * lista.
 */
void
dll_print_string_list(doubly_linked_list_t* list)
{
    dll_node_t* current;

    if(list == NULL){
        return;
    }

    current = list->head;
    for(int i = 0; i < list->size; i++) {
        printf("%s ", (char*)current->data);
        current = current->next;
    }

    printf("\n");
}

int main() {
    doubly_linked_list_t *doublyLinkedList;
    int is_int = 0;
    int is_string = 0;
    while(1) {
        char command[16], added_elem[MAX_STRING_SIZE], *end_ptr;
        long nr, pos;
        scanf("%s", command);
        if(strcmp(command, "create_str") == 0){
            doublyLinkedList = dll_create(MAX_STRING_SIZE);
            is_string = 1;
        }
        if(strcmp(command, "create_int") == 0){
            doublyLinkedList = dll_create(sizeof(int));
            is_int = 1;
        }
        if(strcmp(command, "add") == 0){
            scanf("%ld", &pos);

            if(is_int) {
                scanf("%ld", &nr);
                dll_add_nth_node(doublyLinkedList, pos, &nr);
            } else if(is_string) {
                scanf("%s", added_elem);
                dll_add_nth_node(doublyLinkedList, pos, added_elem);
            } else {
                printf("Create a list before adding elements!\n");
                exit(0);
            }
        }
        if(strcmp(command, "remove") == 0){
            if(!is_int && !is_string) {
                printf("Create a list before removing elements!\n");
                exit(0);
            }

            scanf("%ld", &pos);
            dll_node_t* removed = dll_remove_nth_node(doublyLinkedList, pos);
            free(removed->data);
            free(removed);
        }
        if(strcmp(command, "print") == 0){
            if(!is_int && !is_string) {
                printf("Create a list before printing!\n");
                exit(0);
            }

            if(is_int == 1){
                dll_print_int_list(doublyLinkedList);
            }
            if(is_string == 1){
                dll_print_string_list(doublyLinkedList);
            }
        }
        if(strcmp(command, "free") == 0){
            if(!is_int && !is_string) {
                printf("Create a list before freeing!\n");
                exit(0);
            }
            dll_free(&doublyLinkedList);
            break;
        }
    }
    return 0;
}
