//w25x20cl.h
#ifndef _W25X20CL_H
#define _W25X20CL_H

#include <inttypes.h>


#define W25_STATUS_BUSY   0x01
#define W25_STATUS_WEL    0x02
#define W25_STATUS_BP0    0x04
#define W25_STATUS_BP1    0x08
#define W25_STATUS_TB     0x20
#define W25_STATUS_SRP    0x80


#if defined(__cplusplus)
extern "C" {
#endif //defined(__cplusplus)


extern uint8_t w25x20cl_uid[8];


extern int w25x20cl_ini(void);
extern void w25x20cl_enable_wr(void);
extern void w25x20cl_disable_wr(void);
extern uint8_t w25x20cl_rd_status_reg(void);
extern void w25x20cl_wr_status_reg(uint8_t val);
extern void w25x20cl_rd_data(uint32_t addr, uint8_t* data, uint8_t cnt);
extern void w25x20cl_page_program(uint32_t addr, uint8_t* data, uint8_t cnt);
extern void w25x20cl_sector_erase(uint32_t addr);
extern void w25x20cl_block32_erase(uint32_t addr);
extern void w25x20cl_block64_erase(uint32_t addr);
extern void w25x20cl_chip_erase(void);


#if defined(__cplusplus)
}
#endif //defined(__cplusplus)
#endif //_W25X20CL_H
