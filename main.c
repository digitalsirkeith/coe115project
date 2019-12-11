#include "xc.h" // include processor files - each processor file is guarded.  

_CONFIG1 (FWDTEN_OFF & JTAGEN_OFF)
_CONFIG2 (POSCMOD_NONE & OSCIOFNC_ON & FCKSM_CSDCMD & FNOSC_FRCPLL & PLL96MHZ_OFF & PLLDIV_NODIV)
_CONFIG3 (SOSCSEL_IO)

#include "lcd.h"

extern struct lcd LCD;

int main(void) {
    LCD.init();
    LCD.set_cursor(12);
    
    while (1)
    {
        __delay_ms(500);
        if (_LATB13)
            LCD.print_string("Putangina", "ng CoE 115!");
        else
            LCD.print_string("Kold", "Bantutan");
        _LATB13 = ~_LATB13;
    }
    return 0;
}
