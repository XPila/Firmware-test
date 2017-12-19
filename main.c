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
//	register sd_response_t rsp = {0,0,0,0,0,0,0,0};
//	rsp = sd_cmd_00(0);
//	if (rsp.crc_error) return 0;
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


	PIN_OUT(X_PIN_TMC2130_CS);
	PIN_OUT(Y_PIN_TMC2130_CS);
	PIN_OUT(Z_PIN_TMC2130_CS);
	PIN_OUT(E_PIN_TMC2130_CS);

	PIN_SET(X_PIN_TMC2130_CS);
	PIN_SET(Y_PIN_TMC2130_CS);
	PIN_SET(Z_PIN_TMC2130_CS);
	PIN_SET(E_PIN_TMC2130_CS);

	swspi_init();

	swi2c_init();

	w25x20cl_init();

	pat9125_init();

	sei();

	// Arduino-like setup and looping
	setup();
	while (1)
		loop();

}

void kill(const char fmt, ...)
{
}
