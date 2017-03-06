#ifndef APPS_MAINS_H
#define APPS_MAINS_H

#include "../config.h"
#include "../main.h"
#include "apps.h"


typedef void (*functionptr_t)();
struct Apps{
	char name[16];
	functionptr_t pointer;
};


extern struct Apps apps[APPSIZE];

#endif
