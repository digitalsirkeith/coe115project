/*
 * File:   vargas_lib.c
 * Author: ucl
 *
 * Created on October 25, 2019, 9:21 AM
 */

#include "lcd.h"

struct lcd LCD = {
    .data = {},
    .cursor = 0,
    
    .init = lcd_init,
    .send = {
        .bits4 = lcd_send4bits,
        .bits8 = lcd_send8bits,
        .character = lcd_sendchar
    },
    .set_cursor = lcd_cursor,
    .set_line = lcd_copy_string,
    .display = lcd_print,
    .print_string = lcd_print_string,
};


void io_init()
{
//    TIMER
    OSCCON = 0x2203;
    CLKDIV = 0x0000;
    T1CON = 0x0030; 
    TMR1 = 0;
    PR1 = 15624;
    _T1IF = 0;
    _T1IP = 1;
    _T1IE = 1;
    
//    TIMER2
    T2CON = 0x0030;
    TMR1 = 0;
    PR2 = 79;
    _T2IF = 0;
    _T2IP = 2;
    _T2IE = 1;
    
//    LED
    _TRISB13 = 0;
    __builtin_write_OSCCONL(OSCCON & 0xBF);
    _RP13R = 19;
    __builtin_write_OSCCONL(OSCCON | 0x40);
    
    OC2CON1 = 0;                                             // Clear registers
    OC2CON2 = 0;
    OC2CON2bits.SYNCSEL = 0x1F;               //Synchronized by itself
    OC2CON1bits.OCTSEL = 0x07;                  //Peripheral clock is the source for output Compare
    
//    ADC
    _TRISB15 = 1;
    AD1PCFG = 0xFFFF;
}

void lcd_init()
{
    int idx;
    TRIS_E  = 0;
    TRIS_RS = 0;
    TRIS_D7 = 0;
    TRIS_D6 = 0;
    TRIS_D5 = 0;
    TRIS_D4 = 0;
    
    RS = 0;
    E = 0;
    D7 = 0;
    D6 = 0;
    D5 = 0;
    D4 = 0;
    
    __delay_ms(15);
    LCD.send.bits4(0x3);
    
    __delay_us(4100);
    LCD.send.bits4(0x3);
    
    __delay_us(100);
    LCD.send.bits4(0x3);
    
    __delay_us(4100);
    LCD.send.bits4(0x2);
    
    
    __delay_ms(10);
    LCD.send.bits8(0, 0x28);
    
    __delay_ms(10);
    LCD.send.bits8(0, 0x8);
    
    __delay_ms(10);
    LCD.send.bits8(0, 0x1);
    
    __delay_ms(10);
    LCD.send.bits8(0, 0x6);
    
    __delay_ms(10);
    LCD.send.bits8(0, 0xf);
    
    __delay_ms(10);
    
    for (idx = 0; idx < LCD_DATA_LEN; idx++)
        LCD.data[idx] = ' ';
    LCD.cursor = 0;
}

void lcd_send4bits(uint8_t val)
{
    RS = 0;
    E = 1;
    
    D7 = (val & 0x8) > 0;
    D6 = (val & 0x4) > 0;
    D5 = (val & 0x2) > 0;
    D4 = (val & 0x1) > 0;
    
    E = 0;
}

void lcd_send8bits(uint8_t rs, uint8_t val)
{
    RS = rs & 0x1;
    E = 1;
    D7 = (val & 0x80) || 0;
    D6 = (val & 0x40) || 0;
    D5 = (val & 0x20) || 0;
    D4 = (val & 0x10) || 0;
    E = 0;
    
    __delay_us(100);
    
    E = 1;
    D7 = (val & 0x8) || 0;
    D6 = (val & 0x4) || 0;
    D5 = (val & 0x2) || 0;
    D4 = (val & 0x1) || 0;
    E = 0;
}

void lcd_sendchar(char c)
{
    RS = 0x1;
    E = 1;
    D7 = (c & 0x80) || 0;
    D6 = (c & 0x40) || 0;
    D5 = (c & 0x20) || 0;
    D4 = (c & 0x10) || 0;
    __delay_us(50);
    E = 0;
    
    __delay_us(100);
    
    E = 1;
    D7 = (c & 0x8) || 0;
    D6 = (c & 0x4) || 0;
    D5 = (c & 0x2) || 0;
    D4 = (c & 0x1) || 0;
    __delay_us(50);
    E = 0;
    __delay_us(50);
}

void lcd_cursor(int new_cursor)
{
    int idx;
    for (idx = LCD.cursor; idx < new_cursor + LCD_DATA_LEN; idx++)
        LCD.send.character(LCD.data[idx % 80]);
    LCD.cursor = new_cursor;
}

void lcd_copy_string(uint8_t line, char *str)
{
    int idx;
    line = line ? 40 : 0;
    for (idx = 0; str[idx]; idx++)
        LCD.data[idx + line] = str[idx];
    while (idx < 40)
        LCD.data[idx++ + line] = ' ';
}

void lcd_print()
{
    uint8_t idx = 0;
    for (idx = LCD.cursor; idx < LCD_DATA_LEN; idx++)
        LCD.send.character(LCD.data[idx]);
    for (idx = 0; idx < LCD.cursor; idx++)
        LCD.send.character(LCD.data[idx]);
}

void lcd_print_string(char *line1, char *line2)
{
    LCD.set_line(0, line1);
    LCD.set_line(1, line2);
    LCD.display();
}

void lcd_home()
{
    lcd_send8bits(0, 0x2);
    __delay_ms(50);
}

void lcd_clear()
{
    LCD.print_string("", "");
}

void struct_init(struct lcd *lcd)
{
    lcd -> init = lcd_init;
    lcd -> send.bits4 = lcd_send4bits;
    lcd -> send.bits8 = lcd_send8bits;
    lcd -> send.character = lcd_sendchar;
    
    lcd -> set_cursor = lcd_cursor;
    lcd -> set_line = lcd_copy_string;
    lcd -> display = lcd_print;
    lcd -> print_string = lcd_print_string;
    lcd -> clear = lcd_clear;
}