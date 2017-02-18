#define F_CPU 12000000UL
#include<avr/io.h>
#include<util/delay.h>
#include<avr/pgmspace.h>
#include<avr/interrupt.h>
#include<avr/sleep.h>
#include <string.h>
#include "device_drivers/screen.h"
#include "device_drivers/input.h"

#define APPSIZE 3

#define true 1
#define false 0


/*
PD2  positive response
PD3 negative response

PD4 left
PD5 right
PD6 down
PD7 right

*/

uint8_t brightness = 100;
volatile float temperature=27.8;
volatile char datetime[21];
char hhmmss[9];



void strcut(char * source, char *target,uint8_t from,uint8_t to){
    uint8_t counter;
    for(counter = from;counter<to;counter++){
        target[counter] = source[counter];
    }
    target[counter++]=' ';
    target[counter] = '\0';
}



void adc_init(){
	ADMUX |=(1<<REFS0);
	ADCSRA = (1<<ADEN)|(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2);
}


uint16_t adc_read(uint8_t channel){
	channel &= 0b00000111;
	ADMUX  = (ADMUX & 0xF8) | channel;
	ADCSRA |= (1<<ADSC);
	while(ADCSRA & (1<<ADSC));
	return ADC;
}


void print_int_to_ascii(uint16_t num){

	struct stack {
	char stack_array[20];
	char pointer;
	};

	struct stack LIFO;
	uint16_t rem;
	LIFO.pointer=0;
	for(LIFO.pointer=0;num!=0;LIFO.pointer++){
		rem = num%10;
		num = num/10;
		LIFO.stack_array[LIFO.pointer] = rem+48;
	}
	for(LIFO.pointer--;LIFO.pointer>=0;LIFO.pointer--){
	 	render_char(LIFO.stack_array[LIFO.pointer]);
	}
	return;
}


void print_float(float num){
	uint16_t mant,deci;
	mant = (int) num;
	deci = (num-(mant*1.0))*1000000;
	print_int_to_ascii(mant);
	render_char('.');
	print_int_to_ascii(deci);
	return;
}

void get_temp(){
		uint16_t temp;
		float temp2;
        temp= adc_read(0x0);

        temp2 = ((float)temp)*0.48828;
        temperature = temp2 ;
}


void appone(){
	char exit = 0;
	screen_clear();
	screen_normal();

	while(!exit){

		render_sentence_xy("Brightness",15,1);

		set_cursor_bank(15,3);
		print_int_to_ascii(brightness);


	if(input_status & (1<<NEGAT)){
		screen_clear();
		_delay_ms(200);
		exit = 1;
	}


	if(input_status & (1<<NAVI_TOP)){

		if(brightness>240){
			brightness = 250;
		}else{
			brightness = brightness +10;
			set_dutycycle(brightness);
		}
	screen_clear();
	render_sentence_xy("Brightness",15,1);

		set_cursor_bank(15,3);
		print_int_to_ascii(brightness);

		_delay_ms(300);
	}



	if(input_status & (1<<NAVI_DOWN)){
		if(brightness>10){
			brightness = brightness -10;
			set_dutycycle(brightness);
		}else{
			brightness = 10;
		}

	screen_clear();

		render_sentence_xy("Brightness",15,1);

		set_cursor_bank(15,3);
		print_int_to_ascii(brightness);


		_delay_ms(300);
	}

	}

};

volatile float voltage;


ISR(ADC_vect){


}



void apptwo(){
	char exit = 00;
	screen_normal();
	screen_clear();

	render_sentence_xy("signal in channel",0,0);
	render_sentence_xy("4 (in Volts)",0,1);

	while(!exit){

	set_cursor_bank(15,3);
	print_float(voltage);

	if(input_status & (1<<NEGAT)){
		screen_clear();
		_delay_ms(200);
		exit = 1;

	}
	}

}


void appThree () {
	char exit = 00;
	char devices[][20] = {{"HallLight: "},{"AC Sys: "},{"Gyser: "}};
	// char deviceOnStatus[][20] = {{"HallLight:on"},{"AC Sys:on"},{"Gyser:on"}};
	// char deviceOffStatus[][20] = {{"HallLight:off"},{"AC Sys:off"},{"Gyser:off"}};
	uint8_t status =0x00;
	uint8_t i;
	uint8_t selector = 0;
	uint8_t length;
	char message[100];
	screen_normal();
	screen_clear();
	render_sentence_xy("IoT Example App",0,0);



	while(!exit){
		// screen_clear();
		set_cursor_bank(15,3);
		// print_float(voltage);
		// render_sentence_xy(print_int_to_ascii(status),1,1);
		// print_int_to_ascii(selector);
		// print_int_to_ascii(status);

		render_sentence_xy(">",0,selector+2);

		for(i=0;i<3;i++) {
			render_sentence_xy(&devices[i][0],7,i+2);
			// print_int_to_ascii(?1:0);
			if (status & (1<<i)) {
				render_char('O');
				render_char('N');
			} else {
				render_char('O');
				render_char('F');
				render_char('F');
			}
			// render_sentence_xy("-->",6+(int)strlen(&devices[i][0]),i+2);
		}

		if(input_status & (1<<NEGAT)){
			screen_clear();
			_delay_ms(200);
			exit = 1;
		} else if (input_status & (1<<NAVI_TOP)) {
			selector = (selector+1)%3;
			screen_clear();
			render_sentence_xy("IoT Example App",0,0);

			_delay_ms(100);

		} else if (input_status & (1<<NAVI_DOWN)) {
			if (selector != 0)
				selector = (selector-1)%3;
			else
				selector = 2;
			screen_clear();
			render_sentence_xy("IoT Example App",0,0);
			_delay_ms(150);
		} else if (input_status & (1<<NAVI_RIGHT)) {
			if (status & (1<<selector)) {

				// strcpy(devices[selector][0],deviceOffStatus[selector][0]);
				status&= ~(1<<selector);
			} else {
				// strcpy(devices[selector][0],deviceOnStatus[selector][0]);
				status|= (1<<selector);
			}

			strcpy(message,"d,topic:/ucontrol,data:");
			length = strlen(message);
			message[length]=(char)status+48;
			message[length+1]='\0';

			serial_send_string(message);
			DDRC |= (1<<PC2);
			PORTC|=(1<<PC2);
			_delay_ms(50);
			PORTC&=~(1<<PC2);


			_delay_ms(150);
			screen_clear();
			render_sentence_xy("IoT Example App",0,0);


		} else if (input_status & (1<<NAVI_LEFT)) {
			if (status & (1<<selector)) {
				// strcpy(devices[selector][0],deviceOffStatus[selector][0]);
				status&= ~(1<<selector);
			} else {
				// strcpy(devices[selector][0],deviceOnStatus[selector][0]);
				status|= (1<<selector);
			}

			strcpy(message,"d,topic:/ucontrol,data:");
			length = strlen(message);
			message[length]=(char)status+48;
			message[length+1]='\0';


			serial_send_string(message);
			DDRC |= (1<<PC2);
			PORTC|=(1<<PC2);
			_delay_ms(50);
			PORTC&=~(1<<PC2);

			_delay_ms(150);
			screen_clear();
			render_sentence_xy("IoT Example App",0,0);

		}
	}

}


void main(){


	// inputs

	typedef void (*functionptr_t)();

	struct Apps{
		char name[16];
		functionptr_t pointer;
	};

	int counter;

	struct Apps apps[APPSIZE] = {
		{
			.name = "Brightness",
			.pointer = appone
		},{
			.name = "VoltMeter",
			.pointer = apptwo
		},{
			.name = "uControl",
			.pointer = appThree
		}
	};





	input_init();
	screen_init();
	serial_init();
	set_dutycycle(brightness);
	DDRC |=(1<<PC2);
	PORTC|=(1<<PC2);
	_delay_ms(500);
	PORTC&=~(1<<PC2);

    RTCinit();
    adc_init();


	uint8_t exit=0;
	uint8_t current_menu;
	TCCR1B |=(1<<CS12)|(1<<WGM12);
	OCR1A = 46860;
	TIMSK |= (1<<OCIE1A);


    TCNT1=0;

	render_sentence_xy("Waiting For",10,2);
	render_sentence_xy("WiFi",15,3);
	_delay_ms(5000);

	screen_clear();
	// serial_send_string("c,topic:/message\n");
	serial_send_string("c,topic:/message");

	render_sentence_xy("Subscribing to",10,2);
	render_sentence_xy("/message",15,3);
	_delay_ms(3000);

	serial_send_string("d,topic:/ucontrol,data: welcome World");
	sei();



	screen_clear();
	// render_sentence_xy("Testing 	one  \0",15,2);
    RTCSet("8841001140516"); //hhmmssDddmmyy

	while(1){
        // strcut(datetime,hhmmss,0,8);



    	render_sentence_xy(hhmmss,15,2);
		set_cursor_bank(15,3);
		print_int_to_ascii((int)temperature);
		render_sentence_xy("`C Mysuru",27,3);

		screen_invert();
		if(input_status & (1<<NEGAT)){
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

		if(input_status & (1<<POSIT)){
			//Menu	s
			_delay_ms(100);
			current_menu = 0;
			exit = 0;
			screen_clear();
			screen_normal();
			while(!exit){
				render_sentence_xy(apps[current_menu].name,20,2);
				screen_invert();

				if(input_status & (1<<NAVI_TOP)){
					if(current_menu < APPSIZE -1){
						current_menu++;
					}else{
						current_menu = 0;
					}
					_delay_ms(100);
					DDRC |= (1<<PC2);
					PORTC|=(1<<PC2);
					_delay_ms(50);
					PORTC&=~(1<<PC2);

					screen_clear();
				}

				if(input_status&(1<<NEGAT)){
					_delay_ms(100);
					exit = 1;
					screen_clear();
				}
				if(input_status & (1<<NAVI_DOWN)){
					if(current_menu > 0)
						current_menu--;
					else
						current_menu = APPSIZE -1;

					_delay_ms(100);
	DDRC | (1<<PC2);
	PORTC|=(1<<PC2);
	_delay_ms(50);
	PORTC&=~(1<<PC2);

					screen_clear();
				}

				if((input_status & (1<<NAVI_LEFT))|(input_status & (1<<NAVI_RIGHT))){
					_delay_ms(100);
					apps[current_menu].pointer();
				}




			}

		}

		// if(input_status & (1<<NAVI_TOP)){
		// 	//Menu

		// 	screen_clear();
		// 	screen_normal();
		// 	render_sentence_xy("top",15,2);
		// }


		// if(input_status & (1<<NAVI_DOWN)){
		// 	//Menu

		// 	screen_clear();
		// 	screen_normal();
		// 	render_sentence_xy("down",15,2);
		// }


		// if(input_status & (1<<NAVI_RIGHT)){
		// 	//Menu

		// 	screen_clear();
		// 	screen_normal();
		// 	render_sentence_xy("right",15,2);
		// }


		// if(input_status & (1<<NAVI_LEFT)){
		// 	//Menu

		// 	screen_clear();
		// 	screen_normal();
		// 	render_sentence_xy("left",15,2);
		// }


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
        float temp;
        uint16_t inter;

        RTCRead(datetime);
        strcut(datetime,hhmmss,0,8);
        get_temp();
        inter = adc_read(0x4);
		voltage = inter/204.8;
}




// if(flag){
			// screen_clear();

			// if(input_status & (1<<NAVI_TOP)){
			// 	render_sentence_xy("TOP",42,2);
			// }

			// if(input_status & (1<<NAVI_DOWN)){
			// 	render_sentence_xy("DOWN",42,2);
			// }

			// if(input_status & (1<<NAVI_LEFT)){
			// 	render_sentence_xy("LEFT",42,2);
			// }

			// if(input_status & (1<<NAVI_RIGHT)){
			// 	render_sentence_xy("RIGHT",42,2);
			// }

			// if(input_status & (1<<POSIT)){
			// 	render_sentence_xy("positive",42,2);
			// }

			// if(input_status & (1<<NEGAT)){
			// 	render_sentence_xy("Negative",42,2);
			// }

			// flag =false;
			// }
