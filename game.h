#ifndef GAME_TEMPLATE_H
#define	GAME_TEMPLATE_H

#include "lcd.h"
#include "profile.h"
#include "keypad.h"
#include "button.h"
#include "led.h"
#include "potentiometer.h"
#include "spi.h"

enum game_mode {
    START,
    PROFILE,
    SETTINGS,
    RESET
};

struct game {
    void (*init)();
    void (*run)();
    void (*menu)();
    void (*intro)();
    void (*start)();
    void (*profile)();
    void (*settings)();
    void (*reset)();
    
    enum game_mode mode;
};

void game_init();
void game_run();
void game_menu();
void game_intro();
void game_start();
void game_profile();
void game_settings();
void game_reset();

#endif

