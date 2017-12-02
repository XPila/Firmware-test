//uart.c
#include "uart.h"
#include <avr/io.h>

#define UART_BAUD_SELECT(baudRate,xtalCpu) (((float)(xtalCpu))/(((float)(baudRate))*8.0)-1.0+0.5)

void uart0_ini(void)
{
	UCSR0A |= (1 << U2X0);
	UBRR0L = UART_BAUD_SELECT(UART0_BAUD, F_CPU);
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	asm volatile ("nop"); // wait until port has changed
//	rbufr = 0;
//	rbufw = 0;

}

uint8_t uart0_rx(void)
{
	while (!(UCSR0A & (1 << RXC0))); // wait until byte available
	UCSR0A |= (1 << RXC0); // delete RXCflag
	return UDR0; // receive byte
}

void uart0_tx(uint8_t c)
{
	UDR0 = c; // transmit byte
	while (!(UCSR0A & (1 << TXC0))); // wait until byte sent
	UCSR0A |= (1 << TXC0); // delete TXCflag
}
