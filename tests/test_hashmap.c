#include "../src/hashmap.c"
#include <assert.h>
#include <signal.h>
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
        assert(entry.key == NULL);
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

void test_insert_many()
{
    printf("test_insert_many\n");

    int capacity = 100;
    struct HashMap* map = create_hash_map(capacity);

    /* preventing from reallocation */
    for (int i = 0; i < 74; i++) {
        char key[1] = { i };
        int data = i + 1;
        insert(map, key, &data);
    }

    // int* lookup = calloc(capacity, sizeof(int));

    for (int i = 0; i < capacity; i++) {
        struct Entry entry = map->buffer[i];
        printf("%i", *(int*)entry.data);
    }
}

int main()
{
    test_create_hashmap();
    test_insert_one();
    test_insert_many();
    return 0;
}
