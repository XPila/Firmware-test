
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


//extern void delay_500ms(void);
//#include "rbuf.h";
//#include "lcd.h";
//#include "uart.h";
//extern uint8_t uart0_ibuf[UART0_IBUF];
//extern uint8_t uart0_obuf[UART0_IBUF];

void setup(void)
{
	while (1)
	{
//		for (int c = 0; c = 10; c++)
			delay_50us(5000); //
		led_neg();
/*

		//get start time
		uint32_t time_us = timer0_us();

		//print long string to serial and meassure time
		fprintf_P(uart0io, PSTR("abcdefghijklmnopqrstuvwxyz cycle %ld\n"), timer0_ms);

		//get end time
		uint32_t time_us1 = timer0_us();

		int kbd = lcd_get();

		//calc delay
		uint32_t time = time_us1 - time_us;

*/
		uint32_t time;

//		lcd_put('a');
		//print delay to LCD
		lcd_cmd(LCD_CMD_SETDDRAMADDR, 1);
		//delay_50us(50);

		//get start time
		uint32_t time_us = timer0_us();

		fprintf_P(lcdio, PSTR("abcdefghijklmnopqrstuw delay %ld us    "), time);

		//get end time
		uint32_t time_us1 = timer0_us();
		time = time_us1 - time_us;

//		lcd_cmd(LCD_CMD_SETDDRAMADDR+20);
		//fprintf_P(lcdio, PSTR("kbd %d"), kbd);
//		int uart_tx = rbuf_cnt(uart0_obuf);
//		fprintf_P(lcdio, PSTR("uart0 tx %d   "), uart_tx);
	}
}

void loop(void)
{
}

}