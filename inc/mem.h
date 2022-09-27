#ifndef __MEM_H__
#define __MEM_H__

#define MEM_SIZE 30000

struct mem_st {
    int len_start;
    int len_end;
    char arr[MEM_SIZE];
    int index;
};

void mem_init(void);

int mem_inc(void);

int mem_dec(void);

int mem_left(void);

int mem_right(void);

int mem_get(void);

int mem_set(char v);

void mem_printDebug(void);

#endif