#ifndef RTC_H
#define RTC_H

#include "../config.h"
#include<avr/io.h>
#include "../peripheral_drivers/i2c.h"

void RTCinit(void);
void RTCSet(char *);
void RTCRead(char *);
#endif
