#ifndef __MEM_H__
#define __MEM_H__

#define MEM_SIZE 30000

struct mem_st {
    char arr[MEM_SIZE];
    int index;
};

/* Funktsioon, mis liidab aktiivsele mäluväljale parameetrina antud väärtuse,
 * mis võib olla ka negatiivne. Funktsioon tagastab aktiivse mäluvälja väärtuse.
 */
int mem_add(int amount);

/* Funktsioon liigutab aktiivset mäluvälja vasakule ja paremale ning tagastab
 * uue positsiooni.
 */
int mem_move(int numberOfPos);

/* Funktsioon nullib ära kõik mälu väljad ja liigutab aktiivse mäluala
 * indeksile 0. Neil, kes kasutasid mälu moodulis mingit sorti
 * initsialiseerimis funktsiooni on sisuliselt mem_init olemas, anname
 * sellele nüüd aga ühtse nime.
 */
void mem_init();

int mem_inc(void);

int mem_dec(void);

int mem_left(void);

int mem_right(void);

int mem_get(void);

int mem_set(char v);

void mem_print(void);

void mem_read(void);

void mem_printDebug(void);

#endif