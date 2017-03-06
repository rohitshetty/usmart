#include "main.h"

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
		render_sentence_xy("Mysuru",27,3);

		screen_invert();


		if(PRESSED_INPUT_NEGATIVE){
			goto_sleep(); // in utils
		}

		if (PRESSED_INPUT_POSITIVE) {
			menu_state_machine();
		}
	}
	return 0;
}

void menu_state_machine (void) {
	//App state machine
	_delay_ms(100);
 	uint8_t current_menu = 0;
	uint8_t exit = false;
	screen_clear();
	screen_normal();
	while(!exit){
		render_sentence_xy(apps[current_menu].name,20,2);
		screen_invert();

		//When top is selected show previous app
		if(PRESSED_INPUT_TOP){
			if(current_menu < APPSIZE -1){
				current_menu++;
			}else{
				current_menu = 0;
			}
			_delay_ms(100);
			_delay_ms(50);
			screen_clear();
		}

		// If negative, go back to home screen
		if(PRESSED_INPUT_NEGATIVE){
			_delay_ms(100);
			exit = true;
			screen_clear();
		}

		//If down, show next app
		if(PRESSED_INPUT_DOWN){
			if(current_menu > 0)
				current_menu--;
			else
				current_menu = APPSIZE -1;
			_delay_ms(100);
			screen_clear();
		}

		//goto app
		if(PRESSED_INPUT_LEFT | PRESSED_INPUT_RIGHT){
			_delay_ms(100);
			apps[current_menu].pointer();
		}
	}
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
