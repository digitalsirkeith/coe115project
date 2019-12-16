#ifndef KEYPAD_HEADER_H
#define	KEYPAD_HEADER_H

#include "util.h" 

struct keypad {
    void (*init)();
    int (*read)();
    int value;
};

void keypad_init();
int keypad_read();

#endif
