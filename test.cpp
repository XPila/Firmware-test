//test.cpp
#include "main.h"

//class definitions here


//setup and loop (called from main.c)
extern "C"
{

void delay_50us(uint16_t us50)
{
	while (us50--)
		for (uint8_t i = 0; i < 200; i++)
		{ asm ("nop"); }
}
//#define PROG_MEM __attribute__(section(".progmem")) 
//#define _n(str) ((progmem const char*)str)
//#define _n(s) (__extension__({static char __c[] PROGMEM = (s); &__c[0];}))
//#define _n(s) (__extension__({static prog_char __c[] = (s); &__c[0];})) 





//#define _n(s) PSTR(s)





uint16_t vals[ADC_CHAN_CNT];
uint8_t led_intensity;

void adc_ready(void)
{
	for (uint8_t i = 0; i < ADC_CHAN_CNT; i++)
		vals[i] = adc_val[i];
}

void setup(void)
{
/*
	for (uint8_t i = 0; i < ADC_CHAN_CNT; i++)
	{
		if ((i & 3) == 0)
			fprintf_P(lcdio, PSTR(ESC_H(0,%d)), (i >> 2));
		fprintf_P(lcdio, PSTR("%4d "), adc_chan(i));
	}
	while (1);*/

//	uint8_t ch = 0;
	while (1)
	{
		for (uint8_t i = 0; i < ADC_CHAN_CNT; i++)
		{
			if ((i & 3) == 0)
				fprintf_P(lcdio, PSTR(ESC_H(0,%d)), (i >> 2));
			fprintf_P(lcdio, PSTR("%4d "), vals[i] >> 4);
		}
	led_intensity++;
	if (led_intensity < 128) swpwm_val0 = led_intensity;
	else swpwm_val0 = 255 - led_intensity;
	uint8_t led_int1 = 2 * led_intensity;
	if (led_int1 < 128) swpwm_val1 = led_int1;
	else swpwm_val1 = 255 - led_int1;
	led_int1 = 4 * led_intensity;
	if (led_int1 < 128) swpwm_val2 = led_int1;
	else swpwm_val2 = 255 - led_int1;

//		adc_setmux(ch);
//		ADCSRA |= (1 << ADSC); //start conversion
//		adc_cycle();
//		swpwm_cycle();
//		swdelay_n40us(25);
//		swdelay_n40us(100);
//		if ((ch & 3) == 0)
//			fprintf_P(lcdio, PSTR(ESC_H(0,%d)), (ch >> 2));
//		fprintf_P(lcdio, PSTR("%4d "), ADC);

//		ch++;
//		ch &= 0x0f;
	}

//	fprintf_P(lcdio, PSTR(ESC_2J"setup %S%S"), PSTR("xxx"), PSTR("yyy"));
//	fprintf_P(lcdio, PSTR(ESC_2J"mfr=%02x dev=%02x       uid=%02x%02x%02x%02x%02x%02x%02x%02x"), w25x20cl_mfrid, w25x20cl_devid, w25x20cl_uid[0], w25x20cl_uid[1], w25x20cl_uid[2], w25x20cl_uid[3], w25x20cl_uid[4], w25x20cl_uid[5], w25x20cl_uid[6], w25x20cl_uid[7]);
//	fprintf_P(lcdio, PSTR(ESC_2J"uid=%02x%02x%02x%02x%02x%02x%02x%02x"), w25x20cl_uid[0], w25x20cl_uid[1], w25x20cl_uid[2], w25x20cl_uid[3], w25x20cl_uid[4], w25x20cl_uid[5], w25x20cl_uid[6], w25x20cl_uid[7]);
//	fprintf_P(lcdio, _n(ESC_2J"uid=%02x%02x%02x%02x%02x%02x%02x%02x                   "), w25x20cl_uid[0], w25x20cl_uid[1], w25x20cl_uid[2], w25x20cl_uid[3], w25x20cl_uid[4], w25x20cl_uid[5], w25x20cl_uid[6], w25x20cl_uid[7]);
//	fputs_P(_n(ESC_2J), lcdio);
//	fputs_P(_i("hello world!"), lcdio);
//	fputs_P(_i("fuck you!"), lcdio);

//	uint8_t data[10];
//	for (uint8_t i = 0; i < 10; i++)
//		data[i] = i;

//	w25x20cl_enable_wr();

//	w25x20cl_page_program(0x000000, data, 10);

//	while (w25x20cl_rd_status_reg() & W25_STATUS_BUSY);

//	w25x20cl_disable_wr();

/*	for (uint8_t i = 0; i < 10; i++)
		data[i] = 0x00;

	w25x20cl_rd_data(0x000000, data, 10);
	for (uint8_t i = 0; i < 10; i++)
		fprintf_P(lcdio, PSTR("%02x"), data[i]);


	fprintf_P(lcdio, PSTR(ESC_H(0,1)"%02x %02x"), pat9125_PID1, pat9125_PID2);

	while(1)
	{
		uint32_t time_us1 = timer0_us();
		pat9125_update();
		uint32_t time_us2 = timer0_us();

		fprintf_P(lcdio, PSTR(ESC_H(0,3)"%3d %4d %4d %3d %2d"), time_us2 - time_us1, pat9125_x, pat9125_y, pat9125_b, pat9125_s);
		swdelay_n40us(100);
	}
*/
///	fprintf_P(lcdio, PSTR(ESC_2J"setup"));
//	delay_50us(20000);

//	uint32_t time = 0;
	while (1)
	{
//		for (int c = 0; c = 10; c++)
//			delay_50us(5000); //
//		led_neg();
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
//		uint32_t time_us = timer0_us();

//		fprintf_P(lcdio, PSTR(ESC_2J"abcdefghijklmnopqrst"ESC_H(0,1)"delay %ld us    "), time);

		//get end time
//		uint32_t time_us1 = timer0_us();
//		time = time_us1 - time_us;

//		lcd_cmd(LCD_CMD_SETDDRAMADDR+20);
		//fprintf_P(lcdio, PSTR("kbd %d"), kbd);
//		int uart_tx = rbuf_cnt(uart0_obuf);
//		fprintf_P(lcdio, PSTR("uart0 tx %d   "), uart_tx);
	}
}

void loop(void)
{
	delay_50us(20000);
}

} //extern "C"
