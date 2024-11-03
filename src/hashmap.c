#include "../include/hashmap.h"
#include <stdlib.h>

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
    struct Entry entry = { key, data, 1 };
    /* trying to insert */
    int is_occupied = map->buffer[bucket_index].is_occupied;
    int is_free = !is_occupied;
    if (is_free) {
        /* not a collision */
        map->buffer[bucket_index] = entry;
        map->size += 1;
        return;
    }
    /* handling collistion with linear probbing method */
    int curr_idx = bucket_index;
    while (curr_idx < map->capacity) {
        int new_bucket_index = curr_idx % map->capacity;
        int is_free = !map->buffer[new_bucket_index].is_occupied;
        if (is_free) {
            break;
        }
        curr_idx++;
    }
    map->buffer[curr_idx] = entry;
    map->size += 1;
}

void delete_entry(struct HashMap* map, const char* key)
{
    int bucket_idx = get_bucket_idx(map, key);

    map->buffer[bucket_idx].data = NULL;
    map->buffer[bucket_idx].key = NULL;
    map->buffer[bucket_idx].is_occupied = 0;
}

void move_buckets(struct HashMap* from, struct HashMap* to)
{
    for (int bucket_idx = 0; bucket_idx < from->size; bucket_idx++) {
        const char* key = from->buffer[bucket_idx].key;
        void* data = from->buffer[bucket_idx].data;
        insert(to, key, data);
    }
}

void reallocate_map(struct HashMap* map)
{
    int new_capacity = map->capacity * GROWTH_FACTOR;
    struct HashMap* new_hash_map = create_hash_map(new_capacity);
    move_buckets(map, new_hash_map);
    new_hash_map->size = map->size;
    map = new_hash_map;
}

const struct Entry* get_entry(struct HashMap* map, const char* key)
{
    int bucket_idx = get_bucket_idx(map, key);
    const struct Entry* entry = &map->buffer[bucket_idx];
    return entry;
}
