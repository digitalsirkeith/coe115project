#ifndef BUTTON_TEMPLATE_H
#define	BUTTON_TEMPLATE_H

#include "util.h"

struct button {
    void (*init)();
    int (*read)();
    int value;
};

void button_init();
int button_read();

#endif	
