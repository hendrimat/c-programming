#ifndef __MEM_H__
#define __MEM_H__

#define MEM_SIZE 30000

struct mem_st {
    char arr[MEM_SIZE];
    int index;
};

int mem_inc(void);

int mem_dec(void);

int mem_left(void);

int mem_right(void);

int mem_get(void);

int mem_set(char v);

void mem_print(void);

void mem_read(void);

void mem_printDebug(void);

#endif