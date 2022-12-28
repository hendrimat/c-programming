#ifndef __TRANSLATOR_H__
#define __TRANSLATOR_H__

/* Selle struktuuriga esitame kõiki Brainfuck instruktsioone koos
   lisainfoga, mis võimaldavad optimeeringuid.
*/
struct BF_instruction_st {

    /* Instruktsiooni väljakutse funktsioon. Esimene parameeter on viit
       instruktsiooni objektile teine on viit instruktsiooni indeksile, mida
       antud funktsioon peab kas suurendama või muutma (näiteks tsüklites).
    */
    void (*run)(struct BF_instruction_st *instruction, int *index);

    /* Assembleri implementatsiooni funktsioon. Trükib välja vastava
       instruktsiooni implementatsiooni assembleris. */
    void (*printAsm)(struct BF_instruction_st *instruction, int *index);

    /* Implementatsiooni spetsiifilised väärtused. */
    union {
        /* Suurenda liitmisel väärtust selle võrra (võib olla ka negatiivne). */
        int increment;

        /* Mitu kohta tuleb mälu asukohta liigutada (võib olla ka negatiivne).
         */
        int numberOfPos;

        /* Indeks kuhu hüpata tsükli alguses kui getMem() == 0. */
        int loopForwardIndex;

        /* Indeks kuhu hüpata tagasi tsükli lõpus kui getMem() != 0. */
        int loopBackIndex;
    };
};

void interpret2(char *program);

void printAsm(struct BF_instruction_st **inst_arr, int inst_arr_len);

#endif