//test.cpp
extern "C"
{
#include "main.h"
}


//application class
static class Capp
{
public:
	void setup(void);
	void loop(void);
protected:
	uint8_t m_view;
} app; //application instance

class Cstr
{
public:
	Cstr(const char* PROGMEM pstr);
};

extern "C" //setup and loop are called from main.c
{

void setup(void)
{
	app.setup();
}

void loop(void)
{
	app.setup();
}

}

void delay_50us(uint16_t us50)
{
	while (us50--)
		for (uint8_t i = 0; i < 200; i++)
		{ asm ("nop"); }
}


void Capp::setup(void)
{
//	fprintf_P(lcdio, PSTR(ESC_2J"setup %S%S"), PSTR("xxx"), PSTR("yyy"));
//	fprintf_P(lcdio, PSTR(ESC_2J"mfr=%02x dev=%02x       uid=%02x%02x%02x%02x%02x%02x%02x%02x"), w25x20cl_mfrid, w25x20cl_devid, w25x20cl_uid[0], w25x20cl_uid[1], w25x20cl_uid[2], w25x20cl_uid[3], w25x20cl_uid[4], w25x20cl_uid[5], w25x20cl_uid[6], w25x20cl_uid[7]);
	fprintf_P(lcdio, PSTR(ESC_2J"uid=%02x%02x%02x%02x%02x%02x%02x%02x"), w25x20cl_uid[0], w25x20cl_uid[1], w25x20cl_uid[2], w25x20cl_uid[3], w25x20cl_uid[4], w25x20cl_uid[5], w25x20cl_uid[6], w25x20cl_uid[7]);

	uint8_t data[10];
	for (uint8_t i = 0; i < 10; i++)
		data[i] = i;

	w25x20cl_enable_wr();

	w25x20cl_page_program(0x000000, data, 10);

	while (w25x20cl_rd_status_reg() & W25_STATUS_BUSY);

	w25x20cl_disable_wr();

	for (uint8_t i = 0; i < 10; i++)
		data[i] = 0x00;

	w25x20cl_rd_data(0x000000, data, 10);
	for (uint8_t i = 0; i < 10; i++)
		fprintf_P(lcdio, PSTR("%02x"), data[i]);



	while(1);
	fprintf_P(lcdio, PSTR(ESC_2J"setup"));
	delay_50us(20000);

	uint32_t time = 0;
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

//		lcd_put('a');
		//print delay to LCD
		//lcd_cmd(LCD_CMD_SETDDRAMADDR, 1);
		//delay_50us(50);

		//get start time
		uint32_t time_us = timer0_us();

//		fprintf_P(lcdio, PSTR(ESC_2J"abcdefghijklmnopqrst"ESC_H(0,1)"delay %ld us    "), time);

		//get end time
		uint32_t time_us1 = timer0_us();
		time = time_us1 - time_us;

//		lcd_cmd(LCD_CMD_SETDDRAMADDR+20);
		//fprintf_P(lcdio, PSTR("kbd %d"), kbd);
//		int uart_tx = rbuf_cnt(uart0_obuf);
//		fprintf_P(lcdio, PSTR("uart0 tx %d   "), uart_tx);
	}
}

void Capp::loop(void)
{
	delay_50us(20000);
}


Cstr::Cstr(const char* PROGMEM pstr)
{
}
