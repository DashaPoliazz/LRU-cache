#include <stdlib.h>

struct Node {
  void *value;
  struct Node *next;
  struct Node *prev;
};

struct Node *create_node(size_t data_size, void *data) {
  struct Node *node = (struct Node *)calloc(1, sizeof(struct Node));
  node->value = data;
  return node;
}

struct Page {
  int number;
};

int main() {
  struct Page *page = (struct Page *)calloc(1, sizeof(struct Page));
  struct Node *node = create_node(sizeof(page), page);

  return 0;
}
