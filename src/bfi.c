#include <stdio.h>
#include "mem.h"
#include "bfi.h"

int main(int argc, char **argv) {
    /* Kontrollime, et programmile anti täpselt üks parameeter (lisaks programmi nimele endale). */
    if (argc != 2) {
        printf("Programmil peab olema üks parameeter, milleks on BF programm!\n");

        /* Tagastame veakoodi. */
        return 1;
    }

    /* Käivitame programmi, mille kasutaja andis käsurealt. */
    interpret(argv[1]);

    return 0;
}