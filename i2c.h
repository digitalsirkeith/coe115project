#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include "util.h"

struct i2c {
    void (*init)();
    void (*start)();
    void (*restart)();
    void (*stop)();
    void (*ack)();
    void (*nack)();
    int (*write)(uint8_t byte);
    int (*read)();
};

void i2c_init();
void i2c_start();
void i2c_restart();
void i2c_stop();
void i2c_ack();
void i2c_nack();
int i2c_write(uint8_t byte);
int i2c_read();

#endif	/* XC_HEADER_TEMPLATE_H */

