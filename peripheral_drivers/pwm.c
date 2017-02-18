#define F_CPU 12000000UL
#include<avr/io.h>
#include "pwm.h"

void pwm_init(void){
	// inverted mode, fast pwm at prescaler set to 64
	TCCR0 = (1<<CS01)|(WGM01)|(1<<WGM00)|(1<<COM01)|(1<<COM00);
	DDRB |=(1<<PB3);
	PORTB |=(1<<PB3);
}

void set_dutycycle(uint8_t dutycycle){
	OCR0 = dutycycle;
}