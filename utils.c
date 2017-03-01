#include "utils.h"

void strcut(char * source, char *target,uint8_t from,uint8_t to){
	uint8_t counter;
    for(counter = from;counter<to;counter++){
        target[counter] = source[counter];
    }
    target[counter++]=' ';
    target[counter] = '\0';
}
