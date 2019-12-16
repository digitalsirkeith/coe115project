#include "game.h"

extern struct lcd           LCD;
extern struct ee_prom       EEPROM;
extern struct keypad        Keypad;
extern struct button        Button;
extern struct led           LED;
extern struct potentiometer Pot;
extern struct spi           Socket;
extern struct profile       Profile;

struct game Game = {
    .init       = game_init,
    .run        = game_run,
    .intro      = game_intro,
    .menu       = game_menu,
    .start      = game_start,
    .profile    = game_profile,
    .settings   = game_settings,
    .reset      = game_reset,
    
    .mode       = PROFILE
};

void game_init()
{
    AD1PCFG = 0xFDFF;
    
    LCD.init();
    LED.init();
    Button.init();
    EEPROM.init();
    Keypad.init();
    Pot.init();
    Profile.load();
    
    LCD.set_cursor(17);
}

void game_run()
{
    return;
}

void game_menu()
{
    int pot_val;
    
    char menu_list[][17] = {
        "Scroll using POT",
        "[1] Start Game",
        "[2] Profile",
        "[3] Settings",
        "[4] Reset"
    };
    
    while (1) {
        pot_val = Pot.read(2);
        LCD.print_string(menu_list[pot_val], menu_list[1 + pot_val]);
        
        Keypad.read();
        if (Keypad.value > 0 && Keypad.value <= 4)
            break;
    }
    
    switch (Keypad.value)
    {
        case 1:
            Game.mode = START;
            break;
        case 2:
            Game.mode = PROFILE;
            break;
        case 3:
            Game.mode = SETTINGS;
            break;
        case 4:
            Game.mode = RESET;
            break;
        default:
            break;
    }
}

void game_intro()
{
    LCD.print_string(
        "[Pixel Fighters]",
        "Push BTN to Play"
    );
    
    while (Button.read());
    LED.on();
}

void game_profile()
{
    LCD.set_line(0, Profile.data.name);
    LCD.set_line(1, "00 Win - 00 Loss");
    
    LCD.data[40] = '0' + (Profile.data.wins / 10);
    LCD.data[41] = '0' + (Profile.data.wins % 10);
    
    LCD.data[49] = '0' + (Profile.data.wins / 10);
    LCD.data[50] = '0' + (Profile.data.wins % 10);
    
    LCD.display();
    __delay_ms(200);
    while (Button.read() && Keypad.read() < 0);
}

void game_settings()
{
    char master[] = "MASTER";
    char slave[] = "SLAVE ";
    
    LCD.set_line(0, "SPI Mode:       ");
    LCD.set_line(1, "[1] Tog [2] Back");
    
    
    while (1)
    {
        if (Profile.data.type == MASTER)
            copy_str(master, LCD.data + 10);
        else
            copy_str(slave, LCD.data + 10);

        LCD.display();
        __delay_ms(200);
        while (Keypad.read() < 0 && Keypad.read() > 2);
        
        if (Keypad.value == 1)
            Profile.toggle_spi_mode();
        else if (Keypad.value == 2)
            break;
    }
}

void game_reset()
{
    LCD.print_string("Reset Data?", "[1] Yes [2] No");
    
    while (1)
    {
        Keypad.read();
        if (Keypad.value == 1)
        {
            Profile.reset_data();
            LCD.print_string("   Data reset!", "");
            __delay_ms(1000);
            break;
        }
        
        else if (Keypad.value == 2)
            break;
    }
}

void game_start()
{
    
}