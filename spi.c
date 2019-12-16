#include "spi.h"

extern struct profile Profile;

struct spi Socket = {
    .init       = spi_init,
    .enable     = spi_enable,
    .send       = spi_send,
    .receive    = spi_receive
};

void spi_init()
{
    SPI1STAT = 0;
    SPI1CON1 = 0;
    SPI2CON2 = 0;
    
    SPI1CON1bits.CKE = 1;
    SPI1CON1bits.MODE16 = 1;
    
//  SPI Pin assignments
    __builtin_write_OSCCONL(OSCCON & 0xBF);
    _SCK1R = 7;
    _SDI1R = 10;
    _RP11R = 7;
    __builtin_write_OSCCONL(OSCCON | 0x40);
    
//  Specific Control Bits
    if (Profile.data.type == MASTER)
        SPI1CON1bits.MSTEN = 1;
    spi_enable();
}

void spi_enable()
{
    SPI1STATbits.SPIEN = 1;
}

int spi_send(int value)
{
    SPI1BUF = value;
    while (SPI1STATbits.SPITBF);
    while (!SPI1STATbits.SPIRBF);
    _SPI1IF = 0;
    return SPI1BUF;
}

int spi_receive()
{
    return spi_send(0);
}

//int spi_slave_send(int value)
//{
//    SPI1BUF = value;
//    
//    while (SPI1STATbits.SPITBF);
//    
//    _SPI1IF = 0;
//    
//    return SPI1BUF;
//}
