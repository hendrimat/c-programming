#include "mem.h"
#include <stdio.h>
#include <string.h>

struct mem_st mem = {
    .arr = {0},
    .index = 0,
};

int mem_add(int amount) {
    mem.arr[mem.index] += amount;
    return mem.arr[mem.index];
}

int mem_move(int numberOfPos) {
    mem.index += numberOfPos;
    if (mem.index < 0) {
        mem.index = MEM_SIZE + mem.index;
    } else if (mem.index >= MEM_SIZE) {
        mem.index %= MEM_SIZE;
    }
    return mem.index;
}

void mem_init() {
    memset(mem.arr, 0, MEM_SIZE * sizeof(char));
    mem.index = 0;
}

int mem_inc() { return mem_add(1); }

int mem_dec() { return mem_add(-1); }

int mem_left() { return mem_move(-1); }

int mem_right() { return mem_move(1); }

int mem_get() { return mem.arr[mem.index]; }

int mem_set(char v) {
    mem.arr[mem.index] = v;
    return v;
}

void mem_read() {
    /* Loeme märgi standardsisendist (kasutaja sisestab konsooli). */
    int c = getc(stdin);
    if (EOF == c) {
        /* Sisendi lõpu korral lõpetame interpretaatori töö. */
        printf("Sisendi lõpp!\n");
        return;
    }

    /* Lisame mällu loetud väärtuse. */
    mem_set(c);
}

void mem_print() {
    char c = mem_get();
    putc(c, stdout);
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