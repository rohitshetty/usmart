#include "screen.h"

// The 7-bit ASCII character set...
// This charset font array is taken from Carlos Rodrigues <cefrodrigues@gmail.com> library for arduino.
const PROGMEM unsigned char charset[96][5] = {
  { 0x00, 0x00, 0x00, 0x00, 0x00 },  // 20 space
  { 0x00, 0x00, 0x5f, 0x00, 0x00 },  // 21 !
  { 0x00, 0x07, 0x00, 0x07, 0x00 },  // 22 "
  { 0x14, 0x7f, 0x14, 0x7f, 0x14 },  // 23 #
  { 0x24, 0x2a, 0x7f, 0x2a, 0x12 },  // 24 $
  { 0x23, 0x13, 0x08, 0x64, 0x62 },  // 25 %
  { 0x36, 0x49, 0x55, 0x22, 0x50 },  // 26 &
  { 0x00, 0x05, 0x03, 0x00, 0x00 },  // 27 '
  { 0x00, 0x1c, 0x22, 0x41, 0x00 },  // 28 (
  { 0x00, 0x41, 0x22, 0x1c, 0x00 },  // 29 )
  { 0x14, 0x08, 0x3e, 0x08, 0x14 },  // 2a *
  { 0x08, 0x08, 0x3e, 0x08, 0x08 },  // 2b +
  { 0x00, 0x50, 0x30, 0x00, 0x00 },  // 2c ,
  { 0x08, 0x08, 0x08, 0x08, 0x08 },  // 2d -
  { 0x00, 0x60, 0x60, 0x00, 0x00 },  // 2e .
  { 0x20, 0x10, 0x08, 0x04, 0x02 },  // 2f /
  { 0x3e, 0x51, 0x49, 0x45, 0x3e },  // 30 0
  { 0x00, 0x42, 0x7f, 0x40, 0x00 },  // 31 1
  { 0x42, 0x61, 0x51, 0x49, 0x46 },  // 32 2
  { 0x21, 0x41, 0x45, 0x4b, 0x31 },  // 33 3
  { 0x18, 0x14, 0x12, 0x7f, 0x10 },  // 34 4
  { 0x27, 0x45, 0x45, 0x45, 0x39 },  // 35 5
  { 0x3c, 0x4a, 0x49, 0x49, 0x30 },  // 36 6
  { 0x01, 0x71, 0x09, 0x05, 0x03 },  // 37 7
  { 0x36, 0x49, 0x49, 0x49, 0x36 },  // 38 8
  { 0x06, 0x49, 0x49, 0x29, 0x1e },  // 39 9
  { 0x00, 0x36, 0x36, 0x00, 0x00 },  // 3a :
  { 0x00, 0x56, 0x36, 0x00, 0x00 },  // 3b ;
  { 0x08, 0x14, 0x22, 0x41, 0x00 },  // 3c <
  { 0x14, 0x14, 0x14, 0x14, 0x14 },  // 3d =
  { 0x00, 0x41, 0x22, 0x14, 0x08 },  // 3e >
  { 0x02, 0x01, 0x51, 0x09, 0x06 },  // 3f ?
  { 0x32, 0x49, 0x79, 0x41, 0x3e },  // 40 @
  { 0x7e, 0x11, 0x11, 0x11, 0x7e },  // 41 A
  { 0x7f, 0x49, 0x49, 0x49, 0x36 },  // 42 B
  { 0x3e, 0x41, 0x41, 0x41, 0x22 },  // 43 C
  { 0x7f, 0x41, 0x41, 0x22, 0x1c },  // 44 D
  { 0x7f, 0x49, 0x49, 0x49, 0x41 },  // 45 E
  { 0x7f, 0x09, 0x09, 0x09, 0x01 },  // 46 F
  { 0x3e, 0x41, 0x49, 0x49, 0x7a },  // 47 G
  { 0x7f, 0x08, 0x08, 0x08, 0x7f },  // 48 H
  { 0x00, 0x41, 0x7f, 0x41, 0x00 },  // 49 I
  { 0x20, 0x40, 0x41, 0x3f, 0x01 },  // 4a J
  { 0x7f, 0x08, 0x14, 0x22, 0x41 },  // 4b K
  { 0x7f, 0x40, 0x40, 0x40, 0x40 },  // 4c L
  { 0x7f, 0x02, 0x0c, 0x02, 0x7f },  // 4d M
  { 0x7f, 0x04, 0x08, 0x10, 0x7f },  // 4e N
  { 0x3e, 0x41, 0x41, 0x41, 0x3e },  // 4f O
  { 0x7f, 0x09, 0x09, 0x09, 0x06 },  // 50 P
  { 0x3e, 0x41, 0x51, 0x21, 0x5e },  // 51 Q
  { 0x7f, 0x09, 0x19, 0x29, 0x46 },  // 52 R
  { 0x46, 0x49, 0x49, 0x49, 0x31 },  // 53 S
  { 0x01, 0x01, 0x7f, 0x01, 0x01 },  // 54 T
  { 0x3f, 0x40, 0x40, 0x40, 0x3f },  // 55 U
  { 0x1f, 0x20, 0x40, 0x20, 0x1f },  // 56 V
  { 0x3f, 0x40, 0x38, 0x40, 0x3f },  // 57 W
  { 0x63, 0x14, 0x08, 0x14, 0x63 },  // 58 X
  { 0x07, 0x08, 0x70, 0x08, 0x07 },  // 59 Y
  { 0x61, 0x51, 0x49, 0x45, 0x43 },  // 5a Z
  { 0x00, 0x7f, 0x41, 0x41, 0x00 },  // 5b [
  { 0x02, 0x04, 0x08, 0x10, 0x20 },  //	backslash. this is one hilarrious problem.
  { 0x00, 0x41, 0x41, 0x7f, 0x00 },  // 5d ]
  { 0x04, 0x02, 0x01, 0x02, 0x04 },  // 5e ^
  { 0x40, 0x40, 0x40, 0x40, 0x40 },  // 5f _
  { 0x00, 0x01, 0x02, 0x04, 0x00 },  // 60 `
  { 0x20, 0x54, 0x54, 0x54, 0x78 },  // 61 a
  { 0x7f, 0x48, 0x44, 0x44, 0x38 },  // 62 b
  { 0x38, 0x44, 0x44, 0x44, 0x20 },  // 63 c
  { 0x38, 0x44, 0x44, 0x48, 0x7f },  // 64 d
  { 0x38, 0x54, 0x54, 0x54, 0x18 },  // 65 e
  { 0x08, 0x7e, 0x09, 0x01, 0x02 },  // 66 f
  { 0x0c, 0x52, 0x52, 0x52, 0x3e },  // 67 g
  { 0x7f, 0x08, 0x04, 0x04, 0x78 },  // 68 h
  { 0x00, 0x44, 0x7d, 0x40, 0x00 },  // 69 i
  { 0x20, 0x40, 0x44, 0x3d, 0x00 },  // 6a j
  { 0x7f, 0x10, 0x28, 0x44, 0x00 },  // 6b k
  { 0x00, 0x41, 0x7f, 0x40, 0x00 },  // 6c l
  { 0x7c, 0x04, 0x18, 0x04, 0x78 },  // 6d m
  { 0x7c, 0x08, 0x04, 0x04, 0x78 },  // 6e n
  { 0x38, 0x44, 0x44, 0x44, 0x38 },  // 6f o
  { 0x7c, 0x14, 0x14, 0x14, 0x08 },  // 70 p
  { 0x08, 0x14, 0x14, 0x18, 0x7c },  // 71 q
  { 0x7c, 0x08, 0x04, 0x04, 0x08 },  // 72 r
  { 0x48, 0x54, 0x54, 0x54, 0x20 },  // 73 s
  { 0x04, 0x3f, 0x44, 0x40, 0x20 },  // 74 t
  { 0x3c, 0x40, 0x40, 0x20, 0x7c },  // 75 u
  { 0x1c, 0x20, 0x40, 0x20, 0x1c },  // 76 v
  { 0x3c, 0x40, 0x30, 0x40, 0x3c },  // 77 w
  { 0x44, 0x28, 0x10, 0x28, 0x44 },  // 78 x
  { 0x0c, 0x50, 0x50, 0x50, 0x3c },  // 79 y
  { 0x44, 0x64, 0x54, 0x4c, 0x44 },  // 7a z
  { 0x00, 0x08, 0x36, 0x41, 0x00 },  // 7b {
  { 0x00, 0x00, 0x7f, 0x00, 0x00 },  // 7c |
  { 0x00, 0x41, 0x36, 0x08, 0x00 },  // 7d }
  { 0x10, 0x08, 0x08, 0x10, 0x08 },  // 7e ~
  { 0x00, 0x00, 0x00, 0x00, 0x00 }   // 7f
};

//end of Carlos Rodrigues <cefrodrigues@gmail.com> font set array


void screen_reset(void){
	//Resets the status of screen
	SCREEN_PORT |=(1<<RST);
	_delay_ms(10);
	SCREEN_PORT &= ~(1<<RST);
	_delay_ms(100);
	SCREEN_PORT |=(1<<RST);

}


void screen_invert(void){
  screen_send_command(DISPLAY_CONTROL|INVERSE);
}

void screen_normal(void){
  screen_send_command(DISPLAY_CONTROL|NORMAL);
}

void screen_send_command(uint8_t command){
	//Sends the data in  command mode
	SELECT_SCREEN;
	RESET_DC;
	SPI_TransReceive(command);
	RELEASE_SCREEN;
}


void screen_send_data(uint8_t data){
	//Data sent over SPI into nokia 5110 screen
	SELECT_SCREEN;
	SET_DC;
	SPI_TransReceive(data);

	RELEASE_SCREEN;
}

void render_char(char data){
	//Loop unrolled. renders character
		screen_send_data(pgm_read_byte(&charset[data-32][0]));
		screen_send_data(pgm_read_byte(&charset[data-32][1]));
		screen_send_data(pgm_read_byte(&charset[data-32][2]));
		screen_send_data(pgm_read_byte(&charset[data-32][3]));
		screen_send_data(pgm_read_byte(&charset[data-32][4]));
}

void set_cursor_bank(uint8_t x, uint8_t y){
	//Sets the cursor in required bank. 0<= x <= 83 0<= y <=5
	screen_send_command(GOTOXBANK_BASE|x);
	screen_send_command(GOTOYBANK_BASE|y);
}

void render_sentence_xy(char *sentence, uint8_t x, uint8_t y){
	//expects the string to have NULL character. and renders the string in given x y bank
	uint8_t counter;
	set_cursor_bank(x,y);

	for(counter=0;sentence[counter]!='\0';counter++){
		render_char(sentence[counter]);
	}

}


void screen_clear(void){
	//clears the screen
	int i;
	screen_send_command(SCREEN_FUNCTION_SET);
	screen_send_command(DISPLAY_CONTROL|NORMAL);
	screen_send_command(GOTOXBANK_BASE);
	screen_send_command(GOTOYBANK_BASE);
	for(i=0;i<504;i++){
		screen_send_data(0x0);
	}
	screen_send_command(GOTOXBANK_BASE|0);
	screen_send_command(GOTOYBANK_BASE|0);

}


void screen_init(void){
	//initalize the screen
	pwm_init();                    //set pwm
	set_dutycycle(100);            // dutycycle varied from 0 to 255. here set one
	SPI_init(0x50);
	screen_send_command(SCREEN_FUNCTION_SET|EXTENDED_FUNCTION);  // extended company mode H=1
	SCREEN_DDR |=((1<<RST)|(1<<DC));                             // set the Data/command bar line as O/P
	SCREEN_PORT |=((1<<RST)|(1<<DC));
	screen_reset();
	screen_send_command(SCREEN_FUNCTION_SET|EXTENDED_FUNCTION);
	screen_send_command(BIAS_BASE|0x04);                        //Set the bias
	screen_send_command(VOP_BASE|50);                           // set contrast. actually contrast is also function of bias too.
	screen_send_command(SCREEN_FUNCTION_SET);                  // get back to H=0 mode.
	screen_clear();                                           // this sets the cursor back to (0,0) and clears the screens, puts
															 //it into normal mode
	render_sentence_xy("ReinventioLabs ",10,2);             // Boot screen.
	screen_send_command(DISPLAY_CONTROL|INVERSE);
	_delay_ms(1000);
	screen_clear();
}

void print_int_to_ascii(uint16_t num){

	struct stack {
		char stack_array[20];
		uint8_t pointer;
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