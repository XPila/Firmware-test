//timer0.c
#include "timer0.h"
#include <avr/io.h>
#include <avr/interrupt.h>


uint8_t timer0_100us; // 8bit 100microsecond counter
uint32_t timer0_ms; // 32bit milisecond counter (overflow in 49.71 days)


#ifdef TIMER0_CB_100US
extern void TIMER0_CB_100US(void);
#endif //TIMER0_CB_100US

#ifdef TIMER0_CB_1MS
extern void TIMER0_CB_1MS(void);
#endif //TIMER0_CB_1MS


void timer0_ini(void)
{
	timer0_100us = 0; // initialize 100us counter to zero
	timer0_ms = 0; // initialize milisecond counter to zero
	TCCR0B |= TIMER0_PRESCALER; // set up timer with fclk/64 prescaling
	TCNT0 = (256 - TIMER0_CYC_100US); // initialize counter - overflow in 25 cycles (=100us@16MHz)
	TIMSK0 |= (1 << TOIE0); // enable timer overflow interrupt
}

uint32_t timer0_us(void)
{
	uint8_t _sreg = SREG;
	cli();
	uint8_t tcnt = TCNT0;
	uint8_t t100us = timer0_100us;
	uint32_t ms = timer0_ms;
	SREG = _sreg;
	return (1000 * ms) + (100 * t100us) + (4 * (tcnt - (256 - TIMER0_CYC_100US)));
}

ISR(TIMER0_OVF_vect)
{
	TCNT0 = (256 - TIMER0_CYC_100US); // initialize counter - overflow in 25 cycles (=100us@16MHz)
	if (++timer0_100us == 10)
	{
		timer0_100us = 0; // reset 100us counter
		timer0_ms++; // increment milisecond counter
#ifdef TIMER0_CB_1MS
		TIMER0_CB_1MS();
#endif //TIMER0_CB_1MS
	}
#ifdef TIMER0_CB_100US
	TIMER0_CB_100US();
#endif //TIMER0_CB_100US
}