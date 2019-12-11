#include "xc.h" // include processor files - each processor file is guarded.  

_CONFIG1 (FWDTEN_OFF & JTAGEN_OFF)
_CONFIG2 (POSCMOD_NONE & OSCIOFNC_ON & FCKSM_CSDCMD & FNOSC_FRCPLL & PLL96MHZ_OFF & PLLDIV_NODIV)
_CONFIG3 (SOSCSEL_IO)

#include "lcd.h"
#include "eeprom.h"

extern struct lcd LCD;
extern struct ee_prom EEPROM;

int main(void) {
    char arr[] = "2015-01481";
    char s[16];
    int addr = 0x0f;
    int i;
    
    EEPROM.init();
    LCD.init();
    
    EEPROM.write_string(addr, arr);    
    EEPROM.read_string(addr, s, 10);
    s[10] = 0;
    LCD.set_line(0, s);
    LCD.set_line(1, "KOLD");
    LCD.data[47] = LCD.data[10];
    
    LCD.display();
        
    while (1);
    
    return 0;
}
