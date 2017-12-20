//pat9125.h - 2-axis IR-laser motion sensor
#ifndef _PAT9125_H
#define _PAT9125_H

#include <inttypes.h>
#include "config.h"

//PAT9125 I2C
//#define PAT9125_ADDR        0x75  //ID=LO
//#define PAT9125_ADDR        0x79  //ID=HI
//#define PAT9125_ADDR        0x73  //ID=NC


#if defined(__cplusplus)
extern "C" {
#endif //defined(__cplusplus)


extern uint8_t pat9125_PID1;
extern uint8_t pat9125_PID2;

extern uint8_t pat9125_xres;
extern uint8_t pat9125_yres;

extern int pat9125_x;
extern int pat9125_y;
extern uint8_t pat9125_b;
extern uint8_t pat9125_s;

extern int pat9125_ini(void);
extern int pat9125_update(void);
extern int pat9125_update_y(void);

extern int pat9125_rd_reg(uint8_t addr);
extern int pat9125_wr_reg(uint8_t addr, uint8_t data);


#if defined(__cplusplus)
}
#endif //defined(__cplusplus)
#endif //_PAT9125_H
