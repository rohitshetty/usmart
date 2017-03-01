#ifndef MAIN_H
#define MAIN_H

#include "config.h"
#include<avr/io.h>
#include<util/delay.h>
#include<avr/pgmspace.h>
#include<avr/interrupt.h>
#include<avr/sleep.h>
#include <string.h>

#include "peripheral_drivers/serial/serial.h"
#include "peripheral_drivers/pwm/pwm.h"
#include "peripheral_drivers/i2c/i2c.h"

#include "device_drivers/screen/screen.h"
#include "device_drivers/input/input.h"
#include "device_drivers/rtc/rtc.h"
#include "utils/utils.h"

#endif
