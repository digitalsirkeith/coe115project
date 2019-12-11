/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef LCD_HEADER_H
#define	LCD_HEADER_H

#include "util.h"

#define E _LATB5
#define RS _LATB4
#define D7 _LATB3
#define D6 _LATB2
#define D5 _LATB1
#define D4 _LATB0

#define TRIS_E  _TRISB5
#define TRIS_RS _TRISB4
#define TRIS_D7 _TRISB3
#define TRIS_D6 _TRISB2
#define TRIS_D5 _TRISB1
#define TRIS_D4 _TRISB0

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

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

