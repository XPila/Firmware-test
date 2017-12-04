
//#include "main.h"

//test.cpp

/*
class Ctest
{
public:
	Ctest();
};

Ctest::Ctest()
{
	fprintf_P(lcdio, PSTR("Ctest"));
}
*/


extern "C" //setup and loop are called from main.c
{
#include "main.h"

void delay_50us(uint16_t us50)
{
	while (us50--)
		for (uint8_t i = 0; i < 200; i++)
		{ asm ("nop"); }
}


extern void delay_500ms(void);
//#include "rbuf.h";
//#include "lcd.h";
//#include "uart.h";
//extern uint8_t uart0_ibuf[UART0_IBUF];
//extern uint8_t uart0_obuf[UART0_IBUF];

void setup(void)
{
	while (1)
	{
		delay_500ms();
		led_neg();

		lcd_cmd(LCD_CMD_SETDDRAMADDR);

		//get start time
		cli();
		uint32_t time_ms = timer0_ms;
		uint8_t time_100us = timer0_100us;
		sei();

		//print long string to serial and meassure time
		fprintf_P(uart0io, PSTR("abcdefghijklmnopqrstuvwxyz cycle %ld\n"), timer0_ms);

		//get end time
		cli();
		uint32_t time_ms1 = timer0_ms;
		uint8_t time_100us1 = timer0_100us;
		sei();

		//calc delay
		uint32_t time0 = 10 * time_ms + time_100us;
		uint32_t time1 = 10 * time_ms1 + time_100us1;
		uint32_t time = time1 - time0;
		//print delay to LCD
		fprintf_P(lcdio, PSTR("delay %ld (x100us)   "), time);
//		int uart_tx = rbuf_cnt(uart0_obuf);
//		fprintf_P(lcdio, PSTR("uart0 tx %d   "), uart_tx);
	}
}

void loop(void)
{
}

}