#include "mem.h"
#include "stack.h"
#include "bfi.h"
#include "translator.h"
#include <stdio.h>
#include <stdlib.h>

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

int main(int argc, char **argv) {
    /* Kontrollime, et programmile anti täpselt üks parameeter (lisaks programmi
     * nimele endale). */
    if (argc != 2) {
        printf(
            "Programmil peab olema üks parameeter, milleks on BF programm!\n");

        /* Tagastame veakoodi. */
        return EXIT_FAILURE;
    }

    /* Käivitame programmi, mille kasutaja andis käsurealt. */
    interpret2(argv[1]);

    return EXIT_SUCCESS;
}