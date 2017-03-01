#include "main.h"

/*
PD2  positive response
PD3 negative response

PD4 left
PD5 right
PD6 down
PD7 right
*/

uint8_t brightness = 100;
volatile char datetime[21];
char hhmmss[9];

void init_hardware () {
	input_init();
	screen_init();
	serial_init();
	set_dutycycle(brightness);
	_delay_ms(500);
    RTCinit();

	// Initialize timers
	TCCR1B |=(1<<CS12)|(1<<WGM12);
	OCR1A = 46860;
	TIMSK |= (1<<OCIE1A);
    TCNT1=0;
	screen_clear();

}

int main(){

	init_hardware();

	sei();

    RTCSet("8841001140516"); //hhmmssDddmmyy

	while(1){
    	render_sentence_xy(hhmmss,15,2);
		set_cursor_bank(15,3);
		render_sentence_xy("`C Mysuru",27,3);

		screen_invert();
	}
	return 0;
}



ISR(INT0_vect){
	return;
}


ISR(USART_RXC_vect)
{
	// Code to be executed when the USART receives a byte here
}

ISR(TIMER1_COMPA_vect){
        RTCRead((char *)datetime);
        strcut((char *)datetime,hhmmss,0,8);
}
