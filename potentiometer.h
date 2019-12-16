#ifndef POTENTIOMETER_TEMPLATE_H
#define	POTENTIOMETER_TEMPLATE_H

#include "util.h"

struct potentiometer {
    void (*init)();
    int (*read)(uint8_t bits);
};

void potentiometer_init();
int potentiometer_read(uint8_t bits);

#endif	/* XC_HEADER_TEMPLATE_H */
