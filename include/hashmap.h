#ifndef HASHMAP_H
#define HASHMAP_H
#define MAX_KEY_LENGTH 50

#include <stddef.h>

const int INITIAL_CAPACITY = 100;
const float LOAD_FACTOR = 0.75;
const int GROWTH_FACTOR = 2;

struct Entry
{
    char key[MAX_KEY_LENGTH];
    void* data;
    int is_occupied;
};

struct HashMap
{
    struct Entry* buffer;
    int capacity;
    int size;
};

unsigned long hash(const char* str);

struct HashMap* create_hash_map(int capacity);
int get_bucket_idx(struct HashMap* map, const char* key);
struct Entry create_entry(const char* key, void* data);
void insert(struct HashMap* map, const char* key, void* data);
void delete_entry(struct HashMap* map, const char* key);
const struct Entry* get_entry(struct HashMap* map, const char* key);

void move_buckets(struct HashMap* from, struct HashMap* to);
int needs_reallocation(struct HashMap* map);
void reallocate_map(struct HashMap* map);

#endif
