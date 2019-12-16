#ifndef LED_HEADER_H
#define	LED_HEADER_H

#include "util.h"

struct led {
    void (*init)();
    void (*on)();
    void (*off)();
    void (*blink)();
};

void led_init();
void led_on();
void led_off();
void led_blink();

#endif

