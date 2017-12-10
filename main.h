//main.h
#ifndef _MAIN_H
#define _MAIN_H

#include <inttypes.h>
#include <stdio.h>
#include <stdarg.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "config.h"
#include "io_atmega2560.h"
#include "timer0.h"
#include "rbuf.h"
#include "uart.h"
#include "swdelay.h"
#include "lcd.h"
#include "swspi.h"
#include "swi2c.h"
#include "w25x20cl.h"
#include "pat9125.h"


#ifdef LED_PIN
#define led_ini() { DDR(LED_PIN) |= __MSK(LED_PIN); }
#define led_off() { PORT(LED_PIN) |= __MSK(LED_PIN); }
#define led_on() { PORT(LED_PIN) &= ~__MSK(LED_PIN); }
#define led_neg() { PIN(LED_PIN) |= __MSK(LED_PIN); }
#endif //LED_PIN


#if defined(__cplusplus)
extern "C" {
#endif //defined(__cplusplus)


extern void kill(const char fmt, ...);


#if defined(__cplusplus)
}
#endif //defined(__cplusplus)
#endif //_MAIN_H
