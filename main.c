#include <stddef.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "testalloc.h"

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

