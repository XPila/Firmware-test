#ifndef _CONFIG_H
#define _CONFIG_H

//LED pin connection
#define LED_PIN 13

//TIMER0 configuration
#define TIMER0_PRESCALER   (1 << CS00) | (1 << CS01) // f/64
#define TIMER0_CYC_100US   25                        // 25cyces = 100us
//#define TIMER0_CB_100US    lcd_100us                 // lcd callback
#define TIMER0_CB_100US    main_100us                //
#define TIMER0_CB_1MS      main_1ms                  //

//UART0 configuration
#define UART0               // enable uart0
#define UART0_BAUD  115200  // baudrate
#define UART0_IBUF     256  // input buffer size (for rx data)
#define UART0_OBUF      64  // output buffer size (for tx data)
#define UART0_INBL          // input non blocking mode
//#define UART0_ONBL          // output non blocking mode
#define UART0_FILE          // uart0 file stream uart0io

//LCD configuration
#define LCD_4BIT        // 4bit mode
#define LCD_KNOB        // lcd knob input
//#define LCD_IBUF    8   // input buffer size (for knob data input)
#define LCD_OBUF   64   // output buffer size (for lcd data output)
#define LCD_INBL        // input non blocking mode
//#define LCD_ONBL        // output non blocking mode
#define LCD_FILE        // lcd file stream lcdio
#define LCD_ESCC        // lcd escape codes
//LCD pin connection
#define LCD_PIN_EN 61   // enable signal
#define LCD_PIN_RS 82   // register select signal
#define LCD_PIN_D4 59   // data line 4
#define LCD_PIN_D5 70   // data line 5
#define LCD_PIN_D6 85   // data line 6
#define LCD_PIN_D7 71   // data line 7
//#define LCD_PIN_BL 32   // back light control
//buttons are directly attached using AUX-2
#define LCD_PIN_BTN_EN1  72 // phase1
#define LCD_PIN_BTN_EN2  14 // phase2
#define LCD_PIN_BTN_ENC   9 // the click

//ADC configuration
//#define ADC_CHAN_MSK      0b1111111111111111 //used AD channels bit mask (all)
#define ADC_CHAN_MSK      0b0000001001011111 //used AD channels bit mask (0,1,2,3,4,6,9)
#define ADC_CHAN_CNT      7         //number of used channels)
#define ADC_OVRSAMPL      16        //oversampling multiplier
#define ADC_CALLBACK      adc_ready //callback function ()

//SWPWM configuration
#define SWPWM_CHAN_CNT    3 //three channels
#define SWPWM_CHN0_PIN   13 //boot led
#define SWPWM_CHN1_PIN    6 //fan0 pin
#define SWPWM_CHN2_PIN    8 //fan1 pin
#define SWPWM_CHN0_MAX  127
#define SWPWM_CHN1_MAX  127
#define SWPWM_CHN2_MAX  127

//SWSPI configuration
#define SWSPI_DEL	_swdelay_625ns() //clock delay
#define SWSPI_POL	0 //clock polarity (0=normal, 1=inverted)
#define SWSPI_PHA	0 //phase
#define SWSPI_DOR	0 //data order (0=MSB first, 1=LSB first)
//SWSPI pin connection
#define SWSPI_MISO  50
#define SWSPI_MOSI  51
#define SWSPI_SCK   52

//SWI2C configuration
#define SWI2C_DEL _swdelay_625ns() //clock delay
//#define SWI2C_DEL _delay_10us() //clock delay
#define SWI2C_TMO 2048 //ack timeout in clock cycles
#define SWI2C_A8       //8bit address fuctions
//SWI2C pin connection
#define SWI2C_SDA   20
#define SWI2C_SCL   21

//PAT9125 configuration
#define PAT9125_ADDR 0x75
#define PAT9125_XRES  200
#define PAT9125_YRES  200

//W25X20CL configuration
#define W25X20CL_PIN_CS  32

//SD card configuration
#define SD_PIN_CS        77
#define SD_PIN_DETECT    15

//TMC2130 configuration
#define TMC2130_PIN_CS_X        41
#define TMC2130_PIN_CS_Y        39
#define TMC2130_PIN_CS_Z        67
#define TMC2130_PIN_CS_E        66




#if defined(__cplusplus)
extern "C" {
#endif //defined(__cplusplus)

extern void _swdelay_625ns(void);
extern void _swdelay_10us(void);

#if defined(__cplusplus)
}
#endif //defined(__cplusplus)
#endif //_CONFIG_H
