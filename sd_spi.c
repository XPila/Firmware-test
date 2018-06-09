//w25x20cl.c

#include "sd_spi.h"
#include <avr/io.h>
#include "io_atmega2560.h"
#include "swspi.h"


#define _CS_LOW()  PORT(SD_PIN_CS) &= ~__MSK(SD_PIN_CS)
#define _CS_HIGH() PORT(SD_PIN_CS) |= __MSK(SD_PIN_CS)

#define sd_cmd_00(arg) sd_cmd(0x00, arg, 0, 0)
#define sd_cmd_41(arg) sd_cmd(0x41, arg, 0, 0)
#define sd_cmd_55(arg) sd_cmd(0x55, arg, 0, 0)

void _send_request(uint8_t cmd, uint32_t arg);
sd_response_t _recieve_response(void);


int8_t sd_ini(void)
{
	return 0;
}

int16_t sd_read_block(uint32_t addr, uint8_t* data, uint16_t size)
{
	return 0;
}

int16_t sd_write_block(uint32_t addr, uint8_t* data, uint16_t size)
{
	return 0;
}

sd_response_t sd_cmd(uint8_t cmd, uint32_t arg)
{
	_CS_LOW();
	_send_request(cmd, arg);
	sd_response_t rsp = _recieve_response();
	_CS_HIGH();
	return rsp;
}



sd_response_t sd_cmd_08(uint32_t arg, sd_response_R7_t* rsp_R7)
{
	_CS_LOW();
	_send_request(0x08, arg);
	sd_response_t rsp = _recieve_response();
	_CS_HIGH();
	return rsp;
}

void _send_request(uint8_t cmd, uint32_t arg)
{

}

sd_response_t _recieve_response(void)
{
	sd_response_t response;
	return response;
}