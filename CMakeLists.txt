# Set the minimum version of CMake
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(LRUCache VERSION 1.0)

# Set the C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

# Include directories for header files
include_directories(include)

# Source files for the LRU cache
set(SOURCES
    src/lru_cache.c
    src/linked_list.c
    src/hashmap.c
)

# Add the main library target
add_library(lru_cache STATIC ${SOURCES})

# Add test executable for LRU cache
add_executable(test_lru_cache tests/test_lru_cache.c)
target_link_libraries(test_lru_cache lru_cache)

# Add test executable for linked list
add_executable(test_linked_list tests/test_linked_list.c)
target_link_libraries(test_linked_list lru_cache)

# Add test executable for hashmap
add_executable(test_hashmap tests/test_hashmap.c)
target_link_libraries(test_hashmap lru_cache)

# Optionally, add a custom command to run tests after building
enable_testing()
add_test(NAME LRUCacheTest COMMAND test_lru_cache)
add_test(NAME LinkedListTest COMMAND test_linked_list)
add_test(NAME HashMapTest COMMAND test_hashmap)
