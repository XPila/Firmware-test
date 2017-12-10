//pat9125.c - 2-axis IR-laser motion sensor
//#ifdef PAT9125

#include "pat9125.h"

#define _I2C_TX(addr, data) swi2c_writeByte_A8(PAT9125_ADDR, addr, data)
#define _I2C_RX(addr) swi2c_readByte_A8(PAT9125_ADDR, addr)

//PAT9125 registers
#define PAT9125_PID1			0x00
#define PAT9125_PID2			0x01
#define PAT9125_MOTION			0x02
#define PAT9125_DELTA_XL		0x03
#define PAT9125_DELTA_YL		0x04
#define PAT9125_MODE			0x05
#define PAT9125_CONFIG			0x06
#define PAT9125_WP				0x09
#define PAT9125_SLEEP1			0x0a
#define PAT9125_SLEEP2			0x0b
#define PAT9125_RES_X			0x0d
#define PAT9125_RES_Y			0x0e
#define PAT9125_DELTA_XYH		0x12
#define PAT9125_SHUTTER			0x14
#define PAT9125_FRAME			0x17
#define PAT9125_ORIENTATION		0x19


uint8_t pat9125_PID1 = 0;
uint8_t pat9125_PID2 = 0;
uint8_t pat9125_xres = 0;
uint8_t pat9125_yres = 0;
int pat9125_x = 0;
int pat9125_y = 0;
uint8_t pat9125_b = 0;
uint8_t pat9125_s = 0;


int pat9125_init(void)
{
	pat9125_xres = PAT9125_XRES;
	pat9125_yres = PAT9125_YRES;
	pat9125_PID1 = pat9125_rd_reg(PAT9125_PID1);
	pat9125_PID2 = pat9125_rd_reg(PAT9125_PID2);
//	pat9125_PID1 = 0x31;
//	pat9125_PID2 = 0x91;
	if ((pat9125_PID1 != 0x31) || (pat9125_PID2 != 0x91)) return 0;
    pat9125_wr_reg(PAT9125_RES_X, pat9125_xres);
    pat9125_wr_reg(PAT9125_RES_Y, pat9125_yres);
//	pat9125_wr_reg(PAT9125_ORIENTATION, 0x04 | (xinv?0x08:0) | (yinv?0x10:0)); //!? direction switching does not work
	return -1;
}

int pat9125_update(void)
{
	if ((pat9125_PID1 == 0x31) && (pat9125_PID2 == 0x91))
	{
		uint8_t ucMotion = pat9125_rd_reg(PAT9125_MOTION);
		pat9125_b = pat9125_rd_reg(PAT9125_FRAME);
		pat9125_s = pat9125_rd_reg(PAT9125_SHUTTER);
		if (ucMotion & 0x80)
		{
			uint8_t ucXL = pat9125_rd_reg(PAT9125_DELTA_XL);
			uint8_t ucYL = pat9125_rd_reg(PAT9125_DELTA_YL);
			uint8_t ucXYH = pat9125_rd_reg(PAT9125_DELTA_XYH);
			int iDX = ucXL | ((ucXYH << 4) & 0xf00);
			int iDY = ucYL | ((ucXYH << 8) & 0xf00);
			if (iDX & 0x800) iDX -= 4096;
			if (iDY & 0x800) iDY -= 4096;
			pat9125_x += iDX;
			pat9125_y -= iDY; //negative number, because direction switching does not work
			return 0;
		}
	}
	return -1;
}

int pat9125_update_y(void)
{
	if ((pat9125_PID1 == 0x31) && (pat9125_PID2 == 0x91))
	{
		uint8_t ucMotion = pat9125_rd_reg(PAT9125_MOTION);
		if (ucMotion & 0x80)
		{
			uint8_t ucYL = pat9125_rd_reg(PAT9125_DELTA_YL);
			uint8_t ucXYH = pat9125_rd_reg(PAT9125_DELTA_XYH);
			int iDY = ucYL | ((ucXYH << 8) & 0xf00);
			if (iDY & 0x800) iDY -= 4096;
			pat9125_y -= iDY; //negative number, because direction switching does not work
			return 0;
		}
	}
	return -1;
}

int pat9125_rd_reg(uint8_t addr)
{
	return _I2C_RX(addr);
}

int pat9125_wr_reg(uint8_t addr, uint8_t data)
{
	return _I2C_TX(addr, data);
}


//#endif //PAT9125
