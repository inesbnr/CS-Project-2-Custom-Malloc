#ifndef IMPROVEDALLOC_H
#define IMPROVEDALLOC_H

#include <stddef.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

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

struct mblock* find_free_block(size_t size);

void free(void* ptr);

struct mblock* merge_blocks(struct mblock* first, struct mblock* second);

void* realloc(void* ptr, size_t size);

void* calloc(size_t number, size_t size);

void print_memory_blocks();

#endif  // IMPROVEDALLOC_H
