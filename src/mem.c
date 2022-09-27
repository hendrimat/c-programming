#include <stdio.h>
#include "mem.h"

struct mem_st mem = { 
    .index = 0, 
    .len_start = 0, 
    .len_end = 0
};

void mem_init() {
    if (mem.index < mem.len_start) {
        mem.arr[mem.index] = 0;
        mem.len_start -= 1;
    } else if (mem.index >= mem.len_end) {
        mem.arr[mem.index] = 0;
        mem.len_end += 1;
    }
    
    if (mem.index < 0) {
        mem.index = MEM_SIZE + mem.index;
    } else if (mem.index >= MEM_SIZE) {
        mem.index = mem.index - MEM_SIZE ;
    }

    return;
}

int mem_inc() {
    mem_init();
    mem.arr[mem.index] += 1;
    return mem.arr[mem.index];
}

int mem_dec() {
    mem_init();
    mem.arr[mem.index] -= 1;
    return mem.arr[mem.index];
}

int mem_left() {
    mem.index -= 1;
    mem_init();
    return mem.index;
}

int mem_right() {
    mem.index += 1;
    mem_init();
    return mem.index;
}

int mem_get() {
    return mem.arr[mem.index];
}

int mem_set(char v) {
    mem.arr[mem.index] = v;
    return v;
}

void mem_printDebug() {
    printf("index: %d mem [%d .. %d]: ", mem.index, mem.index, mem.index + 9);
    
/*   int i;*/

    for (int i = 0; i < 10; ++i) {
        int new_index = mem_right();
        printf("%d ", mem.arr[new_index - 1]);
    }

    printf("\n");
    return;
}