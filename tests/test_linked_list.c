#include "../include/linked_list.h"
#include <assert.h>
#include <stdio.h>

void test_create_node() {
  printf("test_create_node\n");
  // for primitive types:
  int fourty_two = 42;
  struct Node *node = create_node(sizeof(int), &fourty_two);
  int lhs = *(int *)node->value;
  int rhs = fourty_two;
  assert(lhs == rhs);
}

void test_create_list() {
  printf("test_create_list\n");
  struct LinkedList *list = create_list();

  assert(list->head == NULL);
  assert(list->tail == NULL);
}

void test_push_right() {
  printf("test_push_right\n");
  struct LinkedList *list = create_list();
  size_t data_size = sizeof(int);
  int one = 1;
  push_right(list, data_size, &one);

  assert(*(int *)list->tail->value == one);
  assert(*(int *)list->head->value == one);

  int two = 2;
  push_right(list, data_size, &two);

  assert(*(int *)list->tail->value == two);
  assert(*(int *)list->head->value == one);
}

int main() {
  printf("Running tests for LRU Cache");
  test_create_node();
  test_push_right();
  return 0;
}
