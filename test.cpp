//test.cpp
#include "main.h"

class Ctest
{
public:
	Ctest();
};

Ctest::Ctest()
{
	fprintf_P(lcdio, PSTR("Ctest"));
}



void delay_50us(uint16_t us50)
{
	while (us50--)
		for (uint8_t i = 0; i < 200; i++)
		{ asm ("nop"); }
}


extern "C" //setup and loop are called from main.c
{
extern void delay_500ms(void);
#include "lcd.h";

void setup(void)
{
//	Ctest test;
//	DDR(_SUF_PIN(LED_PIN));
//	DDR(LED_PIN) |= _MSK(LED_PIN);
//	PORT(LED_PIN) |= _MSK(LED_PIN);
//	DDRB |= 0b10000000;
//	PORTB |= 0b10000000;

	while (1)
	{
//		delay_50us(10000);
		delay_500ms();
		led_neg();
//		PINB |= 0b10000000;
//		PINB(LED_PIN) |= _MSK(LED_PIN);
//		fprintf_P(uart0io, PSTR("cycle %d\n"), timer0_ms);
		lcd_cmd(LCD_CMD_SETDDRAMADDR);
		fprintf_P(lcdio, PSTR("cycle %ld    "), timer0_ms);
//		fprintf_P(uart0io, PSTR("cycle %ld\n"), timer0_ms);
	}
}

void loop(void)
{
}

}