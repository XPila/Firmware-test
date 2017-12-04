//main.c
#include "main.h"


extern void setup(void);
extern void loop(void);

void main_100us(void)
{
}

void main_1ms(void)
{
}

int main(void)
{
	cli();

	timer0_ini();

#ifdef UART0
	uart0_ini();
#endif //UART0

#ifdef UART1
	uart1_ini();
#endif //UART1

#ifdef LCD_4BIT
	lcd_ini();
#endif //LCD_4BIT

#ifdef LED_PIN
	led_ini();
	led_on();
#endif //LED_PIN

	sei();

	// Arduino-like setup and looping
	setup();
	while (1)
		loop();

}