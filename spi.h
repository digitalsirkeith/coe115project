#ifndef SPI_HEADER_H
#define	SPI_HEADER_H

#include "util.h"
#include "profile.h"

struct spi {
    void (*init)();
    void (*enable)();
    int (*send)(int data);
    int (*receive)();
};

struct message {
    int data;
    uint8_t used;
};

void spi_init();
void spi_init_master();
void spi_init_slave();
void spi_enable();

int spi_send(int data);
int spi_receive();

#endif	