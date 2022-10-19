#include "mem.h"
#include "stack.h"
#include "bfi.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    /* Kontrollime, et programmile anti täpselt üks parameeter (lisaks programmi
     * nimele endale). */
    if (argc != 2) {
        printf(
            "Programmil peab olema üks parameeter, milleks on BF programm!\n");

        /* Tagastame veakoodi. */
        return EXIT_FAILURE;
    }

    /* Käivitame programmi, mille kasutaja andis käsurealt. */
    interpret(argv[1]);

    return EXIT_SUCCESS;
}