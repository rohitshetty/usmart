#ifndef I2C_H
#define I2C_H


#include "../../config.h"
#include<avr/io.h>
#include<util/delay.h>
#include<util/twi.h>
#include<avr/interrupt.h>




#define MPU6050Addr 0x68
#define MPU6050ReadAddr 0xD1
#define MPU6050WriteAddr 0xD0

#define waitTillDone while(TWCR&(1<<TWINT)==0);
#define SCL_CLOCK 400000


// from peter flury

void TWIInit(void);

unsigned char i2c_start(unsigned char);
unsigned char i2c_write( unsigned char);
unsigned char i2c_readAck(void);
unsigned char i2c_readNak(void);
void i2c_stop(void);
void i2c_init(void);
unsigned char i2c_start(unsigned char);

#endif
