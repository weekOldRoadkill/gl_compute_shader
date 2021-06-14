#ifndef UTILS_H
#define UTILS_H


// Headers
#include <stdio.h>
#include <stdlib.h>

#include "types.h"


// Info Macro Function
#define info(fmt, ...) printf("INFO:\t"fmt"\n", ##__VA_ARGS__)


// Error Macro Function
#define error(fmt, ...) { \
	fprintf(stderr, "ERROR:\t"fmt"\n", ##__VA_ARGS__); \
	exit(0x01); \
}


// Get Time Function
double get_time();


#endif