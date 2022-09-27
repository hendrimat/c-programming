#include <stdio.h>
#include "stack.h"

/* Globaalse pinu massiivi pikkus. */
#define STACK_SIZE 100

/* Pinu struktuur, mis sisaldab nii pinu pikkust kui ka pinu ennast, mis on
   täisarvude massiiv.
*/
struct stack_st {
    int len;
    int arr[STACK_SIZE];
};

/* Pinu struktuuri muutuja. */
struct stack_st stack = { .len = 0};

/* Funktsioon stack_push saab parameetriks int tüüpi väärtuse, mille lisab globaalsesse pinusse, kui
 * selles on veel ruumi. Vastasel korral trükib ekraanile vea. Funktsioon ei tagasta midagi.
 */

void stack_push(int element) {
    /* Kontrollime kas pinus on veel ruumi, kui ei ole, siis trükime ekraanile veateate. */
    if (stack.len >= STACK_SIZE) {
        printf("Viga: pinusse rohkem elemente ei mahu\n");
        return;
    }

    /* Antud hetkel teame, et pinusse mahub veel vähemalt üks element. */
    stack.arr[stack.len] = element;

    /* Suurendame pinusse lisatud elementide arvu. */
    stack.len++;

    return;
}

/* Funktsioon stack_isEmpty tagastab tõeväärtuse (0-vale ja mitte 0 tõene) vastavalt sellele kas
 * pinu on tühi või mitte.
 */
int stack_isEmpty(void) {
    return !(stack.len > 0);
}

/* Funktsioon stack_peek tagastab pinu pealmise elemendi ilma seda eemaldamata.
 * Kui pinu on tühi, siis see tagastab 0 väärtuse.
 */
int stack_peek(void) {
    if (stack.len == 0) {
        return 0;
    }

    int element = stack.arr[stack.len - 1];

    return element;
}

/* Funktsioon stack_print trükib ekraanile kõik pinu elemendid eraldi reale alustades ülemisest.
 */
void stack_print(void) {
    int i;

    for (i = 1; i <= stack.len; ++i) {
        int element = stack.arr[stack.len - i];
        printf("%d\n", element);
    }

    return;
}

/* Funktsioon stack_pop ei saa ühtegi parameetrit ja tagastab globaalse pinu pealmise elemendi, mille ta
 * pinust eemaldab. Kui pinu on juba tühi, siis funktsioon tagastab väärtuse 0.
 */
int stack_pop(void) {
    /* Kontrollime, kas pinus on elemente. Kui ei ole, siis tagastame väärtuse 0. */
    if (stack.len == 0) {
        /* Pinu on tühi, tagastame väärtuse 0. */
        return 0;
    }

    /* Teame, et pinus on vähemalt üks element. */
    int element = stack.arr[stack.len - 1];

    /* Vähendame pinu elementide arvu. */
    stack.len--;

    /* Tagastame eemaldatud väärtuse. */
    return element;
}

/*
int main(void) {
    int input;

    while (1) {
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
*/