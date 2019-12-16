#include "potentiometer.h"

struct potentiometer Pot = {
    .init = potentiometer_init,
    .read = potentiometer_read
};

void potentiometer_init()
{
    _TRISB15 = 1;
    AD1CON1 = 0xE0; // set form to integer
    AD1CON2 = 0;
    AD1CHS = 0x0009;
    AD1CON3bits.SAMC = 2; // Tsamp
    AD1CON3bits.ADCS = 1; // Tad
    AD1CON1bits.ADON = 1;
}

int potentiometer_read(uint8_t bits)
{
    AD1CON1bits.SAMP = 1;
    while(!AD1CON1bits.DONE);
    AD1CON1bits.DONE = 0;
    return ADC1BUF0 >> (10 - bits);   
}