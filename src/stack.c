#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

/* Funktsioon push saab parameetriks int tüüpi väärtuse, mille lisab
 * globaalsesse pinusse, kui selles on veel ruumi. Vastasel korral trükib
 * ekkraanile vea. Funktsioon ei tagasta midagi.
 */
void stack_push(struct stack_st *s, int element) {
    /* Kontrollime kas pinus on veel ruumi, kui ei ole, siis trükime ekraanile
     * veateate. */
    if (s->size == 0 || s->arr == NULL) {
        /* Mälu pole allokeeritud. */

        /* Alustame ühest elemendist. */
        s->size = 1;

        /* Allokeerime mälu vaid ühe (int tüüpi) elemendi jaoks. */
        s->arr = calloc(s->size, sizeof(int));

        /* Kontrollime kas mälu küsimine õnnestus. */
        if (s->arr == NULL) {
            printf("Mälu otsas!\n");
            return;
        }

        /* Antud hetkel ei saa elemente pinus olla. */
        s->len = 0;
    } else if (s->len == s->size) {
        /* Peame mälu suurendama 2 korda, aga kasutame ajutisi muutujaid, sest
           mälu suuruse muutmine võib ebaõnnestuda. */
        int tmp_size = s->size * 2;
        int *tmp_arr = NULL;

        tmp_arr = realloc(s->arr, tmp_size);
        if (tmp_arr == NULL) {
            printf("Mäluala suuruse muutmine ebaõnnestus.\n");
            return;
        }
        /* Alles nüüd teame, et kõik õnnestus! */

        s->arr = tmp_arr;
        s->size = tmp_size;
    }

    /* Antud hetkel teame, et pinusse mahub veel vähemalt üks element. */
    s->arr[s->len] = element;

    /* Suurendame pinusse lisatud elementide arvu. */
    s->len++;

    return;
}

/* Funktsioon stack_peek tagastab pinu pealmise elemendi ilma seda eemaldamata.
 * Kui pinu on tühi, siis see tagastab 0 väärtuse.
 */
int stack_peek(struct stack_st *s) {
    if (s->len == 0) {
        return 0;
    }

    int element = s->arr[s->len - 1];

    return element;
}

/* Funktsioon stack_pop ei saa ühtegi parameetrit ja tagastab globaalse pinu
 * pealmise elemendi, mille ta pinust eemaldab. Kui pinu on juba tühi, siis
 * funktsioon tagastab väärtuse 0.
 */
int stack_pop(struct stack_st *s) {
    /* Teeme topelt kontrolli, kuigi piisaks vaid ühest, kas mälu on
     * allokeeritud. */
    if (s->size == 0 || s->arr == NULL) {
        /* Mälu pole allokeeritud. */

        /* Alustame ühest elemendist. */
        s->size = 1;

        /* Allokeerime mälu vaid ühe (int tüüpi!!!) elemendi jaoks. */
        s->arr = malloc(sizeof(int) * s->size);

        /* Kontrollime kas mälu küsimine õnnestus. */
        if (s->arr == NULL) {
            printf("Mälu otsas!\n");
            return 1;
        }

        /* Antud hetkel ei saa elemente pinus olla. */
        s->len = 0;

        /* Pinu on tühi, tagastame väärtuse 0. */
        return 0;
    } else if (s->len == 0) {
        stack_free(s);
        /* Pinu on tühi, tagastame väärtuse 0. */
        return 0;
    } else if (s->len <= (0.25 * s->size)) {
        /* Peame mälu vähendama 4 korda, aga kasutame ajutisi muutujaid, sest
           mälu suuruse muutmine võib ebaõnnestuda. */
        int tmp_size = s->size * 0.25;
        int *tmp_arr = NULL;

        tmp_arr = realloc(s->arr, tmp_size);
        if (tmp_arr == NULL) {
            printf("Mäluala suuruse muutmine ebaõnnestus.\n");
            return 1;
        }
        /* Alles nüüd teame, et kõik õnnestus! */

        s->arr = tmp_arr;
        s->size = tmp_size;
    }

    /* Teame, et pinus on vähemalt üks element. */
    int element = s->arr[s->len - 1];

    /* Vähendame pinu elementide arvu. */
    s->len--;

    /* Tagastame eemaldatud väärtuse. */
    return element;
}

void stack_free(struct stack_st *s) {
    free(s->arr);
    s->arr = NULL;
    return;
}

/* Funktsioon stack_isEmpty tagastab tõeväärtuse (0-vale ja mitte 0 tõene)
 * vastavalt sellele kas pinu on tühi või mitte.
 */
int stack_isEmpty(struct stack_st *s) { return !(s->len > 0); }

/* Funktsioon stack_print trükib ekraanile kõik pinu elemendid eraldi reale
 * alustades ülemisest.
 */
void stack_print(struct stack_st *s) {
    int i;

    for (i = 1; i <= s->len; ++i) {
        int element = s->arr[s->len - i];
        printf("%d\n", element);
    }

    return;
}