//swi2c.c - Software I2C
//#ifdef SWI2C

#include "swi2c.h"
#include <avr/io.h>
#include "io_atmega2560.h"


#define SWI2C_RMSK   0x01 //read mask (bit0 = 1)
#define SWI2C_WMSK   0x00 //write mask (bit0 = 0)
#define SWI2C_ASHF   0x01 //address shift (<< 1)
#define SWI2C_DMSK   0x7f //device address mask


void swi2c_init(void)
{
	PIN_OUT(SWI2C_SDA);
	PIN_OUT(SWI2C_SCL);
	PIN_SET(SWI2C_SDA);
	PIN_SET(SWI2C_SCL);
	SWI2C_DEL;
}

void swi2c_start(void)
{
	PIN_CLR(SWI2C_SDA);
	SWI2C_DEL;
	PIN_CLR(SWI2C_SCL);
	SWI2C_DEL;
}

void swi2c_stop(void)
{
	PIN_SET(SWI2C_SCL);
	SWI2C_DEL;
	PIN_SET(SWI2C_SDA);
	SWI2C_DEL;
}

void swi2c_ack(void)
{
	PIN_CLR(SWI2C_SDA);
	SWI2C_DEL;
	PIN_SET(SWI2C_SCL);
	SWI2C_DEL;
	PIN_CLR(SWI2C_SCL);
	SWI2C_DEL;
}

uint8_t swi2c_wait_ack(void)
{
	PIN_INP(SWI2C_SDA);
	SWI2C_DEL;
//	PIN_SET(SWI2C_SDA);
	SWI2C_DEL;
	PIN_SET(SWI2C_SCL);
//	SWI2C_DEL;
	uint16_t timer = SWI2C_TMO;
	uint8_t ack = 0;
	while (!(ack = (PIN_GET(SWI2C_SDA)?0:1)) && timer--) SWI2C_DEL;
	PIN_CLR(SWI2C_SCL);
	SWI2C_DEL;
	PIN_OUT(SWI2C_SDA);
	SWI2C_DEL;
	PIN_CLR(SWI2C_SDA);
	SWI2C_DEL;
	return ack;
}

uint8_t swi2c_read(void)
{
	PIN_SET(SWI2C_SDA);
	SWI2C_DEL;
	PIN_INP(SWI2C_SDA);
	uint8_t data = 0;
	int8_t bit; for (bit = 7; bit >= 0; bit--)
	{
		PIN_SET(SWI2C_SCL);
		SWI2C_DEL;
		data |= PIN_GET(SWI2C_SDA)?(1 << bit):0;
		PIN_CLR(SWI2C_SCL);
		SWI2C_DEL;
	}
	PIN_OUT(SWI2C_SDA);
	return data;
}

void swi2c_write(uint8_t data)
{
	int8_t bit; for (bit = 7; bit >= 0; bit--)
	{
		if (data & (1 << bit)) PIN_SET(SWI2C_SDA);
		else PIN_CLR(SWI2C_SDA);
		SWI2C_DEL;
		PIN_SET(SWI2C_SCL);
		SWI2C_DEL;
		PIN_CLR(SWI2C_SCL);
		SWI2C_DEL;
	}
}

int swi2c_check(uint8_t dev_addr)
{
	swi2c_start();
	swi2c_write((dev_addr & SWI2C_DMSK) << SWI2C_ASHF);
	if (!swi2c_wait_ack()) { swi2c_stop(); return -1; }
	swi2c_stop();
	return 0;
}

#ifdef SWI2C_A8 //8bit address

int swi2c_readByte_A8(uint8_t dev_addr, uint8_t addr)
{
	swi2c_start();
	swi2c_write(SWI2C_WMSK | ((dev_addr & SWI2C_DMSK) << SWI2C_ASHF));
	if (!swi2c_wait_ack()) { swi2c_stop(); return -1; }
	swi2c_write(addr & 0xff);
	if (!swi2c_wait_ack()) return -1;
	swi2c_stop();
	swi2c_start();
	swi2c_write(SWI2C_RMSK | ((dev_addr & SWI2C_DMSK) << SWI2C_ASHF));
	if (!swi2c_wait_ack()) return -1;
	uint8_t b = swi2c_read();
	swi2c_stop();
	return b;
}

int swi2c_writeByte_A8(uint8_t dev_addr, uint8_t addr, uint8_t b)
{
	swi2c_start();
	swi2c_write(SWI2C_WMSK | ((dev_addr & SWI2C_DMSK) << SWI2C_ASHF));
	if (!swi2c_wait_ack()) { swi2c_stop(); return -1; }
	swi2c_write(addr & 0xff);
	if (!swi2c_wait_ack()) return -1;
	swi2c_write(b);
	if (!swi2c_wait_ack()) return -1;
	swi2c_stop();
	return 0;
}

#endif //SWI2C_A8

#ifdef SWI2C_A16 //16bit address

int swi2c_readByte_A16(uint8_t dev_addr, unsigned short addr)
{
	swi2c_start();
	swi2c_write(SWI2C_WMSK | ((dev_addr & SWI2C_DMSK) << SWI2C_ASHF));
	if (!swi2c_wait_ack()) { swi2c_stop(); return -1; }
	swi2c_write(addr >> 8);
	if (!swi2c_wait_ack()) return -1;
	swi2c_write(addr & 0xff);
	if (!swi2c_wait_ack()) return -1;
	swi2c_stop();
	swi2c_start();
	swi2c_write(SWI2C_RMSK | ((dev_addr & SWI2C_DMSK) << SWI2C_ASHF));
	if (!swi2c_wait_ack()) return -1;
	uint8_t b = swi2c_read();
	swi2c_stop();
	return b;
}

int swi2c_writeByte_A16(uint8_t dev_addr, unsigned short addr, uint8_t b)
{
	swi2c_start();
	swi2c_write(SWI2C_WMSK | ((dev_addr & SWI2C_DMSK) << SWI2C_ASHF));
	if (!swi2c_wait_ack()) { swi2c_stop(); return -1; }
	swi2c_write(addr >> 8);
	if (!swi2c_wait_ack()) return -1;
	swi2c_write(addr & 0xff);
	if (!swi2c_wait_ack()) return -1;
	swi2c_write(b);
	if (!swi2c_wait_ack()) return -1;
	swi2c_stop();
	return 0;
}

#endif //SWI2C_A16


//#endif //SWI2C