//swi2c.h - Software I2C
#ifndef SWI2C_H
#define SWI2C_H

#include <inttypes.h>
#include "config.h"


#if defined(__cplusplus)
extern "C" {
#endif //defined(__cplusplus)


//initialize pins
extern void swi2c_init(void);

//check device address acknowledge
extern int swi2c_check(uint8_t dev_addr);

//read write functions - 8bit address (most i2c chips)
#ifdef SWI2C_A8
extern int swi2c_readByte_A8(uint8_t dev_addr, uint8_t addr);
extern int swi2c_writeByte_A8(uint8_t dev_addr, uint8_t addr, uint8_t b);
#endif //SWI2C_A8

//read write functions - 16bit address (e.g. serial eeprom AT24C256)
#ifdef SWI2C_A16
extern int swi2c_readByte_A16(uint8_t dev_addr, unsigned short addr);
extern int swi2c_writeByte_A16(uint8_t dev_addr, unsigned short addr, uint8_t b);
#endif //SWI2C_A16


#if defined(__cplusplus)
}
#endif //defined(__cplusplus)
#endif //SWI2C_H
