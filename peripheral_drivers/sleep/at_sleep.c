#include "at_sleep.h"

void goto_sleep(void) {
	MCUCSR &=~((1<<ISC00)|((1<<ISC01)));
	GICR = (1<<INT0);
	DDRC |= (1<<PC2);
	PORTC|=(1<<PC2);
	_delay_ms(500);
	PORTC&=~(1<<PC2);

	set_dutycycle(0);
	screen_clear();
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	sleep_enable();
	sleep_cpu();
	sleep_disable();
	_delay_ms(100);
	screen_clear();
	set_dutycycle(50);
	GICR &= ~(1<<INT0);
}
