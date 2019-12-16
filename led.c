#include "led.h"

struct led LED = {
    .init = led_init,
    .blink = led_blink,
    .on = led_on,
    .off = led_off
};

void led_init()
{
    TRIS_LED = 0;
}

void led_on()
{
    LIGHT = 1;
}

void led_off()
{
    LIGHT = 0;
}

void led_blink()
{
//    TODO: Output Compare for blinking slowly
}