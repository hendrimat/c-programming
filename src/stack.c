#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

/* Pinu struktuuri muutuja. */
struct stack_st stack = {.len = 0, .size = 0, .arr = NULL};

/* Funktsioon push saab parameetriks int tüüpi väärtuse, mille lisab globaalsesse pinusse, kui
 * selles on veel ruumi. Vastasel korral trükib ekkraanile vea. Funktsioon ei tagasta midagi.
 */
void stack_push(int element) {
	/* Kontrollime kas pinus on veel ruumi, kui ei ole, siis trükime ekraanile
	 * veateate. */
	if (stack.size == 0 || stack.arr == NULL) {
		/* Mälu pole allokeeritud. */

		/* Alustame ühest elemendist. */
        stack.size = 1;

		/* Allokeerime mälu vaid ühe (int tüüpi) elemendi jaoks. */
        stack.arr = calloc(stack.size, sizeof(int));
		
		/* Kontrollime kas mälu küsimine õnnestus. */
        if (stack.arr == NULL) {
           printf("Mälu otsas!\n");
           return;
        }

        /* Antud hetkel ei saa elemente pinus olla. */
        stack.len = 0;
	} else if (stack.len == stack.size) {
        /* Peame mälu suurendama 2 korda, aga kasutame ajutisi muutujaid, sest
           mälu suuruse muutmine võib ebaõnnestuda. */
        int tmp_size = stack.size * 2;
        int *tmp_arr = NULL;

        tmp_arr = realloc(stack.arr, tmp_size);
        if (tmp_arr == NULL) {
            printf("Mäluala suuruse muutmine ebaõnnestus.\n");
            return;
        }
        /* Alles nüüd teame, et kõik õnnestus! */

        stack.arr = tmp_arr;
        stack.size = tmp_size;
    }

	/* Antud hetkel teame, et pinusse mahub veel vähemalt üks element. */
	stack.arr[stack.len] = element;

	/* Suurendame pinusse lisatud elementide arvu. */
	stack.len++;

	return;
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

/* Funktsioon stack_pop ei saa ühtegi parameetrit ja tagastab globaalse pinu
 * pealmise elemendi, mille ta pinust eemaldab. Kui pinu on juba tühi, siis
 * funktsioon tagastab väärtuse 0.
 */
int stack_pop(void) {
	/* Teeme topelt kontrolli, kuigi piisaks vaid ühest, kas mälu on allokeeritud. */
    if (stack.size == 0 || stack.arr == NULL) {
        /* Mälu pole allokeeritud. */

        /* Alustame ühest elemendist. */
        stack.size = 1;

        /* Allokeerime mälu vaid ühe (int tüüpi!!!) elemendi jaoks. */
        stack.arr = malloc(sizeof(int) * stack.size);

        /* Kontrollime kas mälu küsimine õnnestus. */
        if (stack.arr == NULL) {
           printf("Mälu otsas!\n");
           return 1;
        }

        /* Antud hetkel ei saa elemente pinus olla. */
        stack.len = 0;

		/* Pinu on tühi, tagastame väärtuse 0. */
		return 0;
	} else if (stack.len == 0) {
		/* Pinu on tühi, tagastame väärtuse 0. */
		return 0;
	} else if (stack.len <= (0.25 * stack.size)) {
        /* Peame mälu vähendama 4 korda, aga kasutame ajutisi muutujaid, sest
           mälu suuruse muutmine võib ebaõnnestuda. */
        int tmp_size = stack.size * 0.25;
        int *tmp_arr = NULL;

        tmp_arr = realloc(stack.arr, tmp_size);
        if (tmp_arr == NULL) {
            printf("Mäluala suuruse muutmine ebaõnnestus.\n");
            return 1;
        }
        /* Alles nüüd teame, et kõik õnnestus! */

        stack.arr = tmp_arr;
        stack.size = tmp_size;
    }

	/* Teame, et pinus on vähemalt üks element. */
	int element = stack.arr[stack.len - 1];

	/* Vähendame pinu elementide arvu. */
	stack.len--;

	/* Tagastame eemaldatud väärtuse. */
	return element;
}

void stack_free() {
    stack.arr = realloc(stack.arr, 0);
    stack.size = 0;
    return;
}

/* Funktsioon stack_isEmpty tagastab tõeväärtuse (0-vale ja mitte 0 tõene)
 * vastavalt sellele kas pinu on tühi või mitte.
 */
int stack_isEmpty(void) { return !(stack.len > 0); }

/* Funktsioon stack_print trükib ekraanile kõik pinu elemendid eraldi reale
 * alustades ülemisest.
 */
void stack_print(void) {
	int i;

	for (i = 1; i <= stack.len; ++i) {
		int element = stack.arr[stack.len - i];
		printf("%d\n", element);
	}

	return;
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