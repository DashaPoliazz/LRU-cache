#include "../include/linked_list.h"
#include <assert.h>
#include <stdio.h>

void test_create_node()
{
    printf("test_create_node\n");
    // for primitive types:
    int fourty_two = 42;
    struct Node* node = create_node(sizeof(int), &fourty_two);
    int lhs = *(int*)node->value;
    int rhs = fourty_two;
    assert(lhs == rhs);
}

void test_create_list()
{
    printf("test_create_list\n");
    struct LinkedList* list = create_list();

    assert(list->head == NULL);
    assert(list->tail == NULL);
}

void test_push_right()
{
    printf("test_push_right\n");
    struct LinkedList* list = create_list();
    size_t data_size = sizeof(int);
    int one = 1;
    push_right(list, data_size, &one);

    assert(*(int*)list->tail->value == one);
    assert(*(int*)list->head->value == one);

    int two = 2;
    push_right(list, data_size, &two);

    assert(*(int*)list->tail->value == two);
    assert(*(int*)list->head->value == one);
}

void test_push_left()
{
    printf("test_push_left\n");
    struct LinkedList* list = create_list();
    size_t data_size = sizeof(int);
    int one = 1;
    push_left(list, data_size, &one);

    assert(*(int*)list->tail->value == one);
    assert(*(int*)list->head->value == one);

    int two = 2;
    push_left(list, data_size, &two);

    assert(*(int*)list->tail->value == one);
    assert(*(int*)list->head->value == two);
}

void test_pop_left()
{
    printf("test_pop_left\n");
    struct LinkedList* list = create_list();

    int one = 1;
    push_right(list, sizeof(int), &one);
    int two = 2;
    push_right(list, sizeof(int), &two);
    int three = 3;
    push_right(list, sizeof(int), &three);

    int it_should_be_one = *(int*)pop_left(list)->value;
    assert(it_should_be_one == one);

    int it_should_be_two = *(int*)pop_left(list)->value;
    assert(it_should_be_two == two);

    assert(list->head == list->tail);

    int it_should_be_three = *(int*)pop_left(list)->value;
    assert(it_should_be_three == three);

    assert(list->head == NULL);
    assert(list->tail == NULL);
}

void test_pop_right()
{
    printf("test_pop_right\n");
    struct LinkedList* list = create_list();

    int one = 1;
    push_right(list, sizeof(int), &one);
    int two = 2;
    push_right(list, sizeof(int), &two);
    int three = 3;
    push_right(list, sizeof(int), &three);

    int it_should_be_three = *(int*)pop_right(list)->value;
    assert(it_should_be_three == three);

    int it_should_be_two = *(int*)pop_right(list)->value;
    assert(it_should_be_two == two);

    assert(list->head == list->tail);

    int it_should_be_one = *(int*)pop_right(list)->value;
    assert(it_should_be_one == one);

    assert(list->head == NULL);
    assert(list->tail == NULL);
}

void test_is_empty()
{
    printf("test_is_empty\n");

    struct LinkedList* list = create_list();
    for (int i = 0; i < 10; i++) {
        int data = i + 1;
        size_t data_size = sizeof(int);
        push_right(list, data_size, &data);
    }

    assert(is_empty(list) == 0);

    for (int i = 0; i < 10; i++) {
        pop_right(list);
    }

    assert(is_empty(list) == 1);
}

int main()
{
    printf("Running tests for LRU Cache");
    test_create_node();
    test_push_right();
    test_push_left();
    test_pop_left();
    test_pop_right();
    test_is_empty();
    return 0;
}
