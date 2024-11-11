# LRU Cache with HashMap Implementation

This repository contains a naive implementation of an **LRU Cache** (Least Recently Used Cache) combined with a custom **HashMap**. It includes a set of performance measurements and unit tests to evaluate the efficiency of basic operations like hashing, insertion, and retrieval.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Testing](#testing)
- [Implementation Details](#implementation-details)
  - [Hashing](#hashing)
  - [Insertion](#insertion)
  - [Reallocation](#reallocation)
- [Future Improvements](#future-improvements)
- [License](#license)

## Introduction

An **LRU Cache** is a data structure that keeps track of the most recently used items with limited capacity. Once the capacity is full, it discards the least recently used items. This implementation is achieved by combining a **HashMap** for fast key lookups and a **Linked List** to maintain the order of item usage.

This project demonstrates an implementation of the LRU Cache and a custom-built HashMap, which could be used as an exercise to understand fundamental data structures, including linked lists and hash tables.

## Features

- A **HashMap** implementation that supports dynamic reallocation.
- An **LRU Cache** implementation for efficient caching with O(1) insertion, deletion, and access.
- **Unit Tests** for various linked list, hash map, and LRU Cache operations.
- **Performance Measurement** scripts to compare the efficiency of operations.

## Installation

To compile and run the LRU Cache and HashMap implementation:

1. Clone this repository:
   ```sh
   git clone https://github.com/DashaPoliazz/LRU-cache 
   cd LRU-cache
   ```

2. Running make files:
   ```sh
   ./build.sh
   ```

3. Run the tests to verify the implementation:
   ```
   ./build/test_lru_cache
   ```

## Usage

The repository includes multiple tests that demonstrate different operations like **insertion**, **deletion**, and **lookup** for the **HashMap** and **LRU Cache**. Each test is available in `main.c`, and you can modify or add more tests to evaluate the behavior under different scenarios.

## Testing

The repository includes comprehensive unit tests for the following components:

- **Linked List** operations (push, pop, move to head).
- **HashMap** operations (insert, delete, reallocation, lookup).
- **LRU Cache** operations (insert, access, remove).

To run the tests:

```sh
./lru_cache
```

All the tests will print their status, and any assertion failure will be shown clearly for debugging purposes.

## Implementation Details

### Hashing

The **hash function** used is based on the classic `djb2` hashing algorithm, which is known for its simplicity and reasonable distribution. The function converts a string key into an unsigned long hash value.

```c
unsigned long hash(const char* str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}
```

### Insertion

Insertion in the **HashMap** follows a linear probing strategy if a collision occurs. The **Linked List** is used in the **LRU Cache** to keep track of the order of usage, allowing the cache to remove the least recently used item when the capacity is reached.

### Reallocation

When the load factor exceeds a certain threshold (`LOAD_FACTOR`), the HashMap resizes its capacity by a predefined **growth factor** (`GROWTH_FACTOR`). During resizing, all elements are rehashed and moved to the new map.

```c
void reallocate_map(struct HashMap* map) {
    int new_capacity = map->capacity * GROWTH_FACTOR;
    struct HashMap* new_map = create_hash_map(new_capacity);
    move_buckets(map, new_map);
    free(map->buffer);
    map->buffer = new_map->buffer;
    map->capacity = new_capacity;
    free(new_map);
}
```

## Future Improvements

- **Memory Management**: Improve memory management by ensuring all allocated memory is properly freed, especially for linked list nodes.
- **Advanced Hashing**: Explore better hashing strategies to reduce the likelihood of collisions and improve performance.
- **Benchmarking**: Include benchmarking against established hash map implementations (e.g., C++ STL or GLib Hash Table).
- **Concurrency**: Implement thread-safe versions of HashMap and LRU Cache for concurrent environments.

## License

This project is licensed under the MIT License. See the `LICENSE` file for more details.

---

Feel free to contribute or report issues on the [GitHub issues page](https://github.com/your-username/lru-hashmap/issues). If you have questions, suggestions, or ideas for improvements, don't hesitate to open a pull request or contact me.
