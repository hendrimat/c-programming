#include <stddef.h>

#ifndef __BFI_H__
#define __BFI_H__

enum instructions_e {
    BF_RIGHT = '>',
    BF_LEFT = '<',
    BF_INCREASE = '+',
    BF_DECREASE = '-',
    BF_READ = ',',
    BF_PRINT = '.',
    BF_START_LOOP = '[',
    BF_END_LOOP = ']',
    BF_DEBUG = '#'
};

void interpret(char *program) {
    int i = 0;
    struct stack_st loop_stack = EMPTY_STACK;
    while (program[i] != 0) {
        switch (program[i]) {
            case BF_INCREASE:
                mem_inc();
                break;
            case BF_DECREASE:
                mem_dec();
                break;
            case BF_RIGHT:
                mem_right();
                break;
            case BF_LEFT:
                mem_left();
                break;
            case BF_DEBUG:
                mem_printDebug();
                break;
            case BF_READ:
                mem_read();
                break;
            case BF_PRINT:
                mem_print();
                break;
            case BF_START_LOOP: {
                if (mem_get()) {
                    stack_push(&loop_stack, i);
                } else {
                    int counter = 1;
                    while (counter > 0) {
                        i++;
                        if (program[i] == BF_START_LOOP) {
                            counter++;
                        } else if (program[i] == BF_END_LOOP) {
                            counter--;
                        }
                    }
                }
                break;
            }
            case BF_END_LOOP:
                i = stack_pop(&loop_stack) - 1;
                break;
            default:;
        }

        i++;
    }
    stack_free(&loop_stack);
}

#endif