//uart.h
#ifndef _UART_H
#define _UART_H

#include <inttypes.h>
#include "config.h"

#if (defined(UART0_FILE) || defined(UART1_FILE))
#include <stdio.h>
#endif


#if defined(__cplusplus)
extern "C" {
#endif //defined(__cplusplus)


#ifdef UART0
extern void uart0_ini(void);
extern int uart0_rx(void);
extern int uart0_tx(uint8_t c);
#ifdef UART0_FILE
#define uart0io (&_uart0io)
extern FILE _uart0io;
#endif //UART0_FILE
#endif //UART0

#ifdef UART1
extern void uart1_ini(void);
extern int uart1_rx(void);
extern int uart1_tx(uint8_t c);
#ifdef UART1_FILE
#define uart1io (&_uart1io)
extern FILE _uart1io;
#endif //UART0_FILE
#endif //UART1


#if defined(__cplusplus)
}
#endif //defined(__cplusplus)
#endif //_UART_H
