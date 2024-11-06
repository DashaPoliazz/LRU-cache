#include "../include/linked_list.h"
#include "../include/lru_cashe.h"
#include <stdlib.h>

struct LRU* init_cache(int capacity)
{
    struct LinkedList* list = create_list();
    struct HashMap* lookup = create_hash_map(capacity * GROWTH_FACTOR);
    struct LRU* lru = (struct LRU*)calloc(1, sizeof(struct LRU));
    lru->cache = list;
    lru->lookup = lookup;
    return lru;
};
void cache_insert(struct LRU* cache, char* key, void* value)
{
}
void* cache_get(struct LRU* cache, char* key)
{
}
void* cache_remove(struct LRU* cache, char* key)
{
}
void* clear_cache(struct LRU* cache)
{
}
