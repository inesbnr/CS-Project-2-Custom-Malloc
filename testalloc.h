#ifndef TESTALLOC_H
#define TESTALLOC_H

#include <stddef.h>
#include <stdbool.h>

// Structure of a block of memory
struct mblock {
    size_t size;
    bool free;
    void* ptr;
    struct mblock* next;
    struct mblock* prev;
};

void initialize_heap();
void* malloc(size_t size);
void free(void* ptr);
void* realloc(void* ptr, size_t size);
void* calloc(size_t number, size_t size);
void print_memory_blocks();

#endif // TESTALLOC_H
