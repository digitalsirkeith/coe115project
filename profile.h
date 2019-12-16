#ifndef PROFILE_HEADER_H
#define	PROFILE_HEADER_H

#include "util.h"
#include "eeprom.h"

struct profile_data {
    char name[16];
    unsigned int wins;
    unsigned int loss;
    enum peer_type type;
};

struct profile {
    struct profile_data data;
    unsigned int eeprom_addr;
    
    void (*_save)();
    void (*load)();
    void (*toggle_spi_mode)();
    void (*reset_data)();
};

void profile_save();
void profile_load();
void profile_toggle_spi_mode();
void profile_reset_data();

#endif
