#ifndef __BFI_H__
#define __BFI_H__

enum instructions_e {
    BF_RIGHT      = '>',
    BF_LEFT       = '<',
    BF_INCREASE   = '+',
    BF_DECREASE   = '-',
    BF_READ       = ',',
    BF_PRINT      = '.',
    BF_START_LOOP = '[',
    BF_END_LOOP   = ']',
    BF_DEBUG      = '#'
};

void interpret(char *program) {
    int i = 0;
    while (program[i] != 0 ) {
        switch (program[i]) {
            case BF_INCREASE:
                mem_inc();
                break;
            case BF_DECREASE:
                mem_dec();
                break;
            case BF_RIGHT:
                mem_right();
                break;
            case BF_LEFT:
                mem_left();
                break;
            case BF_DEBUG:
                mem_printDebug();
                break;
            default:;
                /* Ignoreerime sümboleid, mida me ei tunne. */
        }

        i++;
    }
}

#endif