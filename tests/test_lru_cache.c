#include "../include/lru_cashe.h"
#include <assert.h>
#include <stdio.h>

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

int main()
{
    test_init();
    return 0;
}
