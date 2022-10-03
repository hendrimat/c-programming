#include <stdio.h>
#include "mem.h"

struct mem_st mem = { 
    .arr = {0},
    .index = 0,
};

int mem_inc() {
    mem.arr[mem.index] += 1;
    return mem.arr[mem.index];
}

int mem_dec() {
    mem.arr[mem.index] -= 1;
    return mem.arr[mem.index];
}

int mem_left() {
    mem.index -= 1;
    if (mem.index < 0) {
        mem.index = MEM_SIZE + mem.index;
    }
    return mem.index;
}

int mem_right() {
    mem.index += 1;
    if (mem.index >= MEM_SIZE) {
        mem.index = mem.index - MEM_SIZE;
    }
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
    for (int i = 0; i < 9; ++i) {
        printf("%d ", mem.arr[mem.index]);
        mem_right();
    }
    printf("%d", mem.arr[mem.index]);
    for (int i = 0; i < 9; ++i) {
        mem_left();
    }

    return;
}