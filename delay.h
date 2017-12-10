//delay.h - Software delay functions
#ifndef _DELAY_H
#define _DELAY_H


#if (F_CPU == 16000000)

//delay functions
extern void _delay_625ns(void);
extern void _delay_10us(void);
extern void _delay_40us(void);
extern void _delay_n10us(void);
extern void _delay_n40us(void);

//delay macros
#define delay_125ns() asm("nop\nnop")            //2cycles = 125ns@16MHz
#define delay_625ns() asm("call _delay_625ns")   //10cycles = 625ns@16MHz
#define delay_10us() asm("call _delay_10us")     //5+1+38*4-1+5 cycles = 10.062us
#define delay_40us() asm("call _delay_40us")     //5+1+158*4-1+5 cycles = 40.125us
#define delay_n10us(n) asm("ldi r19,%0\ncall _delay_n10us" :: "i" (n))
#define delay_n40us(n) asm("ldi r19,%0\ncall _delay_n40us" :: "i" (n))

#endif //(F_CPU == 16000000)


#endif //_DELAY_H