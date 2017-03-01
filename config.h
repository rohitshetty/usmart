#ifndef CONFIG_H
#define CONFIG_H

#define F_CPU 11059200UL

#define APPSIZE 3
#define true 1
#define false 0

#define BAUD 115200
#define BAUDRATE ((F_CPU)/(BAUD*16UL)-1)

#endif
