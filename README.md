# CS-Project-2-Custom-Malloc
Implementing our own malloc(3), free(3), realloc(3) and calloc(3)  functions

## Overview

In this project, we implement our own malloc(3), free(3), realloc(3) and calloc(3) functions. The purpose of these functions is to allocate memory on the heap of a program. These re-implementations use the brk(2) and sbrk(2) system calls

## Setup and Initialization

Before utilizing the custom memory allocator, it's crucial to
- define which elements will define the bloc of memory
- initialize the heap using the `initialize_heap()` function. This function sets the global variable `heap_start` to `NULL`.
```c
void initialize_heap() ;
```

## Features

- **`malloc`:** Allocates a block of memory.
- **`free`:** Deallocates a previously allocated block of memory.
- **`calloc`:** Allocates memory and initialize to zero.
- **`realloc`:** Changes the size of the memory block.

## Memory Allocation Functions

### `malloc`

The `malloc` function allocates a block of memory of the specified size.

'''c
void* malloc(size_t size);
'''

- If the size is less than or equal to 0, the function returns `NULL`.
- Uses the `sbrk(2)` system call to increment the program's data space.
- Allocates a new memory block, updates its information, and adds it to the linked list.

### `free`

The `free` function frees the memory associated with a previously allocated block.

```c
void free(void* ptr);
```

- If `ptr` is `NULL`, the function does nothing.
- Retrieves the block information based on the provided pointer.
- Updates the linked list to remove the block.
- Uses the `brk(2)` system call to set the end of the data segment.

### `realloc`

The `realloc` function changes the size of the memory block pointed to by `ptr`.

```c
void* realloc(void* ptr, size_t size);
```

- If `ptr` is `NULL`, it behaves like `malloc(size)`.
- If `size` is 0, it behaves like `free(ptr)`.
- If the existing block is larger than the new size, it returns the original pointer.
- Allocates a new block, copies data from the old block, and frees the old block.

### `calloc`

The `calloc` function allocates memory for an array of elements, initializing them to zero.

```c
void* calloc(size_t nmemb, size_t size);
```

- Uses `malloc` to allocate memory.
- If successful, initializes all the allocated memory to zero using `memset`.

## Building and Testing

To build and test the custom memory allocator, follow these steps:

1. Clone the repository.
2. Include the custom malloc header in your source code:

   ```c
   #include "malloc.h"
   ```

3. Compile your program with the custom malloc implementation.

   ```bash
   gcc -o your_program your_program.c malloc.c
   ```

4. Execute your program and test the custom memory allocator.

## Project Structure

- `malloc.c`: Implementation of custom memory allocation functions.
- `malloc.h`: Header file containing function declarations and necessary includes.
- `main.c`: Example usage and testing of the custom memory allocator.

## Contributors

- [Inès Beaunoir]
- [Philomène Lamonnerie]





## Features

- **`malloc`:** Allocates a block of memory.
- **`free`:** Deallocates a previously allocated block of memory.
- **`calloc`:** Allocates memory and initialize to zero.
- **`realloc`:** Changes the size of the memory block.

## Getting Started

### Prerequisites

- This project relies on the `brk` and `sbrk` system calls. Ensure your system supports these calls (#include <unistd.h>).

### Compilation instructions


### Testing instructions




### Information
- What do the brk(2) and sbrk(2) system calls do ?
- Write a diagram of the process memory when users try to allocate data and identity the possible problems
- When allocating memory, what information should the program store ?
- What would be a naïve, unoptimized way to implement the memory allocation system ? Identity possible performance issues.
- How would you optimize this process with memory footprint in mind ? With time consumption in mind ?

