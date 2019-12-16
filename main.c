#include "xc.h" // include processor files - each processor file is guarded.  

_CONFIG1 (FWDTEN_OFF & JTAGEN_OFF)
_CONFIG2 (POSCMOD_NONE & OSCIOFNC_ON & FCKSM_CSDCMD & FNOSC_FRCPLL & PLL96MHZ_OFF & PLLDIV_NODIV)
_CONFIG3 (SOSCSEL_IO)

#include "game.h"

void test();
void test_master();
void test_slave();

extern struct game Game;
extern struct lcd LCD;
extern struct button Button;
extern struct potentiometer Pot;

extern struct ee_prom EEPROM;
extern struct profile Profile;
extern struct spi Socket;
extern struct led LED;

int main(void) {
//    test_master();
    test_slave();
    Game.init();
    Game.intro();
    
    while (1)
    {
        Game.menu();

        switch (Game.mode)
        {
            case START:
                LCD.print_string("Game Start", "");
                
                while (Button.read());
                break;
            case PROFILE:
                Game.profile();
                break;
            case SETTINGS:
                Game.settings();
                break;
            case RESET:
                Game.reset();
                break;
            default:
                break;
        }
    }
    
    return 0;
}

void test()
{
    LCD.init();
    EEPROM.init();
    EEPROM.read_byte(0x5f);
    EEPROM.write_byte(0x5f, 1);
    
//    Profile.load();
    LCD.print_string("KOLD", "KOLD");
    while (1);
}

void test_master()
{
    int a;
    AD1PCFG = 0xff;
    LED.init();
    
    Profile.data.type = MASTER;
    Socket.init();
    Socket.enable();
    while (1)
    {
        LIGHT = ~LIGHT;
        a = Socket.receive();
        a = 10 - a;
        Socket.send(a); 
        
        __delay_ms(1000);
    }
}

void test_slave()
{
    int a = 0;
    int b;
    AD1PCFG = 0xff;
    LCD.init();
    LCD.print_string("  KOLD", "SLAVE");
    EEPROM.init();
    Profile.load();
    Profile.data.type = SLAVE;
    Socket.init();
    Socket.enable();
    LCD.print_string("  KOLD", "SENDING");
    
    while (1)
    {
        Socket.send(a);
        b = Socket.receive();
        
        LCD.data[0] = (b % 10) + '0';
        LCD.display();
        a++;
    }
}