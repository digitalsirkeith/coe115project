#ifndef LCD_HEADER_H
#define	LCD_HEADER_H

#include "util.h"

#define LCD_DATA_LEN 80

void lcd_send4bits(uint8_t val);
void lcd_send8bits(uint8_t rs, uint8_t val);
void lcd_sendchar(char c);

void lcd_init();
void lcd_print_string(char *str, char *);
void lcd_print();
void lcd_cursor(int);
void lcd_copy_string(uint8_t line, char *str);
void lcd_clear();

struct SEND {
    void (*bits4)(uint8_t);
    void (*bits8)(uint8_t, uint8_t);
    void (*character)(char);
};

struct lcd {
    char data[LCD_DATA_LEN];
    int cursor;
    
    void (*init)();
    struct SEND send;
    
    void (*set_cursor)(int);
    void (*set_line)(uint8_t line, char *);
    void (*display)();
    void (*print_string)(char *, char *);
    void (*clear)();
};

void struct_init(struct lcd *lcd);

#endif	/* XC_HEADER_TEMPLATE_H */

