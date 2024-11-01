#include "../include/linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node *create_node(size_t data_size, void *data) {
  struct Node *node = (struct Node *)calloc(1, sizeof(struct Node));
  node->value = malloc(data_size);
  memcpy(node->value, data, data_size);

  node->prev = NULL;
  node->next = NULL;

  return node;
}

struct LinkedList *create_list() {
  struct LinkedList *list =
      (struct LinkedList *)calloc(1, sizeof(struct LinkedList));
  return list;
}

void push_right(struct LinkedList *list, size_t data_size, void *data) {
  if (list == NULL) {
    return;
  }

  struct Node *node = create_node(data_size, data);
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

void push_left(struct LinkedList *list, size_t data_size, void *data) {
  if (list == NULL) {
    return;
  }

  struct Node *node = create_node(data_size, data);
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

struct Node *pop_left(struct LinkedList *list) {
  if (list->head == NULL) {
    return NULL;
  }

  struct Node *head = list->head;
  struct Node *new_head = list->head->next;
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

struct Node *pop_right(struct LinkedList *list) {
  if (list->tail == NULL) {
    return NULL;
  }

  struct Node *tail = list->tail;
  struct Node *new_tail = list->tail->prev;
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

int is_empty(struct LinkedList *list) { return list->head == NULL ? 1 : 0; }

void destroy_node(struct Node *node) {
  if (node == NULL) {
    return;
  }
  free(node->value);
  free(node);
}
