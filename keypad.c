#include "keypad.h"

struct keypad Keypad = {
    .read = keypad_read,
    .init = keypad_init,
    .value = -1
};

void keypad_init()
{
    CNPUE_C1 = 1;
    CNPUE_C2 = 1;
    CNPUE_C3 = 1;
    
    TRIS_C1 = 1;
    TRIS_C2 = 1;
    TRIS_C3 = 1;
    TRIS_R1 = 0;
    TRIS_R2 = 0;
}


void __reset_rows()
{
    R1 = 1;
    R2 = 1;
}

int __keypad_read()
{
    R1 = 0;
    R2 = 0;
    
    __delay_ms(50);
    
    if (C1 == 0)
    {
        R1 = 1;
        __delay_ms(50);
        if (C1)
            return 1;
        return 4;
    }
    
    else if (C2 == 0)
    {
        R1 = 1;
        __delay_ms(50);
        if (C2)
            return 2;
        return 5;
    }
    
    else if (C3 == 0)
    {
        R1 = 1;
        __delay_ms(50);
        if (C3)
            return 3;
        return 6;
    }
    
    return -1;
}

int keypad_read()
{
    Keypad.value = __keypad_read();
    __reset_rows();
    return Keypad.value;
}