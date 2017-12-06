//swspi.c
//#ifdef //__SWSPI
#include "swspi.h"
#include <avr/io.h>
#include "io_atmega2560.h"

//SWSPI configuration
#define SWSPI_DEL	0x0f //delay mask (0-3. bit, delay = 1 << DEL [us])
#define SWSPI_POL	0x10 //polarity mask (4. bit, 1=inverted)
#define SWSPI_PHA	0x20 //phase mask (5. bit)
#define SWSPI_DOR	0x40 //data order mask (6. bit, 0=MSB first, 1=LSB first)

#define SWSPI_SCK_UP if (SWSPI_CFG & SWSPI_POL) GPIO_CLR(SWSPI_SCK); else GPIO_SET(SWSPI_SCK);
#define SWSPI_SCK_DN if (SWSPI_CFG & SWSPI_POL) GPIO_SET(SWSPI_SCK); else GPIO_CLR(SWSPI_SCK);

#define GPIO_INP(gpio) DDR(gpio) &= ~__MSK(gpio)
#define GPIO_OUT(gpio) DDR(gpio) |= __MSK(gpio)
#define GPIO_SET(gpio) PORT(gpio) |= __MSK(gpio)
#define GPIO_CLR(gpio) PORT(gpio) &= ~__MSK(gpio)
#define GPIO_GET(gpio) (PIN(gpio) & __MSK(gpio))
#define DELAY(delay) _delay_us(delay)


void _delay_us(uint16_t us)
{
	while (us--) asm("nop");
}

void swspi_init()
{
	GPIO_INP(SWSPI_MISO);
	GPIO_OUT(SWSPI_MOSI);
	GPIO_OUT(SWSPI_SCK);
	GPIO_CLR(SWSPI_MOSI);
	SWSPI_SCK_DN;
}

void swspi_tx(unsigned char tx)
{
	int delay = (1 << (SWSPI_CFG & SWSPI_DEL));
	if (SWSPI_MISO == SWSPI_MOSI) GPIO_OUT(SWSPI_MOSI);
	unsigned char i = 0; for (; i < 8; i++)
	{
		if (tx & 0x80) GPIO_SET(SWSPI_MOSI);
		else GPIO_CLR(SWSPI_MOSI);
	    DELAY(delay);
		SWSPI_SCK_UP;
	    DELAY(delay);
		SWSPI_SCK_DN;
		tx <<= 1;
//		tx >>= 1;
	}
}

unsigned char swspi_rx()
{
	int delay = (1 << (SWSPI_CFG & SWSPI_DEL));
	if (SWSPI_MISO == SWSPI_MOSI) GPIO_OUT(SWSPI_MOSI);
	unsigned char rx = 0;
	unsigned char i = 0; for (; i < 8; i++)
	{
//		rx >>= 1;
		rx <<= 1;
	    DELAY(delay);
		SWSPI_SCK_UP;
	    DELAY(delay);
		rx |= GPIO_GET(SWSPI_MISO)?0x01:0;
		SWSPI_SCK_DN;
	}
	return rx;
}

unsigned char swspi_txrx(unsigned char tx)
{
	int delay = (1 << (SWSPI_CFG & SWSPI_DEL));
	unsigned char rx = 0;
	unsigned char i = 0; for (; i < 8; i++)
	{
		rx <<= 1;
		if (tx & 0x80) GPIO_SET(SWSPI_MOSI);
		else GPIO_CLR(SWSPI_MOSI);
	    DELAY(delay);
		SWSPI_SCK_UP;
	    DELAY(delay);
		rx |= GPIO_GET(SWSPI_MISO)?1:0;
		SWSPI_SCK_DN;
		tx <<= 1;
	}
	return rx;
}

//#endif //__SWSPI
