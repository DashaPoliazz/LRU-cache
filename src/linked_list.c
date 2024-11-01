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

void *pop_left(struct LinkedList *list) {
  if (list->head == NULL) {
    return NULL;
  }

  struct Node *head = list->head;
  struct Node *new_head = head->next;
  /* the last node has been removed */
  if (new_head == NULL) {
    list->head = NULL;
    list->tail = NULL;
    return head->value;
  }
  /* establishing new connections */
  head->next = NULL;
  new_head->prev = NULL;
  list->head = new_head;

  return new_head->value;
}

void *pop_right(struct LinkedList *list) {}
void *peek_head(struct LinkedList *list) {}
void *peek_tail(struct LinkedList *list) {}
