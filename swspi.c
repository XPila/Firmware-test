//swspi.c - software SPI
//#ifdef __SWSPI

#include "swspi.h"
#include <avr/io.h>
#include "io_atmega2560.h"


#if (SWSPI_POL == 0)
#define SWSPI_SCK_UP PIN_SET(SWSPI_SCK)
#define SWSPI_SCK_DN PIN_CLR(SWSPI_SCK)
#else
#define SWSPI_SCK_UP PIN_CLR(SWSPI_SCK)
#define SWSPI_SCK_DN PIN_SET(SWSPI_SCK)
#endif


void swspi_ini()
{
	PIN_INP(SWSPI_MISO);
	PIN_OUT(SWSPI_MOSI);
	PIN_OUT(SWSPI_SCK);
	PIN_CLR(SWSPI_MOSI);
	SWSPI_SCK_DN;
}

void swspi_tx(uint8_t tx)
{
#if (SWSPI_MISO == SWSPI_MOSI)
	PIN_OUT(SWSPI_MOSI);
#endif //(SWSPI_MISO == SWSPI_MOSI)
	register uint8_t i = 0; for (; i < 8; i++)
	{
		if (tx & 0x80) PIN_SET(SWSPI_MOSI);
		else PIN_CLR(SWSPI_MOSI);
	    SWSPI_DEL;
		SWSPI_SCK_UP;
	    SWSPI_DEL;
		SWSPI_SCK_DN;
		tx <<= 1;
	}
}

uint8_t swspi_rx()
{
#if (SWSPI_MISO == SWSPI_MOSI)
	PIN_OUT(SWSPI_MOSI);
#endif //(SWSPI_MISO == SWSPI_MOSI)
	register uint8_t rx = 0;
	register uint8_t i = 0; for (; i < 8; i++)
	{
		rx <<= 1;
	    SWSPI_DEL;
		SWSPI_SCK_UP;
	    SWSPI_DEL;
		rx |= PIN_GET(SWSPI_MISO)?0x01:0;
		SWSPI_SCK_DN;
	}
	return rx;
}

#if (SWSPI_MISO != SWSPI_MOSI)
uint8_t swspi_txrx(uint8_t tx)
{
	register uint8_t rx = 0;
	register uint8_t i = 0; for (; i < 8; i++)
	{
		rx <<= 1;
		if (tx & 0x80) PIN_SET(SWSPI_MOSI);
		else PIN_CLR(SWSPI_MOSI);
	    SWSPI_DEL;
		SWSPI_SCK_UP;
	    SWSPI_DEL;
		rx |= PIN_GET(SWSPI_MISO)?1:0;
		SWSPI_SCK_DN;
		tx <<= 1;
	}
	return rx;
}
#endif //(SWSPI_MISO != SWSPI_MOSI)

//#endif //__SWSPI
