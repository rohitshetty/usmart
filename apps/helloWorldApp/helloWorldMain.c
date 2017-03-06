#include "helloWorldMain.h"

void helloWorld (void) {
	uint8_t exit=0;
	screen_clear();
	screen_normal();

	render_sentence_xy("Hello World",20,2);

	while(!exit) {
		if(PRESSED_INPUT_NEGATIVE){
			exit = 1;
			screen_clear();
			_delay_ms(200);
		}

		if (PRESSED_INPUT_POSITIVE) {
			screen_invert();
		}
	}
}
