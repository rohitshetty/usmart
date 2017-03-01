#ifndef SERIAL_H
#define SERIAL_H


#include "../config.h"
#include<avr/io.h>

void serial_init(void);
void send_float(float);
void send_int(uint8_t);
void int_to_ascii(uint8_t);
void serial_send(char);
void serial_send_string(char*);

#endif
