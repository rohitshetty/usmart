#ifndef INPUT_H


//This is for the apps useage
#define NAVI_TOP 0
#define NAVI_DOWN 1
#define NAVI_LEFT 2
#define NAVI_RIGHT 3
#define POSIT 4
#define NEGAT 5

extern volatile uint8_t flag;
extern volatile uint8_t input_status;

void input_init(void);
void enable_wakeup(void);
void disable_wakeup(void);
void debounce(void);


#endif
