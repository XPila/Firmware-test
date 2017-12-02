//timer0.c
#include "timer0.h"
#include <avr/io.h>
#include <avr/interrupt.h>


uint32_t timer0_ms = 0; // 32bit milisecond counter (overflow in 49.71 days)


void timer0_ini(void)
{
	timer0_ms = 0; // initialize milisecond counter to zero
	TCCR0B |= (1 << CS00) | (1 << CS01); // set up timer with fclk/64 prescaling
	TCNT0 = 6; // initialize counter - overflow in 250 cycles (=1ms@16MHz)
	TIMSK0 |= (1 << TOIE0); // enable timer overflow interrupt
}

ISR(TIMER0_OVF_vect)
{
	TCNT0 = 6; // initialize counter - overflow in 250 cycles (=1ms@16MHz)
	timer0_ms++; // increment milisecond counter
}