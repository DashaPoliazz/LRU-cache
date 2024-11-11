#include "../include/linked_list.h"
#include "../include/lru_cashe.h"
#include <stdio.h>
#include <stdlib.h>

struct LRU* init_cache(int capacity)
{
    struct LinkedList* list = create_list();
    struct HashMap* lookup = create_hash_map(capacity * GROWTH_FACTOR);
    struct LRU* lru = (struct LRU*)calloc(1, sizeof(struct LRU));
    lru->cache = list;
    lru->lookup = lookup;
    lru->capacity = capacity;
    return lru;
};

void cache_insert(struct LRU* lru, char* key, void* value)
{
    /* inserting as head of list */
    int exist = has(lru->lookup, key);
    if (exist) {
        /* moving node from it's current position to the head of list */
        struct Node* node_to_move = (struct Node*)get_entry(lru->lookup, key)->data;
        move_to_head(lru->cache, node_to_move);
    } else {
        /* inserting to the head */
        struct ListValue* list_value = calloc(1, sizeof(struct ListValue));
        list_value->key = key;
        list_value->value = value;
        push_left(lru->cache, sizeof(struct ListValue), list_value);
        insert(lru->lookup, key, lru->cache->head);
        /* moving node from it's current position to the head of list */
        struct Node* node_to_move = (struct Node*)get_entry(lru->lookup, key)->data;
        move_to_head(lru->cache, node_to_move);

        lru->size += 1;
    }
    /* evicting extra node if it's needed */
    if (lru->size > lru->capacity) {
        struct Node* tail = pop_right(lru->cache);
        struct ListValue* tail_value = (struct ListValue*)tail->value;
        const char* key = tail_value->key;
        delete_entry(lru->lookup, key);
        lru->size -= 1;
    }
}

const void* cache_get(struct LRU* lru, char* key)
{
    /* hit */
    int exist = has(lru->lookup, key);
    if (exist) {
        /* moving node from it's current position to the head of list */
        struct Node* node_to_move = (struct Node*)get_entry(lru->lookup, key)->data;
        move_to_head(lru->cache, node_to_move);
        struct ListValue* node_value = (struct ListValue*)node_to_move->value;
        return node_value->value;
    }
    /* miss */
    return NULL;
}

void cache_remove(struct LRU* cache, char* key)
{
    int exists = has(cache->lookup, key);
    if (!exists) {
        return;
    }

    struct Entry* entry = (struct Entry*)get_entry(cache->lookup, key);
    struct Node* node_to_remove = (struct Node*)entry->data;
    remove_node(cache->cache, node_to_remove);
    free_entry(cache->lookup, entry);
    destroy_node(node_to_remove);
}

void clear_cache(struct LRU* cache)
{
    struct HashMap* lookup = cache->lookup;
    free_hashmap(lookup);

    struct LinkedList* list = cache->cache;
    struct Node* node_to_destroy = cache->cache->head;

    while (node_to_destroy != NULL) {
        destroy_node(node_to_destroy);
        node_to_destroy = node_to_destroy->next;
    }
}
