#ifndef _CONFIG_H
#define _CONFIG_H

//LED pin connection
#define LED_PIN 13

//TIMER0 configuration
#define TIMER0_PRESCALER   (1 << CS00) | (1 << CS01)
#define TIMER0_CYC_100US   25


//UART0 configuration
#define UART0               // enable uart0
#define UART0_BAUD  115200  // baudrate
#define UART0_IBUF     256  // input buffer size (for rx data)
#define UART0_OBUF      64  // output buffer size (for tx data)
#define UART0_RXNB          // rx non blocking mode
//#define UART0_TXNB          // tx non blocking mode
#define UART0_FILE          // uart0 file stream uart0io

//LCD configuration
#define LCD_4BIT      // 4bit mode
#define LCD_KNOB      // lcd knob input
#define LCD_IBUF    8 // input buffer size (for knob data input)
#define LCD_OBUF   32 // output buffer size (for lcd data output)
#define LCD_FILE      // lcd file stream lcdio
//LCD pin connection
#define LCD_PIN_EN 61 // enable signal
#define LCD_PIN_RS 82 // register select signal
#define LCD_PIN_D4 59 // data line 4
#define LCD_PIN_D5 70 // data line 5
#define LCD_PIN_D6 85 // data line 6
#define LCD_PIN_D7 71 // data line 7
#define LCD_PIN_BL 32 // back light control


#endif //_CONFIG_H
