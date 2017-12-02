#ifndef _UART_H
#define _UART_H

#include <inttypes.h>
#include "config.h"

#ifdef UART0
extern void uart0_ini(void);
extern uint8_t uart0_rx(void);
extern void uart0_tx(uint8_t c);
#endif //UART0

#ifdef UART1
extern void uart1_ini(void);
extern uint8_t uart1_rx(void);
extern void uart1_tx(uint8_t c);
#endif //UART1

#endif //_UART_H
