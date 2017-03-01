#ifndef MAIN_H
#define MAIN_H

#include "config.h"
#include<avr/io.h>
#include<util/delay.h>
#include<avr/pgmspace.h>
#include<avr/interrupt.h>
#include<avr/sleep.h>
#include <string.h>

#include "peripheral_drivers/serial.h"
#include "peripheral_drivers/pwm.h"
#include "peripheral_drivers/i2c.h"

#include "device_drivers/screen.h"
#include "device_drivers/input.h"
#include "device_drivers/rtc.h"
#include "utils.h"

#endif
