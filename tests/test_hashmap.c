#include "../src/hashmap.c"
#include <assert.h>
#include <stdio.h>

void test_create_hashmap()
{
    printf("test_create_hashmap\n");
    int capacity = 100;
    struct HashMap* map = create_hash_map(capacity);

    assert(map->capacity == 100);
    assert(map->size == 0);
    for (int i = 0; i < capacity; i++) {
        struct Entry entry = map->buffer[i];
        assert(entry.key[0] == '\0');
        assert(entry.data == NULL);
        assert(entry.is_occupied == 0);
    }
}

void test_insert_one()
{
    printf("test_insert_one\n");
    int capacity = 100;
    struct HashMap* map = create_hash_map(capacity);

    char* key_one = "one";
    int data_one = 1;

    insert(map, key_one, &data_one);
    assert(map->size == 1);

    for (int i = 0; i < 100; i++) {
        void* data = map->buffer[i].data;
        if (data == NULL) {
            continue;
        } else if ((int*)data) {
            continue;
        }
        /* should be never reached */
        assert(1 == 0);
    }
}

void test_hashing()
{
    printf("test_hashing\n");

    char* key_one = malloc(2);
    key_one[0] = '1';
    key_one[1] = '\n';
    char* key_two = malloc(2);
    key_two[0] = '1';
    key_two[1] = '\n';

    assert(hash(key_one) == hash(key_two));
}

void test_insert_many()
{
    printf("test_insert_many\n");

    const int THRESHOLD = 74;
    int capacity = 100;

    struct HashMap* map = create_hash_map(capacity);

    /* preventing from reallocation */
    for (int i = 0; i < THRESHOLD; i++) {
        char* key = malloc(2);
        key[0] = (char)i + 1;
        key[1] = '\n';
        int* data = malloc(1);
        data[0] = i + 1;
        insert(map, key, data);
    }

    int max = 0;
    for (int i = 0; i < capacity; i++) {
        char* key = malloc(2);
        key[0] = (char)i + 1;
        key[1] = '\n';
        const struct Entry* entry = get_entry(map, key);
        if (entry == NULL) {
            continue;
        }

        int value = *(int*)entry->data;
        if (value > max) {
            max = value;
        }
    }

    assert(max == THRESHOLD);
}

void test_reallocations()
{
    printf("test_reallocation");
    int default_capacity = 100;
    struct HashMap* map = create_hash_map(default_capacity);
    int old_capacity = map->capacity;

    for (int i = 0; i < default_capacity; i++) {
        char* key = malloc(2);
        key[0] = (char)i + 1;
        key[1] = '\n';
        int* data = malloc(1);
        data[0] = i + 1;
        insert(map, key, data);
    }

    assert(map->capacity == old_capacity * GROWTH_FACTOR);

    int max = 0;
    for (int i = 0; i < default_capacity; i++) {
        char* key = malloc(2);
        key[0] = (char)i + 1;
        key[1] = '\n';

        const struct Entry* entry = get_entry(map, key);
        if (entry == NULL) {
            continue;
        }

        int data = *(int*)entry->data;
        if (data > max) {
            max = data;
        }
    }

    assert(max == default_capacity);
}

int main()
{
    test_hashing();
    test_create_hashmap();
    test_insert_one();
    test_insert_many();
    test_reallocations();

    return 0;
}
