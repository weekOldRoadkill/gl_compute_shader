// Headers
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "types.h"


// Get Time Function
double get_time() {
	struct timeval t;
	gettimeofday(&t, 0x00);
	return t.tv_sec+t.tv_usec/1000000.0;
}