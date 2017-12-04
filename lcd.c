//lcd.c
#include "lcd.h"
#include <avr/io.h>
#include "io_atmega2560.h"
#include "rbuf.h"


#ifdef LCD_IBUF
uint8_t lcd_ibuf[LCD_IBUF];
#endif //LCD_IBUF

#ifdef LCD_OBUF
uint8_t lcd_obuf[LCD_OBUF];
#endif //LCD_OBUF


#ifdef LCD_4BIT

int lcd_test;

#ifdef LCD_FILE
FILE _lcdio = {0};
int lcd_putchar(char c, FILE *stream)
{
	return lcd_put(c);
}
int lcd_getchar(FILE *stream)
{
	return lcd_get();
}
#endif //LCD_FILE

//delay macros
#define delay_125ns() asm("nop\nnop")            //2cycles = 125ns@16MHz
#define delay_625ns() asm("call _delay_625ns")   //10cycles = 625ns@16MHz
#define delay_40us() asm("call _delay_40us")     //5+1+158*4-1+5 cycles = 40.125us
#define delay_n40us(n) asm("ldi r19,%0\ncall _delay_n40us" :: "i" (n))
//delay functions

void _delay_625ns(void)
{ }                          // 5cycles call + 5cycles ret = 625ns@16MHz

void _delay_40us(void)
{                            // 5cycles call
	asm("ldi r18, 0");       // 1cycle
	asm("inc r18");          // 1cycle
	asm("cpi r18, 159");     // 1cycle
	asm("brne .-6");         // 1/2cycles
}                            // 5cycles ret

void _delay_n40us(void)
{                            // 5cycles call
	asm("call _delay_40us"); // 40us
	asm("dec r19");          // 1cycle
	asm("cpi r19, 0");       // 1cycle
	asm("brne .-10");         // 1/2cycles
}                            // 5cycles ret


//lcd functions

void lcd_write(uint8_t val)
{
	if (val & 0x80) PORT(LCD_PIN_D7) |= __MSK(LCD_PIN_D7); else PORT(LCD_PIN_D7) &= ~__MSK(LCD_PIN_D7);
	if (val & 0x40) PORT(LCD_PIN_D6) |= __MSK(LCD_PIN_D6); else PORT(LCD_PIN_D6) &= ~__MSK(LCD_PIN_D6);
	if (val & 0x20) PORT(LCD_PIN_D5) |= __MSK(LCD_PIN_D5); else PORT(LCD_PIN_D5) &= ~__MSK(LCD_PIN_D5);
	if (val & 0x10) PORT(LCD_PIN_D4) |= __MSK(LCD_PIN_D4); else PORT(LCD_PIN_D4) &= ~__MSK(LCD_PIN_D4);
	delay_125ns();
	PORT(LCD_PIN_EN) |= __MSK(LCD_PIN_EN);
	delay_625ns();
	PORT(LCD_PIN_EN) &= ~__MSK(LCD_PIN_EN);
	if (val & 0x08) PORT(LCD_PIN_D7) |= __MSK(LCD_PIN_D7); else PORT(LCD_PIN_D7) &= ~__MSK(LCD_PIN_D7);
	if (val & 0x04) PORT(LCD_PIN_D6) |= __MSK(LCD_PIN_D6); else PORT(LCD_PIN_D6) &= ~__MSK(LCD_PIN_D6);
	if (val & 0x02) PORT(LCD_PIN_D5) |= __MSK(LCD_PIN_D5); else PORT(LCD_PIN_D5) &= ~__MSK(LCD_PIN_D5);
	if (val & 0x01) PORT(LCD_PIN_D4) |= __MSK(LCD_PIN_D4); else PORT(LCD_PIN_D4) &= ~__MSK(LCD_PIN_D4);
	delay_125ns();
	PORT(LCD_PIN_EN) |= __MSK(LCD_PIN_EN);
	delay_625ns();
	PORT(LCD_PIN_EN) &= ~__MSK(LCD_PIN_EN);
	PORT(LCD_PIN_D7) |= __MSK(LCD_PIN_D7);
	PORT(LCD_PIN_D6) |= __MSK(LCD_PIN_D6);
	PORT(LCD_PIN_D5) |= __MSK(LCD_PIN_D5);
	PORT(LCD_PIN_D4) |= __MSK(LCD_PIN_D4);
}

void lcd_ini(void)
{
	DDR(LCD_PIN_EN) |= __MSK(LCD_PIN_EN);
	DDR(LCD_PIN_RS) |= __MSK(LCD_PIN_RS);
	DDR(LCD_PIN_D7) |= __MSK(LCD_PIN_D7);
	DDR(LCD_PIN_D6) |= __MSK(LCD_PIN_D6);
	DDR(LCD_PIN_D5) |= __MSK(LCD_PIN_D5);
	DDR(LCD_PIN_D4) |= __MSK(LCD_PIN_D4);
	PORT(LCD_PIN_EN) &= ~__MSK(LCD_PIN_EN);
	PORT(LCD_PIN_RS) &= ~__MSK(LCD_PIN_RS);
	PORT(LCD_PIN_D7) |= __MSK(LCD_PIN_D7);
	PORT(LCD_PIN_D6) |= __MSK(LCD_PIN_D6);
	PORT(LCD_PIN_D5) |= __MSK(LCD_PIN_D5);
	PORT(LCD_PIN_D4) |= __MSK(LCD_PIN_D4);
	delay_n40us(200);
	delay_n40us(175); //15ms (orig 15ms)
	PORT(LCD_PIN_D7) &= ~__MSK(LCD_PIN_D7);
	PORT(LCD_PIN_D6) &= ~__MSK(LCD_PIN_D6);
	delay_125ns(); //125ns (orig 100ns)
	PORT(LCD_PIN_EN) |= __MSK(LCD_PIN_EN);
	delay_625ns(); //625ns (orig 500ns)
	PORT(LCD_PIN_EN) &= ~__MSK(LCD_PIN_EN);
	delay_n40us(103); //4120us (orig 4100us)
	PORT(LCD_PIN_EN) |= __MSK(LCD_PIN_EN);
	delay_625ns(); //625ns (orig 500ns)
	PORT(LCD_PIN_EN) &= ~__MSK(LCD_PIN_EN);
	delay_n40us(3); //120us (orig 100us)
	PORT(LCD_PIN_EN) |= __MSK(LCD_PIN_EN);
	delay_625ns(); //625ns (orig 500ns)
	PORT(LCD_PIN_EN) &= ~__MSK(LCD_PIN_EN);
	delay_40us(); //40us (orig 40us)
	PORT(LCD_PIN_D4) &= ~__MSK(LCD_PIN_D4);
	delay_125ns(); //125ns (orig 100ns)
	PORT(LCD_PIN_EN) |= __MSK(LCD_PIN_EN);
	delay_625ns(); //625ns (orig 500ns)
	PORT(LCD_PIN_EN) &= ~__MSK(LCD_PIN_EN);
	delay_40us(); //40us (orig 40us)
	PORT(LCD_PIN_D4) &= ~__MSK(LCD_PIN_D4);
	delay_125ns(); //125ns (orig 100ns)
	PORT(LCD_PIN_EN) |= __MSK(LCD_PIN_EN);
	delay_625ns(); //625ns (orig 500ns)
	PORT(LCD_PIN_EN) &= ~__MSK(LCD_PIN_EN);
	delay_625ns(); //625ns (orig 500ns)
	PORT(LCD_PIN_D7) |= __MSK(LCD_PIN_D7);
	delay_125ns(); //125ns (orig 100ns)
	PORT(LCD_PIN_EN) |= __MSK(LCD_PIN_EN);
	delay_625ns(); //625ns (orig 500ns)
	PORT(LCD_PIN_EN) &= ~__MSK(LCD_PIN_EN);
	delay_40us(); //40us (orig 40us)
	lcd_cmd(LCD_CMD_DISPLAYCONTROL, 1);
	lcd_cmd(LCD_CMD_CLEARDISPLAY, 1);
	lcd_cmd(LCD_CMD_ENTRYMODESET | LCD_FLG_ENTRYSHIFTINC, 1);
	lcd_cmd(LCD_CMD_DISPLAYCONTROL | LCD_FLG_DISPLAYON, 1);
#ifdef LCD_FILE
	fdev_setup_stream(lcdio, lcd_putchar, lcd_getchar, _FDEV_SETUP_WRITE | _FDEV_SETUP_READ); //setup lcd i/o stream
#endif //LCD_FILE
#ifdef LCD_KNOB
	DDR(LCD_PIN_BTN_EN1) &= ~__MSK(LCD_PIN_BTN_EN1);
	DDR(LCD_PIN_BTN_EN2) &= ~__MSK(LCD_PIN_BTN_EN2);
	DDR(LCD_PIN_BTN_ENC) &= ~__MSK(LCD_PIN_BTN_ENC);
	PORT(LCD_PIN_BTN_EN1) |= __MSK(LCD_PIN_BTN_EN1);
	PORT(LCD_PIN_BTN_EN2) |= __MSK(LCD_PIN_BTN_EN2);
	PORT(LCD_PIN_BTN_ENC) |= __MSK(LCD_PIN_BTN_ENC);
#endif //LCD_KNOB

#ifdef LCD_IBUF
	rbuf_ini(lcd_ibuf, LCD_IBUF - 4);
#endif //LCD_IBUF

#ifdef LCD_OBUF
	rbuf_ini(lcd_obuf, LCD_OBUF - 4);
#endif //LCD_OBUF

}

void lcd_cmd(uint8_t cmd, uint8_t wait)
{
	PORT(LCD_PIN_RS) &= ~__MSK(LCD_PIN_RS);
	lcd_write(cmd);
	if (wait == 0) return;
	if ((cmd & LCD_CMD_CLEARDISPLAY) || (cmd & LCD_CMD_RETURNHOME))
		delay_n40us(41); //1640us (orig 1640us)
	else
		delay_40us(); //40us (orig 40us)
}

void lcd_chr(uint8_t chr, uint8_t wait)
{
	PORT(LCD_PIN_RS) |= __MSK(LCD_PIN_RS);
	lcd_write(chr);
	if (wait == 0) return;
	delay_40us(); //40us (orig 40us)
}

int lcd_put(uint8_t c)
{
#ifdef LCD_OBUF
#ifdef LCD_ONBL
	return rbuf_put(lcd_obuf, c);
#else LCD_ONBL
	while (rbuf_put(lcd_obuf, c) < 0);
	return 0;
#endif LCD_ONBL
#else LCD_OBUF
	lcd_chr(c, 1);
	return 0;
#endif //LCD_OBUF
}

#ifdef LCD_KNOB
int lcd_get(void)
{
//	return lcd_test;
	uint8_t btn = 0;
	if ((PIN(LCD_PIN_BTN_EN1) & __MSK(LCD_PIN_BTN_EN1)) == 0) btn |= 1;
	if ((PIN(LCD_PIN_BTN_EN2) & __MSK(LCD_PIN_BTN_EN2)) == 0) btn |= 2;
	if ((PIN(LCD_PIN_BTN_ENC) & __MSK(LCD_PIN_BTN_ENC)) == 0) btn |= 4;
	return btn;
}
#endif //LCD_KNOB

#ifdef LCD_OBUF
void lcd_100us(void)
{
	int c = rbuf_get(lcd_obuf);
	if (c > 0) lcd_chr(c, 0);
}
#endif //LCD_OBUF

#endif //LCD_4BIT