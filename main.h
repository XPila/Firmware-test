#ifndef _MAIN_H
#define _MAIN_H

#include <inttypes.h>
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "config.h"
#include "io_atmega2560.h"
#include "timer0.h"
#include "rbuf.h"
#include "uart.h"
#include "lcd.h"
#include "swspi.h"
#include "w25x20cl.h"


#ifdef LED_PIN
#define led_ini() { DDR(LED_PIN) |= __MSK(LED_PIN); }
#define led_off() { PORT(LED_PIN) |= __MSK(LED_PIN); }
#define led_on() { PORT(LED_PIN) &= ~__MSK(LED_PIN); }
#define led_neg() { PIN(LED_PIN) |= __MSK(LED_PIN); }
#endif //LED_PIN


#endif //_MAIN_H
