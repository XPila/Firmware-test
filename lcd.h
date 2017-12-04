//lcd.h
#ifndef _LCD_H
#define _LCD_H

#include <inttypes.h>
#include "config.h"

#if (defined(LCD_FILE))
#include <stdio.h>
#endif

#define LCD_CMD_CLEARDISPLAY    0x01
#define LCD_CMD_RETURNHOME      0x02
#define LCD_CMD_ENTRYMODESET    0x04
#define LCD_CMD_DISPLAYCONTROL  0x08
#define LCD_CMD_CURSORSHIFT     0x10
#define LCD_CMD_FUNCTIONSET     0x20
#define LCD_CMD_SETCGRAMADDR    0x40
#define LCD_CMD_SETDDRAMADDR    0x80

#define LCD_FLG_FUNC8BIT        0x10
#define LCD_FLG_FUNC2LINE       0x08
#define LCD_FLG_FUNC10DOTS      0x04
#define LCD_FLG_SHIFTDISPLAY    0x08
#define LCD_FLG_SHIFTRIGHT      0x04
#define LCD_FLG_DISPLAYON       0x04
#define LCD_FLG_CURSORON        0x02
#define LCD_FLG_BLINKON         0x01
#define LCD_FLG_ENTRYLEFT       0x01
#define LCD_FLG_ENTRYSHIFTINC   0x02


#ifdef LCD_FILE
#define lcdio (&_lcdio)
extern FILE _lcdio;
#endif //LCD_FILE


extern void lcd_ini(void);
extern void lcd_cmd(uint8_t cmd, uint8_t wait);
extern void lcd_chr(uint8_t chr, uint8_t wait);
extern int lcd_put(uint8_t c);

#ifdef LCD_KNOB
extern int lcd_get(void);
#endif //LCD_KNOB

#ifdef LCD_OBUF
extern void lcd_100us(void);
#endif //LCD_OBUF


#endif //_LCD_H
