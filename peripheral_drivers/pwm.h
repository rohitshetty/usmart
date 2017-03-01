#ifndef PWM_H
#define PWM_H

#include "../config.h"
#include<avr/io.h>

void pwm_init(void);

void set_dutycycle(uint8_t);

#endif
