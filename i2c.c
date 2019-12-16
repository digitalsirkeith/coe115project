#include "i2c.h"
#include "lcd.h"

extern struct lcd LCD;

struct i2c I2C = {
    .init       = i2c_init,
    .restart    = i2c_restart,
    .nack       = i2c_nack,
    .ack        = i2c_ack,
    .read       = i2c_read,
    .write      = i2c_write,
    .stop       = i2c_stop,
    .start      = i2c_start
};

void i2c_init()
{
    I2C1BRG = 37; //I2C1BRG = (Fcy/Fsck) - (Fcy/10Meg) - 1
                  // I2C1CON
    I2C1CONbits.I2CSIDL = 1;
    I2C1CONbits.ACKDT = 0;
    I2C1CONbits.A10M = 0;
    I2C1CONbits.A10M = 0;
    // IEC1
    IEC1bits.SI2C1IE = 1;
    // Enable I2C after configuration
    I2C1CONbits.I2CEN = 1;
}

void i2c_start()
{
    // Set Start Condition Enabled Bit
    I2C1CONbits.SEN = 1;
    // Wait for operation to finish by checking interrupt flag
    while (!IFS1bits.MI2C1IF);
    // Clear interrupt flag
    IFS1bits.MI2C1IF = 0;
}

void i2c_restart()
{
    // Set last five bits to zero
    I2C1CON &= 0xFFE0;
    // Set Repeated Start Condition Enabled bit
    I2C1CONbits.RSEN = 1;
    // Wait for operation to finish by checking interrupt flag
    while (!IFS1bits.MI2C1IF);
    // Clear interrupt flag
    IFS1bits.MI2C1IF = 0;
    
}

void i2c_stop()
{
    // Set last five bits to zero
    I2C1CON = I2C1CON & 0xFFE0;
    // Set Stop Condition Enabled bit
    I2C1CONbits.PEN = 1;
    // Wait for operation to finish by checking interrupt flag
    while (!IFS1bits.MI2C1IF);
    // Clear interrupt flag
    IFS1bits.MI2C1IF = 0;
}

void i2c_ack()
{
    // Set last five bits to zero
    I2C1CON &= 0xFFE0;
    // Set Acknowledge Data bit
    I2C1CONbits.ACKDT = 0;
    // Set Acknowledge Sequence Enabled bit
    I2C1CONbits.ACKEN = 1;
    // Wait for operation to finish by checking interrupt flag
    while (!IFS1bits.MI2C1IF);
    // Clear interrupt flag
    IFS1bits.MI2C1IF = 0;
}

void i2c_nack()
{
    // Set last five bits to zero
    I2C1CON = I2C1CON & 0xFFE0;
    // Set Acknowledge Data bit
    I2C1CONbits.ACKDT = 1;
    // Set Acknowledge Sequence Enabled bit
    I2C1CONbits.ACKEN = 1;
    // Wait for operation to finish by checking interrupt flag
    while (!IFS1bits.MI2C1IF);
    // Clear interrupt flag
    IFS1bits.MI2C1IF = 0;
}

int i2c_write(uint8_t byte)
{
    // Write byte to transmit buffer register
    I2C1TRN = byte;
    // Wait for operation to finish by checking interrupt flag
    while (!IFS1bits.MI2C1IF);
    // Clear interrupt flag
    IFS1bits.MI2C1IF = 0;
    // Return Acknowledge bit received
    
    return I2C1STATbits.ACKSTAT;
}

int i2c_read()
{
    // Set last five bits to zero
    I2C1CON &= 0xFFE0;
    // Set Receive Enable bit
    I2C1CONbits.RCEN = 1;
    // Wait for operation to finish by checking interrupt flag
    while (!IFS1bits.MI2C1IF);
    // Clear interrupt flag
    IFS1bits.MI2C1IF = 0;
    // Return receive buffer contents
    return I2C1RCV;
}