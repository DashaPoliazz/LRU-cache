#include "../include/linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node* create_node(size_t data_size, void* data)
{
    struct Node* node = (struct Node*)calloc(1, sizeof(struct Node));
    node->value = malloc(data_size);
    memcpy(node->value, data, data_size);

    node->prev = NULL;
    node->next = NULL;

    return node;
}

struct LinkedList* create_list()
{
    struct LinkedList* list = (struct LinkedList*)calloc(1, sizeof(struct LinkedList));
    return list;
}

void push_right(struct LinkedList* list, size_t data_size, void* data)
{
    if (list == NULL) {
        return;
    }

    struct Node* node = create_node(data_size, data);
    /* if there is no head, then we have to create it and init as tail */
    if (list->head == NULL) {
        list->head = node;
        list->tail = node;
        return;
    }

    /* otherwise, we have tail */
    node->prev = list->tail;
    list->tail->next = node;
    list->tail = node;
};

void push_left(struct LinkedList* list, size_t data_size, void* data)
{
    if (list == NULL) {
        return;
    }

    struct Node* node = create_node(data_size, data);
    /* if there is no head, then we have to create it and init as tail */
    if (list->head == NULL) {
        list->head = node;
        list->tail = node;
        return;
    }

    node->next = list->head;
    list->head->prev = node;
    list->head = node;
}

struct Node* pop_left(struct LinkedList* list)
{
    if (list->head == NULL) {
        return NULL;
    }

    struct Node* head = list->head;
    struct Node* new_head = list->head->next;
    /* there are only one node in list */
    if (new_head == NULL) {
        list->head = NULL;
        list->tail = NULL;
        return head;
    }

    /* updating head */
    list->head->next->prev = NULL;
    list->head->next = NULL;
    list->head = new_head;

    return head;
}

struct Node* pop_right(struct LinkedList* list)
{
    if (list->tail == NULL) {
        return NULL;
    }

    struct Node* tail = list->tail;
    struct Node* new_tail = list->tail->prev;
    /* there is onlye one node in list */
    if (new_tail == NULL) {
        list->head = NULL;
        list->tail = NULL;
        return tail;
    }

    /* updating tail */
    list->tail->prev->next = NULL;
    list->tail->prev = NULL;
    list->tail = new_tail;

    return tail;
}

int is_empty(struct LinkedList* list)

{
    return list->head == NULL ? 1 : 0;
}

void destroy_node(struct Node* node)
{
    if (node == NULL) {
        return;
    }
    free(node->value);
    free(node);
}

/* it should be guaranteed that node is in the list */
void move_to_head(struct LinkedList* list, struct Node* node)
{
    /* it's either the single node or it's in the head already */
    int is_single = node->next == NULL && node->prev == NULL;
    int is_head = list->head == node;
    if (is_single || is_head) {
        return;
    }

    /* moving from the tail */
    int is_tail = list->tail == node;
    if (is_tail) {
        /* there is guaranteed more than one node in the list and thus tail->prev != NULL */
        struct Node* new_tail = list->tail->prev;

        list->tail->next = NULL;
        list->tail->prev = NULL;

        list->head->prev = node;
        node->next = list->head;

        list->tail = new_tail;
        list->head = node;

        return;
    }
    /* moving from the middle */
    node->prev->next = node->next;
    node->next->prev = node->prev;
    node->prev = NULL;
    node->next = list->head;

    list->head->prev = node;
    list->head = node;
}

void remove_node(struct LinkedList* list, struct Node* node)
{
    if (node == NULL) {
        return;
    }

    if (node == list->head && node == list->tail) {
        list->head = NULL;
        list->tail = NULL;
        return;
    }

    /* there is no prev -> it's head */
    if (list->head == node) {
        struct Node* new_head = node->next;
        if (new_head != NULL) {
            node->next->prev = NULL;
            node->next = NULL;
        }
        list->head = new_head;
        return;
    }
    /* there is no next -> it's tail */
    if (list->tail == node) {
        /* it's guaranteed that head != tail */
        struct Node* new_tail = node->prev;
        node->prev->next = NULL;
        node->prev = NULL;
        list->tail = new_tail;
        return;
    }
    /* it's regular node */
    node->prev->next = node->next;
    node->next->prev = node->prev;
    node->prev = NULL;
    node->next = NULL;
}

void destroy_list(struct LinkedList* list)
{
    struct Node* node_to_destroy = list->head;
    while (node_to_destroy != NULL) {
        destroy_node(node_to_destroy);
        node_to_destroy = node_to_destroy->next;
    }
}
