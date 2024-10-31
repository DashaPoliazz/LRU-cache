#include "../include/linked_list.h"
#include <stdlib.h>
#include <string.h>

struct Node *create_node(size_t data_size, void *data) {
  struct Node *node = (struct Node *)calloc(1, sizeof(struct Node));
  node->value = malloc(data_size);
  memcpy(node->value, data, data_size);

  node->left = NULL;
  node->right = NULL;

  return node;
}

struct LinkedList create_list() {
  struct LinkedList list;
  return list;
}

void push_right(struct LinkedList *list, size_t data_size, void *data) {
  struct Node *node = create_node(data_size, data);
  if (list->head == NULL) {
    list->head = node;
    list->tail = node;
    return;
  }
  list->tail = node;
};
void push_left(struct LinkedList *list, size_t data_size, void *data) {}
void *pop_left(struct LinkedList *list) {}
void *pop_right(struct LinkedList *list) {}
void *peek_head(struct LinkedList *list) {}
void *peek_tail(struct LinkedList *list) {}
