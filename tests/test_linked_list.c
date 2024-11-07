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

void test_move_to_head()
{
    printf("test_move_to_head\n");

    struct LinkedList* list = create_list();
    for (int i = 0; i < 10; i++) {
        int data = i + 1;
        size_t data_size = sizeof(int);
        push_right(list, data_size, &data);
    }

    struct Node* node = list->head;
    while (*(int*)node->value != 3) {
        node = node->next;
    }

    move_to_head(list, node);

    int direct_sequence[10] = { 3, 1, 2, 4, 5, 6, 7, 8, 9, 10 };
    int result[10] = {};

    int i = 0;
    struct Node* curr_head = list->head;
    while (curr_head != NULL) {
        result[i] = *(int*)curr_head->value;
        curr_head = curr_head->next;
        i++;
    }

    for (int i = 0; i < 10; i++) {
        assert(direct_sequence[i] == result[i]);
    }

    struct Node* curr_tail = list->tail;
    int j = 9;
    while (curr_tail != NULL) {
        assert(*(int*)curr_tail->value == result[j]);
        curr_tail = curr_tail->prev;
        j--;
    }
}

void test_move_to_head_corner_cases()
{
    printf("test_move_to_head_corner_cases\n");

    struct LinkedList* list = create_list();

    int one = 1;
    size_t data_size = sizeof(int);
    push_right(list, data_size, &one);

    move_to_head(list, list->head);
    assert(*(int*)list->head->value == one);
    assert(list->head->prev == NULL);
    assert(list->head->next == NULL);

    int two = 2;
    push_right(list, data_size, &two);

    move_to_head(list, list->head->next);
    assert(*(int*)list->head->value == two);

    // printf("head = %i", *(int*)list->head->value);
    // printf("head.next = %i", *(int*)list->head->next->value);
    assert(*(int*)list->head->next->value == one);
    // printf("head.next.prev = %i", *(int*)list->head->next->prev->value);
    assert(*(int*)list->head->next->prev->value == two);
    assert(list->head->prev == NULL);
}

void test_remove_head_eq_tail()
{
    printf("test_remove_head_eq_tail\n");

    struct LinkedList* list = create_list();

    int one = 1;
    size_t data_size = sizeof(int);
    push_right(list, data_size, &one);
    assert(list->head == list->tail);

    remove_node(list, list->head);
    assert(list->head == NULL);
    assert(list->tail == NULL);
}

void test_remove_head()
{
    printf("test_remove_head\n");

    struct LinkedList* list = create_list();

    int one = 1;
    size_t data_size = sizeof(int);
    push_right(list, data_size, &one);
    int two = 2;
    push_right(list, data_size, &two);
    int three = 3;
    push_right(list, data_size, &three);

    remove_node(list, list->head);
    assert(*(int*)list->head->value == 2);
    assert(list->head->prev == NULL);
}

void test_remove_tail()
{
    printf("test_remove_tail\n");

    struct LinkedList* list = create_list();

    int one = 1;
    size_t data_size = sizeof(int);
    push_right(list, data_size, &one);
    int two = 2;
    push_right(list, data_size, &two);
    int three = 3;
    push_right(list, data_size, &three);

    remove_node(list, list->tail);
    assert(*(int*)list->tail->value == 2);
    assert(*(int*)list->tail->prev->value == 1);
}

void test_remove_middle()
{
    printf("test_remove_middle\n");

    struct LinkedList* list = create_list();

    int one = 1;
    size_t data_size = sizeof(int);
    push_right(list, data_size, &one);
    int two = 2;
    push_right(list, data_size, &two);
    int three = 3;
    push_right(list, data_size, &three);

    remove_node(list, list->head->next);

    assert(*(int*)list->head->value == 1);
    assert(*(int*)list->tail->value == 3);
    assert(list->head->next == list->tail);
    assert(list->tail->prev == list->head);
}

void test_remove_node()
{
    printf("test_remove_head_eq_tail\n");
    test_remove_head_eq_tail();
    test_remove_head();
    test_remove_tail();
    test_remove_middle();
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
    test_move_to_head();
    test_move_to_head_corner_cases();
    test_remove_node();
    return 0;
}
