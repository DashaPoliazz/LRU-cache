#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stddef.h>

struct Node {
  void *value;
  struct Node *prev;
  struct Node *next;
};

struct LinkedList {
  struct Node *head;
  struct Node *tail;
};

struct Node *create_node(size_t data_size, void *data);
struct LinkedList *create_list();
void push_right(struct LinkedList *list, size_t data_size, void *data);
void *pop_left(struct LinkedList *list);
void push_left(struct LinkedList *list, size_t data_size, void *data);
void *pop_right(struct LinkedList *list);
void *peek_head(struct LinkedList *list);
void *peek_tail(struct LinkedList *list);

#endif
