#ifndef __STACK_H__
#define __STACK_H__

/* Pinu struktuur, mis sisaldab nii pinu elementide arvu kui ka pinu massivi ja
   selle massiivi reaalset pikkust.
*/
struct stack_st {
    /* Elementide arv, mis on pinusse lisatud. */
    int len;
    /* Massiivi mahtuvus - mitme elemendi jaoks on ruumi. */
    int size;
    /* Viit allokeeritud mälule. */
    int *arr;
};

#define EMPTY_STACK                                                            \
    (struct stack_st) { 0, 0, NULL }

/* Funktsioon push saab parameetriks int tüüpi väärtuse, mille lisab
 * globaalsesse pinusse, kui selles on veel ruumi. Vastasel korral trükib
 * ekraanile vea. Funktsioon ei tagasta midagi.
 */
void stack_push(struct stack_st *stack, int val);

/* Funktsioon pop ei saa ühtegi parameetrit ja tagastab globaalse pinu pealmise
 * elemendi, mille ta pinust eemaldab. Kui pinu on juba tühi, siis funktsioon
 * tagastab väärtuse 0.
 */
int stack_pop(struct stack_st *stack);

/* Funktsioon free vabastab allokeeritud mälu. */
void stack_free(struct stack_st *stack);

/* Funktsioon isEmpty tagastab tõeväärtuse (0-vale ja mitte 0 tõene) vastavalt
 * sellele kas pinu on tühi või mitte.
 */
int stack_isEmpty(struct stack_st *stack);

/* Funktsioon peek tagastab pinu pealmise elemendi ilma seda eemaldamata.
 * Kui pinu on tühi, siis see tagastab 0 väärtuse.
 */
int stack_peek(struct stack_st *stack);

/* Funktsioon print_stack trükib ekraanile kõik pinu elemendid eraldi reale
 * alustades ülemisest.
 */
void stack_print(struct stack_st *stack);

#endif