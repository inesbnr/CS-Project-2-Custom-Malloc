# CS-Project-2-Custom-Malloc
Implementing our own malloc(3), free(3), realloc(3) and calloc(3)  functions

Contributors : Ines BEAUNOIR & Philomene LAMONNERIE

## Overview

In this project, we implement our own malloc(3), free(3), realloc(3) and calloc(3) functions. The purpose of these functions is to allocate memory on the heap of a program. These re-implementations use the brk(2) and sbrk(2) system calls

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

