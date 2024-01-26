#include <stddef.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "testalloc.h"

// Structure of a bloc of memory 
struct mblock {
    size_t size;
    bool free;
    void* ptr;
    struct mblock* next;
    struct mblock* prev;
};

// Global variable that will point to lastest block added to our linked list
static struct mblock* heap_start = NULL;

// Function to initialize the heap to NULL that will be used in the main() for tests and use
void initialize_heap() {
    heap_start = NULL;
}

// Our own function malloc() to allocate memory that takes size into parameters and return a pointer to the memory allocated
void* malloc(size_t size) {
    if (size <= 0) {
        //print "The size must be more than 0"
        return NULL;  // ERROR
    }

    struct mblock* block = sbrk(sizeof(struct mblock) + size); //use of sbrk() that increments the program's data space by (increment) bytes

    if (block == (void*)-1) {
        //print "Memory allocation failed (sbrk)"
        return NULL;  // sbrk failed ERROR
    }

    block->size = size;
    block->free = false;
    block->ptr = block + sizeof(struct mblock);  // point to the memory area after the memory block structure space (here the memory can be used)

    if (heap_start == NULL) { //if it is the first block created
        heap_start = block;
        block->prev = NULL; // no prev memory block
    } else {
        block->prev = heap_start;
        heap_start->next = block;
        heap_start = block; // lastest block added to the list
    }

    block->next = NULL; // no next block created yet

    return block->ptr;
}

// Our own function free() to free memory of an already existed memory block
void free(void* ptr) {
    if (ptr == NULL) {
        //print "There is no memory block to free"
        return;  // ERROR
    }

    struct mblock* block = (struct mblock*)ptr - sizeof(struct mblock); //from usable memory space to struct details
    
    block->free = true;  // mark the block as free

    if (block->prev != NULL) {
        block->prev->next = block->next;
    } else {
        heap_start = block->next;
    }

    if (block->next != NULL) {
        block->next->prev = block->prev;
    }

    brk(block); //use of brk() that sets the end of the data segment to the value specified by (addr)
}

// Our own function realloc() to reallocate memory
void* realloc(void* ptr, size_t size) {
    if (ptr == NULL) { // there is no memory block
        return malloc(size); //malloc() is used to allocate memory based on the size
    }

    if (size == 0) { // size=0 means that user wants to free
        //print "The size is 0, memory block is now free"
        free(ptr);
        return NULL;
    }

    struct mblock* block = (struct mblock*)ptr - 1;

    size_t new_size = sizeof(struct mblock) + size; // totalsize = size + size of stucture 

    if (new_size <= block->size) {
        return ptr;  // Existing block memory is bigger than the new size, so nothing is changed
        // To optimize maybe recreate 2 blocks (one with memory size/ one free)
    }

    // allocate a new block if size is bigger
    void* new_ptr = malloc(size);
    if (new_ptr == NULL) {
        return NULL;  // ERROR
    }

    // copy data from the old block to the new block with memcpy() function
    size_t copy_size = block->size - sizeof(struct mblock);
    if (size < copy_size) {
        copy_size = size;
    }
    memcpy(new_ptr, ptr, copy_size);

    
    free(ptr); //free the old block

    return new_ptr; //return new block
}

// Our own function calloc() to allocate memory and initialize to zero all the octets
void* calloc(size_t number, size_t size) {
    size_t total_size = number * size;
    void* ptr = malloc(total_size); //use of malloc() function to allocate memory

    if (ptr != NULL) {
        memset(ptr, 0, total_size); //use of memset() function to set all octets to 0
    }
    return ptr;
}

void print_memory_blocks() {
    struct mblock* current_block = heap_start;

// debug
    printf("\nHeapstart: %p\n\n", heap_start);
    while (current_block != NULL) {
        printf("Block: [Size: %zu, Free: %s]\n", current_block->size, current_block->free ? "Yes" : "No");
        printf("  Address: %p\n", current_block->ptr);

        //exceptions case if prev is NULL or next is NULL 
        //we add sizeof(struct mblock) to show where the adress of usable memory actually start
        if (current_block->prev != NULL && current_block->next != NULL) {
        printf("  Prev: %p, Next: %p\n", current_block->prev + sizeof(struct mblock), current_block->next + sizeof(struct mblock));
        } else if (current_block->next == NULL && current_block->prev == NULL) {
        
        printf("  Prev: NULL, Next: NULL\n");
        }
        else if (current_block->prev == NULL) {
        
        printf("  Prev: NULL, Next: %p\n",  current_block->next + sizeof(struct mblock));
        }
        else if (current_block->next == NULL) {
        
        printf("  Prev: %p, Next: NULL\n",  current_block->prev + sizeof(struct mblock));
        }
        
        printf("");

        current_block = current_block->prev;
    }
}

int main() {
    initialize_heap();

    //size of struct
    printf("Size of the structure of mblock: %zu \n", sizeof(struct mblock));

    //TEST 1: allocate 1 memory block of size 20 and print blocks (there should be one block)
    void* block1 = malloc(20);
    printf("\nallocated 20 bytes for block 1:\n");
    print_memory_blocks();

    //TEST 2: allocate 1 more memory block of size 30 and print blocks (there should be 2 blocks)
    void* block2 = malloc(30);
    printf("\nallocated 30 bytes for block 2:\n");
    print_memory_blocks();

    //TEST 3: free the first block and print blocks (there should be 1 block : only the second block)
    free(block1);
    printf("\nfree block 1:\n");
    print_memory_blocks();

    //TEST 4: allocate 1 more memory block of size 15 and print blocks (there should be 2 blocks)
    void* block3 = malloc(15);
    printf("\nallocated 15 bytes for block 3:\n");
    print_memory_blocks();

    //TEST 5: reallocate memory of the second block by 50 and print blocks (there should be 2 blocks)
    void* block4 = realloc(block2, 50);
    printf("\nreallocated block 2 to 50 bytes for block 4:\n");
    print_memory_blocks();

    //TEST 6: Free all allocated memory blocks and print blocks (there should be 0 blcok)
    free(block2);
    free(block3);
    free(block4);
    printf("\nfreed all blocks.\n");
    print_memory_blocks();

    // TEST 7: Allocate memory using calloc and print blocks (there should be 1 block)
    void* block5 = calloc(1, 10);
    printf("\nallocated 10 bytes for block 5 using calloc:\n");
    print_memory_blocks();

    // TEST 8: Free the block allocated by calloc and print blocks (there should be 0 blocks)
    free(block5);
    printf("\nfreed block 5:\n");
    print_memory_blocks();

    return 0;
}

