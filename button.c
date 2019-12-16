#include "button.h"

struct button Button = {
    .init = button_init,
    .read = button_read,
    .value = 1,
};

void button_init()
{
    _CN13PUE = 1;
    TRIS_BTN = 1;
}

int button_read()
{
    if (Button.value != BTN)
    {
        __delay_ms(50);
        Button.value = BTN;
    }
    return Button.value;
}