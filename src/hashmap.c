#include "../include/hashmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long hash(const char* str)
{
    unsigned long hash = 5381;   // Starting value
    int c;

    // Iterate through each character in the string
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;   // hash * 33 + c
    }

    return hash;   // Return the computed hash value
}

struct HashMap* create_hash_map(int capacity)
{
    struct HashMap* map = (struct HashMap*)calloc(1, sizeof(struct HashMap));
    struct Entry* buffer = (struct Entry*)calloc(capacity, (sizeof(struct Entry)));
    map->buffer = buffer;
    map->capacity = capacity;
    return map;
}

int needs_reallocation(struct HashMap* map)
{
    return (float)(map->size) / map->capacity >= LOAD_FACTOR;
}

int get_bucket_idx(struct HashMap* map, const char* key)
{
    unsigned long hashed_key = hash(key);
    int bucket_index = hashed_key % map->capacity;
    return bucket_index;
}

void insert(struct HashMap* map, const char* key, void* data)
{
    /* reallocating hasp map if needed */
    if (needs_reallocation(map)) {
        reallocate_map(map);
    }
    /* hashing key to obtain the number of a bucket */
    int bucket_index = get_bucket_idx(map, key);
    /* initializing entry */
    struct Entry entry;
    strncpy(entry.key, key, MAX_KEY_LENGTH - 1);
    entry.key[MAX_KEY_LENGTH - 1] = '\0';
    entry.data = data;
    entry.is_occupied = 1;

    /* trying to insert */
    int curr_idx = bucket_index;
    while (map->buffer[curr_idx].is_occupied) {
        curr_idx = (curr_idx + 1) % map->capacity;
    }

    map->buffer[curr_idx] = entry;
    map->size += 1;
}

void delete_entry(struct HashMap* map, const char* key)
{
    int bucket_idx = get_bucket_idx(map, key);

    map->buffer[bucket_idx].key[0] = '\0';
    map->buffer[bucket_idx].data = NULL;
    map->buffer[bucket_idx].is_occupied = 0;
}

void move_buckets(struct HashMap* from, struct HashMap* to)
{
    for (int bucket_idx = 0; bucket_idx < from->capacity; bucket_idx++) {
        struct Entry* entry = &from->buffer[bucket_idx];
        if (!entry->is_occupied) {
            continue;
        }
        insert(to, entry->key, entry->data);
    }
}

void reallocate_map(struct HashMap* map)
{
    int new_capacity = map->capacity * GROWTH_FACTOR;
    struct HashMap* new_map = create_hash_map(new_capacity);
    move_buckets(map, new_map);
    free(map->buffer);
    /* reinit buffers */
    map->buffer = new_map->buffer;
    map->capacity = new_capacity;
    /* there is only a buffer lefts from the new_map */
    free(new_map);
}

const struct Entry* get_entry(struct HashMap* map, const char* key)
{
    int bucket_idx = get_bucket_idx(map, key);
    struct Entry* entry = &map->buffer[bucket_idx];
    if (strcmp(entry->key, key) == 0) {
        return entry;
    }

    /* Finding bucket */
    for (int i = 0; i < map->capacity; i++) {
        int curr_bucket = (bucket_idx + i) % map->capacity;
        struct Entry* entry = &map->buffer[curr_bucket];
        if (strcmp(entry->key, key) == 0) {
            return entry;
        }
    }

    return NULL;
}

void free_hashmap(struct HashMap* map)
{
    if (map != NULL) {
        free(map->buffer);
        free(map);
    }
}

int has(struct HashMap* map, const char* key)
{
    const struct Entry* entry = get_entry(map, key);
    return entry == NULL ? 0 : 1;
}
