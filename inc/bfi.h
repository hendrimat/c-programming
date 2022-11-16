#include <stddef.h>

#ifndef __BFI_H__
#define __BFI_H__

enum instructions_e {
    BF_RIGHT = '>',
    BF_LEFT = '<',
    BF_INCREASE = '+',
    BF_DECREASE = '-',
    BF_READ = ',',
    BF_PRINT = '.',
    BF_START_LOOP = '[',
    BF_END_LOOP = ']',
    BF_DEBUG = '#'
};

#endif