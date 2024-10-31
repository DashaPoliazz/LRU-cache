#include "../include/linked_list.h"
#include "../src/linked_list.c"
#include <assert.h>
#include <stdio.h>

void test_create_node__node_allocation() {
  // for primitive types:
  int fourty_two = 42;
  struct Node *node = create_node(sizeof(int), &fourty_two);
  int lhs = *(int *)node->value;
  int rhs = fourty_two;

  printf("test_create_node__node_allocation() -> primitive types");
  assert(lhs == rhs);
}

void test_create_node() { test_create_node__node_allocation(); }

// Main function to run the tests
int main() {
  printf("Running tests for create_node:\n");
  test_create_node();
  return 0;
}
