
// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef UTIL_HEADER_H
#define	UTIL_HEADER_H
#include <xc.h> // include processor files - each processor file is guarded.  

#define FCY 4000000
#include "libpic30.h"


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

#define R1 _LATB11
#define R2 _LATB10
#define C1 _RB9
#define C2 _RB8
#define C3 _RB7

#define TRIS_R1 _TRISB11
#define TRIS_R2 _TRISB10
#define TRIS_C1 _TRISB9
#define TRIS_C4 _TRISB8
#define TRIS_C5 _TRISB7

#endif	/* XC_HEADER_TEMPLATE_H */

