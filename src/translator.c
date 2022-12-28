#include "mem.h"
#include "stack.h"
#include "bfi.h"
#include "translator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Funkctioon BF_increment_new on kood, mida käivitatakse konkreetse
   instruktsiooni käivitamisel.
*/
void BF_increment_run(struct BF_instruction_st *instruction, int *index) {
    /* Suurendame mälu väärtust vastavalt konstruktoris seatud väärtusele! */
    mem_add(instruction->increment);

    /* Suurendame instruktsiooniloendurit ühe võrra. */
    *index = *index + 1;
}

void BF_increment_printAsm(struct BF_instruction_st *instruction, int *index) {
    if (instruction->increment == 1) {
        printf("    ;;;; Instruktsioon +\n");
        printf("    call mem_inc\n");
    } else if (instruction->increment == -1) {
        printf("    ;;;; Instruktsioon -\n");
        printf("    call mem_dec\n");
    }
}

void BF_move_run(struct BF_instruction_st *instruction, int *index) {
    /* Suurendame mälu väärtust vastavalt konstruktoris seatud väärtusele! */
    mem_move(instruction->numberOfPos);

    /* Suurendame instruktsiooniloendurit ühe võrra. */
    *index = *index + 1;
}

void BF_move_printAsm(struct BF_instruction_st *instruction, int *index) {
    if (instruction->numberOfPos == 1) {
        printf("    ;;;; Instruktsioon >\n");
        printf("    call mem_right\n");
    } else if (instruction->numberOfPos == -1) {
        printf("    ;;;; Instruktsioon <\n");
        printf("    call mem_left\n");
    }
}

void BF_debug_run(struct BF_instruction_st *instruction, int *index) {
    /* Suurendame mälu väärtust vastavalt konstruktoris seatud väärtusele! */
    mem_printDebug();

    /* Suurendame instruktsiooniloendurit ühe võrra. */
    *index = *index + 1;
}

void BF_debug_printAsm(struct BF_instruction_st *instruction, int *index) {
    printf("    ;;;; Instruktsioon #\n");
    printf("    call mem_printDebug\n");
}

void BF_output_run(struct BF_instruction_st *instruction, int *index) {
    /* Suurendame mälu väärtust vastavalt konstruktoris seatud väärtusele! */
    char c = mem_get();
    putc(c, stdout);

    /* Suurendame instruktsiooniloendurit ühe võrra. */
    *index = *index + 1;
}

void BF_output_printAsm(struct BF_instruction_st *instruction, int *index) {
    printf("    ;;;; Instruktsioon .\n");
    printf("    call mem_get\n");
    printf("    push eax\n");
    printf("    call putchar\n");
    printf("    add esp, 4\n");
}

void BF_input_run(struct BF_instruction_st *instruction, int *index) {
    /* Suurendame mälu väärtust vastavalt konstruktoris seatud väärtusele! */
    /* Loeme märgi standardsisendist (kasutaja sisestab konsooli). */
    int c = getc(stdin);
    if (EOF == c) {
        /* Sisendi lõpu korral lõpetame interpretaatori töö. */
        printf("Sisendi lõpp!\n");
        return;
    }

    /* Lisame mällu loetud väärtuse. */
    mem_set(c);

    /* Suurendame instruktsiooniloendurit ühe võrra. */
    *index = *index + 1;
}

void BF_input_printAsm(struct BF_instruction_st *instruction, int *index) {
    printf("    ;;;; Instruktsioon ,\n");
    printf("    call getchar\n");
    printf("    push eax\n");
    printf("    call mem_set\n");
    printf("    add esp, 4\n");
}

void BF_beginLoop_run(struct BF_instruction_st *instruction, int *index) {
    int val = mem_get();

    if (instruction->loopForwardIndex < 0) {
        printf("Tsükli algus algväärtustamata!\n");
        return;
    }

    if (val == 0) {
        /* +1 lisamine on selleks, et me ei "hüppaks" tsükli lõpu
           instruktsioonile, vaid sellele järgnevale instruktsioonile. */
        *index = instruction->loopForwardIndex + 1;
    } else {
        ++*index;
    }
}

void BF_beginLoop_printAsm(struct BF_instruction_st *instruction, int *index) {
    printf("    ;;;; Instruktsioon [\n");
    printf("silt_%d:\n", *index);
    printf("    call mem_get\n");
    printf("    cmp eax, 0\n");
    printf("    je silt_%d\n", instruction->loopForwardIndex);
}

void BF_endLoop_run(struct BF_instruction_st *instruction, int *index) {
    int val = mem_get();

    if (instruction->loopBackIndex < 0) {
        printf("Tsükli lõpp algväärtustamata!\n");
        return;
    }

    if (val == 0) {
        /* Pole mõtet tsükli algusesse tagasi hüpata, sest tsüklit enam ei
         * täideta. */
        ++*index;
    } else {
        /* Mine tagasi tsükli algusesse. */
        *index = instruction->loopBackIndex;
    }
}

void BF_endLoop_printAsm(struct BF_instruction_st *instruction, int *index) {
    printf("    ;;;; Instruktsioon ]\n");
    printf("    jmp silt_%d\n", instruction->loopForwardIndex);
    printf("silt_%d:\n", *index);
}

/* Konstruktor funktsioon BF_increment_new loob uue struktuuri, mis suurendab
   aktiivse mäluala väärtust vastavalt parameetrina antud väärtusele, mis võib
   olla ka negatiivne.
*/
struct BF_instruction_st *BF_increment_new(int increment) {
    struct BF_instruction_st *new = NULL;

    /* Kontrollime väärtust, et vältida hilisemaid vigu. */
    if (increment == 0) {
        printf("Liitmisinstruktsiooni parameeter ei saa olla 0!");

        /* Sisuliselt tagastab nüüd funktsioon NULL'i. */
        goto cleanup;
    }

    new = malloc(sizeof(struct BF_instruction_st));
    if (new == NULL) {
        printf("Mälu küsimine ebaõnnestus.");
        goto cleanup;
    }

    /* Väärtustame inkremendi. */
    new->increment = increment;
    new->run = BF_increment_run;
    new->printAsm = BF_increment_printAsm;
cleanup:
    return new;
}

struct BF_instruction_st *BF_move_new(int numberOfPos) {
    struct BF_instruction_st *new = NULL;

    /* Kontrollime väärtust, et vältida hilisemaid vigu. */
    if (numberOfPos == 0) {
        printf("Liitmisinstruktsiooni parameeter ei saa olla 0!");

        /* Sisuliselt tagastab nüüd funktsioon NULL'i. */
        goto cleanup;
    }

    new = malloc(sizeof(struct BF_instruction_st));
    if (new == NULL) {
        printf("Mälu küsimine ebaõnnestus.");
        goto cleanup;
    }

    /* Väärtustame inkremendi. */
    new->numberOfPos = numberOfPos;
    new->run = BF_move_run;
    new->printAsm = BF_move_printAsm;
cleanup:
    return new;
}

struct BF_instruction_st *BF_debug_new() {
    struct BF_instruction_st *new = NULL;

    new = malloc(sizeof(struct BF_instruction_st));
    if (new == NULL) {
        printf("Mälu küsimine ebaõnnestus.");
        goto cleanup;
    }

    new->run = BF_debug_run;
cleanup:
    return new;
}

/* Konstruktor funktsioon BF_output_new loob uue struktuuri, mis suurendab
   aktiivse mäluala väärtust vastavalt parameetrina antud väärtusele, mis võib
   olla ka negatiivne.
*/
struct BF_instruction_st *BF_output_new() {
    struct BF_instruction_st *new = NULL;

    new = malloc(sizeof(struct BF_instruction_st));
    if (new == NULL) {
        printf("Mälu küsimine ebaõnnestus.");
        goto cleanup;
    }

    new->run = BF_output_run;
    new->printAsm = BF_output_printAsm;
cleanup:
    return new;
}

/* Konstruktor funktsioon BF_input_new loob uue struktuuri, mis suurendab
   aktiivse mäluala väärtust vastavalt parameetrina antud väärtusele, mis võib
   olla ka negatiivne.
*/
struct BF_instruction_st *BF_input_new() {
    struct BF_instruction_st *new = NULL;

    new = malloc(sizeof(struct BF_instruction_st));
    if (new == NULL) {
        printf("Mälu küsimine ebaõnnestus.");
        goto cleanup;
    }

    new->run = BF_input_run;
cleanup:
    return new;
}

/* Konstruktor funktsioon BF_beginLoop_new loob uue struktuuri, mis
   implementeerib tsüklite algust.

   NB! Oluline on märkida, et loopForwardIndex ei saa algväärtustatud
   sisulise väärtusega ja seda on vaja muuta hiljem!
*/
struct BF_instruction_st *BF_beginLoop_new(void) {
    struct BF_instruction_st *new = NULL;

    new = malloc(sizeof(struct BF_instruction_st));
    if (new == NULL) {
        printf("Mälu küsimine ebaõnnestus.");
        goto cleanup;
    }

    /* Hetkel pole teada kus asub tsükli lõpp, seega kasutame väärtust, mis
       ei saa korrektne olla.*/
    new->loopForwardIndex = -1;
    new->run = BF_beginLoop_run;
    new->printAsm = BF_beginLoop_printAsm;
cleanup:
    return new;
}

/* Konstruktor funktsioon BF_endLoop_new loob uue struktuuri, mis implementeerib
   tsüklite algust.

   NB! Oluline on märkida, et loopForwardIndex ei saa algväärtustatud
   sisulise väärtusega ja seda on vaja muuta hiljem!
*/
struct BF_instruction_st *BF_endLoop_new(int loopBackIndex) {
    struct BF_instruction_st *new = NULL;

    new = malloc(sizeof(struct BF_instruction_st));
    if (new == NULL) {
        printf("Mälu küsimine ebaõnnestus.");
        goto cleanup;
    }

    new->loopBackIndex = loopBackIndex;
    new->run = BF_endLoop_run;
    new->printAsm = BF_endLoop_printAsm;
cleanup:
    return new;
}

void parse(struct BF_instruction_st **inst_arr, char *program) {
    int i = 0;

    struct stack_st loop_stack = EMPTY_STACK;

    while (program[i] != 0) {
        /* Algväärtustame kõik instruktsioonid eelnevalt NULL'iga. */
        inst_arr[i] = NULL;
        switch (program[i]) {
            case BF_INCREASE:
                inst_arr[i] = BF_increment_new(1);
                break;

            case BF_DECREASE:
                inst_arr[i] = BF_increment_new(-1);
                break;

            case BF_RIGHT:
                inst_arr[i] = BF_move_new(1);
                break;

            case BF_LEFT:
                inst_arr[i] = BF_move_new(-1);
                break;

            case BF_DEBUG:
                inst_arr[i] = BF_debug_new();
                break;

            case BF_READ:
                inst_arr[i] = BF_input_new();
                break;

            case BF_PRINT:
                inst_arr[i] = BF_output_new();
                break;

            case BF_START_LOOP:
                inst_arr[i] = BF_beginLoop_new();
                stack_push(&loop_stack, i);
                break;

            case BF_END_LOOP: {
                int beginIndex = stack_pop(&loop_stack);
                inst_arr[i] = BF_endLoop_new(beginIndex);

                /* Uuendame ka tsükli algust, et seal oleks olemas info kus asub
                 * tsükli lõpp! */
                inst_arr[beginIndex]->loopForwardIndex = i;

                break;
            }

            default:;
                break;
                /* Ignoreerime sümboleid, mida me ei tunne. */
        }

        i++;
    }
    stack_free(&loop_stack);
}

void run(struct BF_instruction_st **inst_arr, int inst_arr_len) {
    int i = 0;
    while (1) {
        if (i < 0 || i >= inst_arr_len)
            break;
        if (inst_arr[i] != NULL) {
            inst_arr[i]->run(inst_arr[i], &i);
        } else {
            /* Suurendame indeksit iseseisvalt. */
            i++;
        }
    }
}

void printAsm(struct BF_instruction_st **inst_arr, int inst_arr_len) {

    printf("global main\n"
           "extern mem_add\n"
           "extern mem_move\n"
           "extern mem_inc\n"
           "extern mem_dec\n"
           "extern mem_left\n"
           "extern mem_right\n"
           "extern mem_get\n"
           "extern mem_set\n"
           "extern mem_printDebug\n\n"
           "extern putchar\n\n");

    printf("section .text\n");
    printf("main:\n");

    /* Käime läbi kõik instruktsioonid ja käivitame neil
       funktsiooni printAsm. */
    for (int i = 0; i < inst_arr_len; i++) {
        if (inst_arr[i] != NULL) {
            inst_arr[i]->printAsm(inst_arr[i], &i);
        }
    }

    /* Funktsiooni main lõpp. */
    printf("    ret\n");
}

void interpret2(char *program) {
    /* Leiame programmi lähtekoodi pikkuse. */
    int program_len = strlen(program);

    /* Teeme massiivi, mis hoiab viitasid, mida on kokku program_len tükku.
       Viitade algväärtustamine toimub parse() funktsioonis. Massiivi pikkus on
       võetud varuga */
    struct BF_instruction_st **inst_arr =
        malloc(sizeof(struct BF_instruction_st *) * program_len);

    /* Parsime sisendprogrammi, mille tulemus salvestatakse inst_arr massiivi.
     */
    parse(inst_arr, program);

    /* Käivitame programmi. */
    printAsm(inst_arr, program_len);

    /* Vabastame mälu */
    for (int i = 0; i < program_len; i++) {
        if (inst_arr[i] != NULL) {
            free(inst_arr[i]);
        }
    }

    free(inst_arr);
}