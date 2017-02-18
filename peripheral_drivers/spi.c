#include<avr/io.h>
#include<avr/interrupt.h>
#include "spi.h"

void SPI_init(uint8_t spcr_mode){
	SPI_PORT_O |=(1<<SS); //Just to make sure it is in high mode, whatever the DDR status be. 
	SPI_PORT_DDR |= ((1<<SS));
	SPCR = spcr_mode;

	SPI_PORT_DDR |= ((1<<MOSI)|(1<<SCK)|(1<<SS)); // make all three spi pins as output.
	SPI_PORT_O |=(1<<SS);
}

void SPI_TransReceive(uint8_t data){
	int d;
	cli();
	SPDR = data;
	while(!(SPSR & (1<<SPIF)));
	d = SPDR;
	sei();
	return;
}