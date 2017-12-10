//delay.c - Software delay functions
#include "delay.h"


//delay functions

#if (F_CPU == 16000000)

void _delay_625ns(void)
{ }                          // 5cycles call + 5cycles ret = 625ns@16MHz

void _delay_10us(void)
{                            // 5cycles call
	asm("ldi r18, 0");       // 1cycle
	asm("inc r18");          // 1cycle
	asm("cpi r18, 39");      // 1cycle
	asm("brne .-6");         // 1/2cycles
}                            // 5cycles ret

void _delay_40us(void)
{                            // 5cycles call
	asm("ldi r18, 0");       // 1cycle
	asm("inc r18");          // 1cycle
	asm("cpi r18, 159");     // 1cycle
	asm("brne .-6");         // 1/2cycles
}                            // 5cycles ret

void _delay_n10us(void)
{                            // 5cycles call
	asm("call _delay_10us"); // 10us
	asm("dec r19");          // 1cycle
	asm("cpi r19, 0");       // 1cycle
	asm("brne .-10");        // 1/2cycles
}                            // 5cycles ret

void _delay_n40us(void)
{                            // 5cycles call
	asm("call _delay_40us"); // 40us
	asm("dec r19");          // 1cycle
	asm("cpi r19, 0");       // 1cycle
	asm("brne .-10");        // 1/2cycles
}                            // 5cycles ret

#endif //(F_CPU == 16000000)
