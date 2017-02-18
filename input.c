#include<avr/io.h>
#include<avr/interrupt.h>
#include "input.h"



#define MAXDEBOUNCEONEPRESS 15
#define MAXDEBOUNCEONENAVI 30

// pin connections
//This is for the device
#define UP 7
#define DOWN 6
#define RIGHT 5
#define LEFT 4
#define OKWAKE 2
#define CANCEL 3


volatile int debouncingCounters[6]={0,0,0,0,0,0};
volatile uint8_t flag=0;
volatile uint8_t input_status=0;
void timer2_init(){
	TCCR2 =(1<<CS22)|(1<<CS21);
	TIMSK = (1<<TOIE2);
}

void input_init(void){
	DDRD |= 0x00;
	PORTD |= (0xff);
	timer2_init();
}


void enable_wakeup(void){
	GICR = (1<<INT0);
	MCUCSR = (1<<ISC01)|(1<<ISC00);
	GIFR = (1<<INTF0);
}

void disable_wakeup(void){
	GICR &= ~(1<<INT0);
	GIFR &= ~(1<<INTF0);
}

void debounce(void){

	if((~PIND)&(1<<PD7)){
		debouncingCounters[0]++;
		if(debouncingCounters[0]>MAXDEBOUNCEONENAVI){
			//set pin
			input_status |= (1<<NAVI_TOP);
			debouncingCounters[0] = 0;
			flag = 1;
		}
	}else{
		debouncingCounters[0] = 0;
		input_status &= ~(1<<NAVI_TOP);

	}

	if((~PIND)&(1<<PD6)){
		debouncingCounters[1]++;
		if(debouncingCounters[1]>MAXDEBOUNCEONENAVI){
			//set pin
			input_status |= (1<<NAVI_DOWN);

			debouncingCounters[1] = 0;
			flag = 1;
		}
	}else{
		debouncingCounters[1] = 0;
		input_status &= ~(1<<NAVI_DOWN);

	}

	if((~PIND)&(1<<PD5)){
		debouncingCounters[2]++;
		if(debouncingCounters[2]>MAXDEBOUNCEONENAVI){
			//set pin
			input_status |= (1<<NAVI_RIGHT);


			debouncingCounters[2] = 0;
			flag = 1;
		}
	}else{
		debouncingCounters[2] = 0;
			input_status &= ~(1<<NAVI_RIGHT);

	}

	if((~PIND)&(1<<PD4)){
		debouncingCounters[3]++;
		if(debouncingCounters[3]>MAXDEBOUNCEONENAVI){
			//set pin
			input_status |= (1<<NAVI_LEFT);

			debouncingCounters[3] = 0;
			flag = 1;
		}
	}else{
		debouncingCounters[3] = 0;
		input_status &= ~(1<<NAVI_LEFT);

	}

	if((~PIND)&(1<<PD2)){
		debouncingCounters[4]++;
		if(debouncingCounters[4]>MAXDEBOUNCEONEPRESS){
			//set pin
			input_status |= (1<<POSIT);
			debouncingCounters[4] = 0;
			flag = 1;
		}
	}else{
		debouncingCounters[4] = 0;
		input_status &= ~(1<<POSIT);

	}

	if((~PIND)&(1<<PD3)){
		debouncingCounters[5]++;
		if(debouncingCounters[5]>MAXDEBOUNCEONEPRESS){
			//set pin
			input_status |= (1<<NEGAT);
			debouncingCounters[5] = 0;
			flag = 1;
		}
	}else{
		debouncingCounters[5] = 0;
		input_status &= ~(1<<NEGAT);

	}
}



ISR(TIMER2_OVF_vect){

debounce();
}
