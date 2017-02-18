#ifndef SPI_H
#define SPI_PORT_DDR DDRB
#define SPI_PORT_O PORTB
#define SPI_PORT_I PINB
#define MOSI 5
#define MISO 6
#define SCK 7
#define SS 4

void SPI_init(uint8_t);
void SPI_TransReceive(uint8_t);

#endif
