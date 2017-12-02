//lcd.c
#include "lcd.h"
#include <avr/io.h>
#include "io_atmega2560.h"

#ifdef LCD_4BIT


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

void delay_500ms(void)
{
	uint8_t i = 125;
	while (i--)
		delay_n40us(100);
}
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
	lcd_cmd(LCD_CMD_DISPLAYCONTROL);
	lcd_cmd(LCD_CMD_CLEARDISPLAY);
	lcd_cmd(LCD_CMD_ENTRYMODESET | LCD_FLG_ENTRYSHIFTINC);
	lcd_cmd(LCD_CMD_DISPLAYCONTROL | LCD_FLG_DISPLAYON);
}

void lcd_cmd(uint8_t cmd)
{
	PORT(LCD_PIN_RS) &= ~__MSK(LCD_PIN_RS);
	lcd_write(cmd);
	if ((cmd & LCD_CMD_CLEARDISPLAY) || (cmd & LCD_CMD_RETURNHOME))
		delay_n40us(41); //1640us (orig 1640us)
	else
		delay_40us(); //40us (orig 40us)
}

void lcd_chr(uint8_t chr)
{
	PORT(LCD_PIN_RS) |= __MSK(LCD_PIN_RS);
	lcd_write(chr);
	delay_40us(); //40us (orig 40us)
}

#endif //LCD_4BIT