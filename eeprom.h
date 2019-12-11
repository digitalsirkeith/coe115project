#ifndef EEPROM_HEADER_H
#define	EEPROM_HEADER_H

#include "i2c.h"

struct ee_prom {
    struct i2c I2C;
    int (*read_byte)(unsigned int addr);
    void (*write_byte)(unsigned int addr, unsigned int data);
    void (*init)();
    int slave_address;
    
    void (*write_string)(unsigned int addr, char *string);
    void (*write_buffer)(unsigned int addr, void *buf, unsigned int buflen);
    
    void (*read_string)(unsigned int addr, char *string, unsigned int strlen);
    void (*read_buffer)(unsigned int addr, void *buf, unsigned int buflen);
};

void eeprom_init();
int eeprom_read_byte(unsigned int addr);
void eeprom_write_byte(unsigned int addr, unsigned int data);
void eeprom_write_string(unsigned int addr, char *string);
void eeprom_write_buffer(unsigned int addr, void *buf, unsigned int buflen);

void eeprom_read_string(unsigned int addr, char *string, unsigned int strlen);
void eeprom_read_buffer(unsigned int addr, void *buf, unsigned int buflen);

#endif
