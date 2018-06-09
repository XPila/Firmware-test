//rnd.c
#include "rnd.h"

int32_t randx;
uint8_t randf;


void srand(uint32_t x)
{
	randx = x;
	randf = 1;
}

int32_t rand(void)
{
	if (!randf) srand(1);
	return ((int32_t)((randx = randx * 1103515245L + 12345) >> 16) & 077777);
}
