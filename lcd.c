//lcd.c
#include "lcd.h"
#include <avr/io.h>
#include "io_atmega2560.h"
#include "rbuf.h"


uint8_t _row_addr[4];

#ifdef LCD_IBUF
uint8_t lcd_ibuf[LCD_IBUF];
#endif //LCD_IBUF

#ifdef LCD_OBUF
uint8_t lcd_obuf[LCD_OBUF];
uint8_t _wait_counter;
#endif //LCD_OBUF

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

#ifdef LCD_ESCC
	uint8_t _escape[8];
#endif //LCD_ESCC

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

#ifdef LCD_4BIT

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
	_wait_counter = 0;
#endif //LCD_OBUF

#ifdef LCD_PIN_BL
	DDR(LCD_PIN_BL) |= __MSK(LCD_PIN_BL);
	PORT(LCD_PIN_BL) |= __MSK(LCD_PIN_BL);
#endif //LCD_PIN_BL

	_row_addr[0] = 0x00;
	_row_addr[1] = 0x40;
	_row_addr[2] = 0x14;
	_row_addr[3] = 0x54;

	_escape[0] = 0;
}

#endif //LCD_4BIT

void lcd_cmd(uint8_t cmd, uint8_t wait)
{
	PORT(LCD_PIN_RS) &= ~__MSK(LCD_PIN_RS);
	lcd_write(cmd);
#ifdef LCD_OBUF
	if ((cmd & LCD_CMD_CLEARDISPLAY) || (cmd & LCD_CMD_RETURNHOME))
		_wait_counter = 20;
#endif //LCD_OBUF
	if (wait == 0) return;
	if ((cmd & LCD_CMD_CLEARDISPLAY) || (cmd & LCD_CMD_RETURNHOME))
		delay_n40us(41); //1640us (orig 1640us)
	else
		delay_40us(); //40us (orig 40us)
}

void lcd_erase_screen(uint8_t wait)
{
	lcd_cmd(LCD_CMD_CLEARDISPLAY, wait);
}

void lcd_cursor_home(uint8_t c, uint8_t r, uint8_t wait)
{
	uint8_t addr = (_row_addr[r] + c) & 0x7f;
	lcd_cmd(LCD_CMD_SETDDRAMADDR | addr, wait);
}

void lcd_cursor_show(uint8_t wait)
{
	lcd_cmd(LCD_CMD_DISPLAYCONTROL | LCD_FLG_DISPLAYON | LCD_FLG_CURSORON, wait);
}

void lcd_cursor_hide(uint8_t wait)
{
	lcd_cmd(LCD_CMD_DISPLAYCONTROL | LCD_FLG_DISPLAYON, wait);
}

#ifdef LCD_ESCC
//Supported VT100 escape codes:
//EraseScreen  "\x1b[2J"
//CursorHome   "\x1b[%d;%dH"
//CursorShow   "\x1b[?25h"
//CursorHide   "\x1b[?25l"
void lcd_esc(uint8_t chr, uint8_t wait)
{
#define escape_cnt (_escape[0])        //escape character counter
#define is_num_msk (_escape[1])        //numeric character bit mask
#define chr_is_num (is_num_msk & 0x01) //current character is numeric
#define e_2_is_num (is_num_msk & 0x04) //escape char 2 is numeric
#define e_3_is_num (is_num_msk & 0x08) //...
#define e_4_is_num (is_num_msk & 0x10)
#define e_5_is_num (is_num_msk & 0x20)
#define e_6_is_num (is_num_msk & 0x40)
#define e_7_is_num (is_num_msk & 0x80)
#define e2_num (_escape[2] - '0')      //number from character 2
#define e3_num (_escape[3] - '0')      //number from character 3
#define e23_num (10*e2_num+e3_num)     //number from characters 2 and 3
#define e4_num (_escape[4] - '0')      //number from character 4
#define e5_num (_escape[5] - '0')      //number from character 5
#define e45_num (10*e4_num+e5_num)     //number from characters 4 and 5
#define e6_num (_escape[6] - '0')      //number from character 6
#define e56_num (10*e5_num+e6_num)     //number from characters 5 and 6
	if (escape_cnt > 1) // escape length > 1 = "\x1b["
	{
		_escape[escape_cnt] = chr; // store current char
		if ((chr >= '0') && (chr <= '9')) // char is numeric
			is_num_msk |= (1 | (1 << escape_cnt)); //set mask
		else
			is_num_msk &= ~1; //clear mask
	}
	switch (escape_cnt++)
	{
	case 0:
		if (chr == 0x1b) return;  // escape = "\x1b"
		break;
	case 1:
		is_num_msk = 0x00; // reset 'is number' bit mask
		if (chr == '[') return; // escape = "\x1b["
		break;
	case 2:
		switch (chr)
		{
		case '2': return; // escape = "\x1b[2"
		case '?': return; // escape = "\x1b[?"
		default:
			if (chr_is_num) return; // escape = "\x1b[%1d"
		}
		break;
	case 3:
		switch (_escape[2])
		{
		case '?': // escape = "\x1b[?"
			if (chr == '2') return; // escape = "\x1b[?2"
			break;
		case '2':
			if (chr == 'J') // escape = "\x1b[2J"
				{ lcd_erase_screen(wait); break; } // EraseScreen
		default:
			if (e_2_is_num && // escape = "\x1b[%1d"
				((chr == ';') || // escape = "\x1b[%1d;"
				chr_is_num)) // escape = "\x1b[%2d"
				return;
		}
		break;
	case 4:
		switch (_escape[2])
		{
		case '?': // "\x1b[?"
			if ((_escape[3] == '2') && (chr == '5')) return; // escape = "\x1b[?25"
			break;
		default:
			if (e_2_is_num) // escape = "\x1b[%1d"
			{
				if ((_escape[3] == ';') && chr_is_num) return; // escape = "\x1b[%1d;%1d"
				else if (e_3_is_num && (chr == ';')) return; // escape = "\x1b[%2d;"
			}
		}
		break;
	case 5:
		switch (_escape[2])
		{
		case '?':
			if ((_escape[3] == '2') && (_escape[4] == '5')) // escape = "\x1b[?25"
				switch (chr)
				{
				case 'h': // escape = "\x1b[?25h"
  					lcd_cursor_show(wait); // CursorShow
					break;
				case 'l': // escape = "\x1b[?25l"
					lcd_cursor_hide(wait); // CursorHide
					break;
				}
			break;
		default:
			if (e_2_is_num) // escape = "\x1b[%1d"
			{
				if ((_escape[3] == ';') && e_4_is_num) // escape = "\x1b%1d;%1dH"
				{
					if (chr == 'H') // escape = "\x1b%1d;%1dH"
						lcd_cursor_home(e4_num, e2_num, wait); // CursorHome
					else if (chr_is_num)
						return; // escape = "\x1b%1d;%2d"
				}
				else if (e_3_is_num && (_escape[4] == ';') && chr_is_num)
					return; // escape = "\x1b%2d;%1d"
			}
		}
		break;
	case 6:
		if (e_2_is_num) // escape = "\x1b[%1d"
		{
			if ((_escape[3] == ';') && e_4_is_num && e_5_is_num && (chr == 'H')) // escape = "\x1b%1d;%2dH"
				lcd_cursor_home(e45_num, e2_num, wait); // CursorHome
			else if (e_3_is_num && (_escape[4] == ';') && e_5_is_num) // escape = "\x1b%2d;%1d"
			{
				if (chr == 'H') // escape = "\x1b%2d;%1dH"
					lcd_cursor_home(e5_num, e23_num, wait); // CursorHome
				else if (chr_is_num) // "\x1b%2d;%2d"
					return;
			}
		}
		break;
	case 7:
		if (e_2_is_num && e_3_is_num && (_escape[4] == ';')) // "\x1b[%2d;"
			if (e_5_is_num && e_6_is_num && (chr == 'H')) // "\x1b[%2d;%2dH"
				lcd_cursor_home(e56_num, e23_num, wait); // CursorHome
		break;
	}
	escape_cnt = 0; // reset escape
end:
	return; // assume sucess
}
#endif //LCD_ESCC

void lcd_chr(uint8_t chr, uint8_t wait)
{
	if (_escape[0] || (chr == 0x1b))
	{
		lcd_esc(chr, wait);
		return;
	}
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
#else //LCD_ONBL
	while (rbuf_put(lcd_obuf, c) < 0);
	return 0;
#endif //LCD_ONBL
#else //LCD_OBUF
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
	if (_wait_counter)
	{
		_wait_counter--;
		return;
	}
	int c = rbuf_get(lcd_obuf);
	if (c > 0) lcd_chr(c, 0);
}
#endif //LCD_OBUF

