#ifndef MAIN_H
#define MAIN_H

#include "config.h"
#include<avr/io.h>
#include<util/delay.h>
#include<avr/pgmspace.h>
#include<avr/interrupt.h>
#include <string.h>

#include "peripheral_drivers/serial/serial.h"
#include "peripheral_drivers/pwm/pwm.h"
#include "peripheral_drivers/i2c/i2c.h"
#include "peripheral_drivers/sleep/at_sleep.h"

#include "device_drivers/screen/screen.h"
#include "device_drivers/input/input.h"
#include "device_drivers/rtc/rtc.h"
#include "utils/utils.h"

#include "apps/apps.mains.h"

/*
PD2  positive response
PD3 negative response

PD4 left
PD5 right
PD6 down
PD7 right
*/


#define PRESSED_INPUT_NEGATIVE (input_status & (1<<NEGAT))
#define PRESSED_INPUT_POSITIVE (input_status & (1<<POSIT))
#define PRESSED_INPUT_TOP (input_status & (1<<NAVI_TOP))
#define PRESSED_INPUT_DOWN (input_status & (1<<NAVI_DOWN))
#define PRESSED_INPUT_LEFT  (input_status & (1<<NAVI_LEFT))
#define PRESSED_INPUT_RIGHT (input_status & (1<<NAVI_RIGHT))

void menu_state_machine (void);
#endif
