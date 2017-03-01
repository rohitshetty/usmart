#ifndef SCREEN_H
#define SCREEN_H

#include "../../config.h"
#include<avr/io.h>
#include<avr/pgmspace.h>
#include<util/delay.h>
#include "../../peripheral_drivers/spi/spi.h"
#include "screen.h"
#include "../../peripheral_drivers/pwm/pwm.h"


#define SCREEN_DDR DDRB
#define SCREEN_PORT PORTB
#define RST 1
#define DC 2
#define CS 4

#define SCREEN_FUNCTION_SET 0x20
#define EXTENDED_FUNCTION 0x01

#define POWERDOWN 0x04


#define BIAS_BASE 0x10
#define VOP_BASE 0x80

#define DISPLAY_CONTROL 0x08

#define GOTOXBANK_BASE 0x80
#define GOTOYBANK_BASE 0x40

//display modes
#define BLANK 0x00
#define ALL_ON 0x1
#define NORMAL 0x4
#define INVERSE 0x5



#define RESET_DC (SCREEN_PORT&=~(1<<DC))
#define SET_DC (SCREEN_PORT|=(1<<DC))

#define SELECT_SCREEN (SCREEN_PORT&=~(1<<CS))
#define RELEASE_SCREEN (SCREEN_PORT|=(1<<CS))

void screen_reset(void);
void screen_send_command(uint8_t);
void screen_send_data(uint8_t);
void screen_init(void);
void render_sentence_xy(char *,uint8_t,uint8_t);
void render_char(char);
void screen_clear(void);
void set_cursor_bank(uint8_t,uint8_t);
void screen_invert(void);
void screen_normal(void);
void print_int_to_ascii(uint16_t);



#endif
