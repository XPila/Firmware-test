//tmc2130.c

#include "tmc2130.h"
#include <avr/io.h>
#include "io_atmega2560.h"
#include "swspi.h"

#define _CS_LOW(axis)  tmc2130_cs_low(axis)
#define _CS_HIGH(axis) tmc2130_cs_high(axis)
#define tmc2130_rd(axis, addr, rval) tmc2130_txrx(axis, addr, 0, rval)
#define tmc2130_wr(axis, addr, wval) tmc2130_txrx(axis, addr | 0x80, wval, 0)

typedef union 
{
	uint32_t ui32;
	uint16_t ui16[2];
	uint8_t  ui8[4];
} tmc2130_reg_t;

uint8_t tmc2130_txrx(uint8_t axis, uint8_t addr, uint32_t wval, uint32_t* rval);
//uint8_t tmc2130_tx(uint8_t axis, uint8_t addr, uint32_t wval);
//uint8_t tmc2130_rx(uint8_t axis, uint8_t addr, uint32_t* rval);


int8_t tmc2130_ini(void)
{
	return 1;
}

inline void tmc2130_cs_low(uint8_t axis)
{
	switch (axis)
	{
	case 0: PORT(TMC2130_PIN_CS_X) &= ~__MSK(TMC2130_PIN_CS_X); break;
	case 1: PORT(TMC2130_PIN_CS_Y) &= ~__MSK(TMC2130_PIN_CS_Y); break;
	case 2: PORT(TMC2130_PIN_CS_Z) &= ~__MSK(TMC2130_PIN_CS_Z); break;
	case 3: PORT(TMC2130_PIN_CS_E) &= ~__MSK(TMC2130_PIN_CS_E); break;
	}
}

inline void tmc2130_cs_high(uint8_t axis)
{
	switch (axis)
	{
	case 0: PORT(TMC2130_PIN_CS_X) |= __MSK(TMC2130_PIN_CS_X); break;
	case 1: PORT(TMC2130_PIN_CS_Y) |= __MSK(TMC2130_PIN_CS_Y); break;
	case 2: PORT(TMC2130_PIN_CS_Z) |= __MSK(TMC2130_PIN_CS_Z); break;
	case 3: PORT(TMC2130_PIN_CS_E) |= __MSK(TMC2130_PIN_CS_E); break;
	}
}

uint8_t tmc2130_txrx(uint8_t axis, uint8_t addr, uint32_t wval, uint32_t* rval)
{
	_CS_LOW(axis);

	_CS_HIGH(axis);
	return 0;
}
