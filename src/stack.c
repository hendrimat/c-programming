#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

/* Funktsioon push saab parameetriks int tüüpi väärtuse, mille lisab
 * globaalsesse pinusse, kui selles on veel ruumi. Vastasel korral trükib
 * ekkraanile vea. Funktsioon ei tagasta midagi.
 */
void stack_push(struct stack_st *stack, int val) {
    /* Kontrollime kas pinus on veel ruumi, kui ei ole, siis trükime ekraanile
     * veateate. */
    if (stack->size == 0 || stack->arr == NULL) {
        /* Mälu pole allokeeritud. */

        /* Alustame ühest elemendist. */
        stack->size = 1;

        /* Allokeerime mälu vaid ühe (int tüüpi) elemendi jaoks. */
        stack->arr = malloc(sizeof(int) * stack->size);

        /* Kontrollime kas mälu küsimine õnnestus. */
        if (stack->arr == NULL) {
            printf("Mälu otsas!\n");
            return;
        }

        /* Antud hetkel ei saa elemente pinus olla. */
        stack->len = 0;
    } else if (stack->len == stack->size) {
        /* Peame mälu suurendama 2 korda, aga kasutame ajutisi muutujaid, sest
           mälu suuruse muutmine võib ebaõnnestuda. */
        int tmp_size = stack->size * 2;
        int *tmp_arr = NULL;

        tmp_arr = realloc(stack->arr, sizeof(int) * tmp_size);
        if (tmp_arr == NULL) {
            printf("Mäluala suuruse muutmine ebaõnnestus.\n");
            return;
        }
        /* Alles nüüd teame, et kõik õnnestus! */

        stack->arr = tmp_arr;
        stack->size = tmp_size;
    }

    /* Antud hetkel teame, et pinusse mahub veel vähemalt üks val. */
    stack->arr[stack->len] = val;

    /* Suurendame pinusse lisatud elementide arvu. */
    stack->len++;

    return;
}

/* Funktsioon stack_peek tagastab pinu pealmise elemendi ilma seda eemaldamata.
 * Kui pinu on tühi, siis see tagastab 0 väärtuse.
 */
int stack_peek(struct stack_st *stack) {
    if (stack->len == 0) {
        return 0;
    }

    int val = stack->arr[stack->len - 1];

    return val;
}

/* Funktsioon stack_pop ei saa ühtegi parameetrit ja tagastab globaalse pinu
 * pealmise elemendi, mille ta pinust eemaldab. Kui pinu on juba tühi, siis
 * funktsioon tagastab väärtuse 0.
 */
int stack_pop(struct stack_st *stack) {
    /* Teeme topelt kontrolli, kuigi piisaks vaid ühest, kas mälu on
     * allokeeritud. */
    if (stack->size == 0 || stack->arr == NULL) {
        /* Mälu pole allokeeritud. */

        /* Alustame ühest elemendist. */
        stack->size = 1;

        /* Allokeerime mälu vaid ühe (int tüüpi!!!) elemendi jaoks. */
        stack->arr = malloc(sizeof(int) * stack->size);

        /* Kontrollime kas mälu küsimine õnnestus. */
        if (stack->arr == NULL) {
            printf("Mälu otsas!\n");
            return 1;
        }

        /* Antud hetkel ei saa elemente pinus olla. */
        stack->len = 0;

        /* Pinu on tühi, tagastame väärtuse 0. */
        return 0;
    } else if (stack->len == 0) {
        stack_free(stack);
        /* Pinu on tühi, tagastame väärtuse 0. */
        return 0;
    } else if (stack->len <= (0.25 * stack->size)) {
        /* Peame mälu vähendama 4 korda, aga kasutame ajutisi muutujaid, sest
           mälu suuruse muutmine võib ebaõnnestuda. */
        int tmp_size = stack->size * 0.25;
        int *tmp_arr = NULL;

        tmp_arr = realloc(stack->arr, sizeof(int) * tmp_size);
        if (tmp_arr == NULL) {
            printf("Mäluala suuruse muutmine ebaõnnestus.\n");
            return 1;
        }
        /* Alles nüüd teame, et kõik õnnestus! */

        stack->arr = tmp_arr;
        stack->size = tmp_size;
    }

    /* Teame, et pinus on vähemalt üks val. */
    int val = stack->arr[stack->len - 1];

    /* Vähendame pinu elementide arvu. */
    stack->len--;

    if (stack->len == 0) {
        stack_free(stack);
    }

    /* Tagastame eemaldatud väärtuse. */
    return val;
}

void stack_free(struct stack_st *stack) {
    free(stack->arr);
    stack->arr = NULL;
    return;
}

/* Funktsioon stack_isEmpty tagastab tõeväärtuse (0-vale ja mitte 0 tõene)
 * vastavalt sellele kas pinu on tühi või mitte.
 */
int stack_isEmpty(struct stack_st *stack) { return !(stack->len > 0); }

/* Funktsioon stack_print trükib ekraanile kõik pinu elemendid eraldi reale
 * alustades ülemisest.
 */
void stack_print(struct stack_st *stack) {
    int i;

    for (i = 1; i <= stack->len; ++i) {
        int val = stack->arr[stack->len - i];
        printf("%d\n", val);
    }

    return;
}