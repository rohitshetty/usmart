#ifndef AT_SLEEP_H
#define AT_SLEEP_H

#include "../../config.h"
#include<avr/io.h>
#include<avr/interrupt.h>
#include<avr/sleep.h>
#include<util/delay.h>
#include "../../device_drivers/screen/screen.h"
void goto_sleep(void);

#endif
