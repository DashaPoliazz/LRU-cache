#include "../include/lru_cashe.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void test_init()
{
    printf("test_init\n");
    int capacity = 100;
    struct LRU* lru = init_cache(capacity);
    assert(lru->size == 0);
    assert(lru->capacity == capacity);
    assert(lru->cache->head == NULL);
    assert(lru->cache->tail == NULL);
    assert(lru->lookup->size == 0);
}

void test_insert_one()
{
    printf("test_insert_one\n");
    int capacity = 100;
    struct LRU* lru = init_cache(capacity);

    char key_1[1] = { 'a' };
    int one = 1;
    cache_insert(lru, key_1, &one);

    assert(lru->size == 1);
    struct ListValue* head_value = (struct ListValue*)lru->cache->head->value;
    assert(*(int*)head_value->value == one);
}

void test_insert_many()
{
    printf("test_insert_many\n");
    int capacity = 10;
    struct LRU* lru = init_cache(capacity);

    for (int i = 0; i < 20; i++) {
        char* key = malloc(2);
        key[0] = (char)i + 1;
        key[1] = '\n';
        int* data = malloc(1);
        data[0] = i + 1;

        cache_insert(lru, key, data);
    }

    assert(lru->size == 10);

    struct Node* curr = lru->cache->head;
    int counter = 20;
    while (curr != NULL) {
        struct ListValue* list_value = (struct ListValue*)curr->value;
        int value = *(int*)list_value->value;
        assert(value == counter);
        counter -= 1;
        curr = curr->next;
    }
}

void test_clear_cashe()
{
    printf("test_clear_cache\n");

    int capacity = 10;
    struct LRU* lru = init_cache(capacity);

    for (int i = 0; i < 20; i++) {
        char* key = malloc(2);
        key[0] = (char)i + 1;
        key[1] = '\n';
        int* data = malloc(1);
        data[0] = i + 1;

        cache_insert(lru, key, data);
    }

    assert(lru->size == 10);

    clear_cache(lru);
}

int main()
{
    test_init();
    test_insert_one();
    test_insert_many();
    test_clear_cashe();
    return 0;
}
