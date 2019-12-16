#ifndef UTIL_HEADER_H
#define	UTIL_HEADER_H
#include <xc.h> // include processor files - each processor file is guarded.  

#define FCY 4000000
#include "libpic30.h"

/*
 *  SPI
 *  PEER_TYPE: Required such that the two boards has only one server and one client
 */

enum peer_type {
    MASTER,
    SLAVE
};

/*
 *  LCD
 *  Set below the configurations for the LCD
 */

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

/*
 *  Keypad
 *  Only two rows and three columns shall be functional
 */

#define R1 _LATA4
#define R2 _LATA3
#define C1 _RA2
#define C2 _RA1
#define C3 _RA0

#define TRIS_R1 _TRISA4
#define TRIS_R2 _TRISA3
#define TRIS_C1 _TRISA2
#define TRIS_C2 _TRISA1
#define TRIS_C3 _TRISA0

#define CNPUE_C1 _CN30PUE
#define CNPUE_C2 _CN3PUE
#define CNPUE_C3 _CN2PUE

/*
 * Button
 */

#define TRIS_BTN _TRISB13
#define BTN _RB13
#define CNPUE_BTN _CN13PUE

/*
 * LED
 * Blinking or Steady
 */

#define TRIS_LED    _TRISB14
#define LIGHT       _LATB14

//SPI
#define SDI__   _RB10
#define SCLK    _RB7
#define SDO_    _LAT11


void copy_str(const char *src, char *dst);

// Redefinitions
#define LCD     lcd
#define Game    game
#define Button  button
#define Pot     potentiometer
#define LED     led
#define Profile profile
#define I2C     i2c
#define EEPROM  ee_prom
#define Socket  socket
#define Keypad  keypad

#endif
