#include <stdio.h>

#define mem_size 30000

struct mem_st {
    int len_start;
    int len_end;
    int arr[mem_size];
    int index;
};

struct mem_st mem = { .index = 0, .len_start = 0, .len_end = 0};

void mem_init() {
    if (mem.index < mem.len_start) {
        mem.arr[mem.index] = 0;
        mem.len_start -= 1;
    } else if (mem.index >= mem.len_end) {
        mem.arr[mem.index] = 0;
        mem.len_end += 1;
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
    
    int i;

    for (i = 0; i < 10; ++i) {
        int new_index = mem_right();
        printf("%d ", mem.arr[new_index - 1]);
    }

    printf("\n");
    return;
}