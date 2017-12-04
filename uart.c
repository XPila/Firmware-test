//uart.c
#include "uart.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "rbuf.h"

#define UART_BAUD_SELECT(baudRate,xtalCpu) (((float)(xtalCpu))/(((float)(baudRate))*8.0)-1.0+0.5)

#ifdef UART0

#define uart0_rxcomplete (UCSR0A & (1 << RXC0))
#define uart0_txcomplete (UCSR0A & (1 << TXC0))
#define uart0_txready    (UCSR0A & (1 << UDRE0))

#ifdef UART0_IBUF
uint8_t uart0_ibuf[UART0_IBUF];
#endif //UART0_IBUF

#ifdef UART0_OBUF
uint8_t uart0_obuf[UART0_OBUF];
#endif //UART0_OBUF

#ifdef UART0_FILE
FILE _uart0io = {0};
int uart0_putchar(char c, FILE *stream)
{
	return uart0_tx(c);
}
int uart0_getchar(FILE *stream)
{
	return uart0_rx();
}
#endif //UART0_FILE

void uart0_ini(void)
{
	UCSR0A |= (1 << U2X0); // baudrate multiplier
	UBRR0L = UART_BAUD_SELECT(UART0_BAUD, F_CPU); // select baudrate
	UCSR0B = (1 << RXEN0) | (1 << TXEN0); // enable receiver and transmitter
#ifdef UART0_IBUF
	UCSR0B |= (1 << RXCIE0); // enable rx interrupt
#endif //UART0_IBUF
#ifdef UART0_OBUF
//	UCSR0B |= (1 << TXCIE0);
#endif //UART0_OBUF	
	asm volatile ("nop"); // wait until port has changed

#ifdef UART0_IBUF
	rbuf_ini(uart0_ibuf, UART0_IBUF - 4);
#endif //UART0_IBUF

#ifdef UART0_OBUF
	rbuf_ini(uart0_obuf, UART0_OBUF - 4);
#endif //UART0_OBUF

#ifdef UART0_FILE
	fdev_setup_stream(uart0io, uart0_putchar, uart0_getchar, _FDEV_SETUP_WRITE | _FDEV_SETUP_READ); //setup uart0 i/o stream
#endif //UART0_FILE

}

int uart0_rx(void)
{
#ifdef UART0_IBUF
#ifdef UART0_RXNB
	if (rbuf_empty(uart0_ibuf)) return -1; // for non blocking mode return -1
#else //UART0_RXNB
	while (rbuf_empty(uart0_ibuf)); // wait until byte available
#endif //UART0_RXNB
	return rbuf_get(uart0_ibuf);
#else //UART0_IBUF
#ifdef UART0_RXNB
	if (!uart0_rxcomplete) return -1; // for non blocking mode return -1
#else //UART0_RXNB
	while (!uart0_rxcomplete); // wait until byte available
#endif //UART0_RXNB
	UCSR0A |= (1 << RXC0); // delete RXCflag
	return UDR0; // receive byte
#endif //UART0_IBUF
}

int uart0_tx(uint8_t c)
{
#ifdef UART0_OBUF
	if (UCSR0B & (1 << TXCIE0))
	{
#ifdef UART0_TXNB
		if (rbuf_put(uart0_obuf, c) < 0) return -1;
#else //UART0_TXNB
		while (rbuf_put(uart0_obuf, c) < 0);
#endif //UART0_TXNB
	}
	else
	{
		UCSR0B |= (1 << TXCIE0); //enable tx interrupt
		UDR0 = c; //transmit the byte
	}
#else //UART0_OBUF
#ifdef UART0_TXNB
	if (!uart0_txready) return -1; // for non blocking mode return -1
	UDR0 = c; // transmit byte
#else //UART0_TXNB
	UDR0 = c; // transmit byte
	while (!uart0_txcomplete); // wait until byte sent
	UCSR0A |= (1 << TXC0); // delete TXCflag
#endif //UART0_TXNB
#endif //UART0_OBUF
	return 0;
}

#ifdef UART0_IBUF
ISR(USART0_RX_vect)
{
	if (rbuf_put(uart0_ibuf, UDR0) < 0) // put received byte to buffer
	{
		//rx buffer full
	}
}
#endif //UART0_IBUF

#ifdef UART0_OBUF
ISR(USART0_TX_vect)
{
	int c = rbuf_get(uart0_obuf);
	if (c >= 0) 
		UDR0 = c; // transmit next byte from buffer
	else
		UCSR0B &= ~(1 << TXCIE0); // disable tx interrupt (used as tx_inprogress flag)
}
#endif //UART0_OBUF

#endif //UART0


#ifdef UART1

#ifdef UART1_FILE
FILE _uart1io = {0};
int uart1_putchar(char c, FILE *stream)
{
	uart1_tx(c);
	return 0;
}
int uart1_getchar(FILE *stream)
{
	return uart1_rx();
}
#endif //UART1_FILE

#endif //UART1
