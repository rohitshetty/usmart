#ifndef INPUT_H


//This is for the apps useage
#define NAVI_TOP 0
#define NAVI_DOWN 1
#define NAVI_LEFT 2
#define NAVI_RIGHT 3
#define POSIT 4
#define NEGAT 5

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


extern volatile uint8_t flag;
extern volatile uint8_t input_status;



void input_init(void);
void enable_wakeup(void);
void disable_wakeup(void);
void debounce(void);


#endif
