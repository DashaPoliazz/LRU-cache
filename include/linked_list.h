#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stddef.h>

struct Node
{
    void* value;
    struct Node* prev;
    struct Node* next;
};

struct LinkedList
{
    struct Node* head;
    struct Node* tail;
};

struct Node* create_node(size_t data_size, void* data);
struct LinkedList* create_list();
void push_right(struct LinkedList* list, size_t data_size, void* data);
struct Node* pop_left(struct LinkedList* list);
void push_left(struct LinkedList* list, size_t data_size, void* data);
struct Node* pop_right(struct LinkedList* list);
int is_empty(struct LinkedList* list);
void destroy_node(struct Node* node);
void move_to_head(struct LinkedList* list, struct Node* node);
void remove_node(struct LinkedList* list, struct Node* node);
void destroy_list(struct LinkedList* list);

#endif
