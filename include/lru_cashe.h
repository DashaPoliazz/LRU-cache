
#ifndef LRU_CACHE
#define LRU_CACHE

#include "./hashmap.h"
#include "./linked_list.h"

struct LRU
{
    int size;
    int capacity;
    /* CacheElement => node */
    struct HashMap* lookup;
    struct LinkedList* cache;
};

struct ListValue
{
    const char* key;
    const void* value;
};

struct LRU* init_cache(int capacity);
void cache_insert(struct LRU* cache, char* key, void* value);
const void* cache_get(struct LRU* cache, char* key);
void cache_remove(struct LRU* cache, char* key);
void clear_cache(struct LRU* cache);

#endif
