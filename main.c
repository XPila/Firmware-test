//main.c
#include "main.h"
#include "timer0.h"
#include "uart.h"
#include "lcd.h"


extern void setup(void);
extern void loop(void);


#ifdef UART0_FILE
FILE _uart0io = {0};
int uart0_putchar(char c, FILE *stream)
{
	uart0_tx(c);
	return 0;
}
int uart0_getchar(FILE *stream)
{
	return uart0_rx();
}
#endif //UART0_FILE

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

#ifdef LCD_FILE
FILE _lcdio = {0};
int lcd_putchar(char c, FILE *stream)
{
	lcd_chr(c);
	return 0;
}
int lcd_getchar(FILE *stream)
{
	return 0;
}
#endif //LCD_FILE


#define rbuf_l(p) (p[0])
#define rbuf_c(p) (p[1])
#define rbuf_i(p) (p[2])
#define rbuf_full(p) (rbuf_c(p) >= rbuf_l(p))
#define rbuf_empty(p) (rbuf_c(p) == 0)

void rbuf_ini(uint8_t* p, uint8_t l)
{
	rbuf_l(p) = l;
	rbuf_c(p) = 0;
	rbuf_i(p) = 0;
}

int rbuf_put(uint8_t* p, uint8_t b)
{
	if (rbuf_full(p)) return -1;
	p[3 + rbuf_i(p)] = b;
	rbuf_c(p)++;
	rbuf_i(p)++;
	if (rbuf_i(p) >= rbuf_l(p)) rbuf_i(p) = 0;
	return 0;
}

int rbuf_get(uint8_t* p)
{
	if (rbuf_empty(p)) return -1;
	uint8_t i = rbuf_i(p);
	if (rbuf_i(p) < rbuf_c(p)) i += rbuf_l(p);
	i -= rbuf_c(p);
	rbuf_c(p)--;
	return p[3 + i];
}

uint8_t buf[16];

extern void delay_500ms(void);

int main(void)
{
	cli();

	timer0_ini();

//	DDR(LED_PIN) |= __MSK(LED_PIN);
//	PORT(LED_PIN) |= __MSK(LED_PIN);
//	_DDR(22) = 0;
//	_DDR(10) = 0;
//	_DDR(30) = 0;
//	_DDR(38) = 0;

#ifdef UART0
	uart0_ini();
#ifdef UART0_FILE
	fdev_setup_stream(uart0io, uart0_putchar, uart0_getchar, _FDEV_SETUP_WRITE | _FDEV_SETUP_READ); //setup uart0 i/o stream
#endif //UART0_FILE
#endif //UART0

#ifdef UART1
	uart1_ini();
#ifdef UART1_FILE
	fdev_setup_stream(uart1io, uart1_putchar, uart1_getchar, _FDEV_SETUP_WRITE | _FDEV_SETUP_READ); //setup uart1 i/o stream
#endif //UART1_FILE
#endif //UART1

#ifdef LCD_4BIT
	lcd_ini();
#ifdef LCD_FILE
	fdev_setup_stream(lcdio, lcd_putchar, lcd_getchar, _FDEV_SETUP_WRITE | _FDEV_SETUP_READ); //setup lcd i/o stream
#endif //LCD_FILE
#endif //LCD_4BIT

#ifdef LED_PIN
	led_ini();
	led_on();
#endif //LED_PIN

	sei();

	rbuf_ini(buf, 13);
	rbuf_put(buf, 'A');
	rbuf_put(buf, 'h');
	rbuf_put(buf, 'o');
	rbuf_put(buf, 'j');

	while (1)
	{
		int b = rbuf_get(buf);
		if (b >= 0)
			fputc(b, lcdio);
		else
			break;
		delay_500ms();
	}

	// Arduino-like setup and looping
	setup();
	while (1)
		loop();

}