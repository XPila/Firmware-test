//timer0.h
#ifndef _TIMER0_H
#define _TIMER0_H

#include <inttypes.h>
#include "config.h"


extern uint8_t timer0_100us;
extern uint32_t timer0_ms;

extern void timer0_ini(void);
extern uint32_t timer0_us(void);


#endif //_TIMER0_H
