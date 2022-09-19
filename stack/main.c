#include <stdio.h>

/* Kasutame stack.h failis olevaid funktsioonide deklaratsioone. */
#include "stack.h"

int main(void) {
    /* Defineerime muutuja sisendi hoidmiseks, aga ei algväärtusta (väärtus võib olla juhuslik). */
    int input;

    /* Lõputu tsükkel, kus 1 on tõene tõeväärtus (võiks kirjutada ka näiteks 1 == 1 või 0 != 1, mis on alati tõesed. */
    while (1) {
        /* Loeme väärtuse funktsiooniga scanf, mis on sarnane funktsiooniga printf. */
        scanf("%d", &input);

        if (input == 0) {
            stack_print();
            break;
        } else if (stack_isEmpty()) {
            stack_push(input);
        } else if (input > 0) {
            if (stack_peek() > 0) {
                stack_push(input);
            } else {
                int element = stack_pop() + input;
                if (element != 0) {
                    stack_push(element);
                }
            }
        } else {
            int element = stack_pop() + input;
            if (element != 0) {
                stack_push(element);
            }
        }
    }

    return 0;
}