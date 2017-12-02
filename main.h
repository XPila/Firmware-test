#ifndef _MAIN_H
#define _MAIN_H

#include <inttypes.h>
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "config.h"
#include "io_atmega2560.h"

extern uint32_t timer0_ms;

#ifdef UART0_FILE
#define uart0io (&_uart0io)
extern FILE _uart0io;
#endif //UART0_FILE

#ifdef UART1_FILE
#define uart1io (&_uart1io)
extern FILE _uart1io;
#endif //UART0_FILE

#ifdef LCD_FILE
#define lcdio (&_lcdio)
extern FILE _lcdio;
#endif //LCD_FILE

#ifdef LED_PIN
#define led_ini() { DDR(LED_PIN) |= __MSK(LED_PIN); }
#define led_off() { PORT(LED_PIN) |= __MSK(LED_PIN); }
#define led_on() { PORT(LED_PIN) &= ~__MSK(LED_PIN); }
#define led_neg() { PIN(LED_PIN) |= __MSK(LED_PIN); }
#endif //LED_PIN

#endif //_MAIN_H
