/*
 * File:   EEPROM.c
 * Author: ucl
 *
 * Created on December 11, 2019, 8:51 AM
 */

#include "eeprom.h"

struct ee_prom EEPROM = {
    .I2C = {
        .init       = i2c_init,
        .restart    = i2c_restart,
        .nack       = i2c_nack,
        .ack        = i2c_ack,
        .read       = i2c_read,
        .write      = i2c_write,
        .stop       = i2c_stop,
        .start      = i2c_start
    },
    
    .read_byte      = eeprom_read_byte,
    .write_byte     = eeprom_write_byte,
    .init           = eeprom_init,
    .slave_address  = 0xA0,
    
    .write_buffer   = eeprom_write_buffer,
    .write_string   = eeprom_write_string,
    
    .read_buffer    = eeprom_read_buffer,
    .read_string    = eeprom_read_string
};

void eeprom_init()
{
    EEPROM.I2C.init();
}

int eeprom_read_byte(unsigned int read_addr)
{
    uint8_t byte = 0;

    EEPROM.I2C.start();
    
    while (EEPROM.I2C.write(EEPROM.slave_address))
        EEPROM.I2C.restart();
    
    EEPROM.I2C.write(read_addr >> 8);
    EEPROM.I2C.write(read_addr);
    
    EEPROM.I2C.restart();
    EEPROM.I2C.write(EEPROM.slave_address + 1);
    
    byte = EEPROM.I2C.read();
    EEPROM.I2C.nack();
    EEPROM.I2C.stop();

    return byte;
}

void eeprom_write_byte(unsigned int addr, unsigned int data)
{
    EEPROM.I2C.start();
    
    while (EEPROM.I2C.write(EEPROM.slave_address + 0))
        EEPROM.I2C.restart();
    
    EEPROM.I2C.write(addr >> 8);
    EEPROM.I2C.write(addr);
    
    EEPROM.I2C.write(data);
    EEPROM.I2C.stop();
}

void eeprom_write_string(unsigned int addr, char *string)
{
    uint8_t idx;
    for (idx = 0; string[idx]; idx++)
        EEPROM.write_byte(addr + idx, string[idx]);
}

void eeprom_write_buffer(unsigned int addr, void *buf, unsigned int buflen)
{
    uint8_t idx;
    for (idx = 0; idx < buflen; idx++)
        EEPROM.write_byte(addr + idx, *(( (uint8_t *) buf ) + idx));
}

void eeprom_read_string(unsigned int addr, char *string, unsigned int strlen)
{
    EEPROM.read_buffer(addr, string, strlen);
    string[strlen] = 0;
}

void eeprom_read_buffer(unsigned int addr, void *buf, unsigned int buflen)
{
    uint8_t idx;
    for (idx = 0; idx < buflen; idx++)
        *(( (uint8_t *) buf ) + idx) = EEPROM.read_byte(addr + idx);
}