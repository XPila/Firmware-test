//sd_spi.h
#ifndef _SD_SPI_H
#define _SD_SPI_H

#include <inttypes.h>


#if defined(__cplusplus)
extern "C" {
#endif //defined(__cplusplus)


//#pragma pack(push) // ignored in avrgcc
//#pragma pack(1)

typedef struct //1byte
{
	uint8_t idle_state:1;
	uint8_t erase_reset:1;
	uint8_t ilegal_command:1;
	uint8_t crc_error:1;
	uint8_t erase_error:1;
	uint8_t address_error:1;
	uint8_t parameter_error:1;
	uint8_t start_bit:1;
} sd_response_t;

typedef struct //4bytes
{
	uint8_t check_pattern:8;
	uint8_t voltage_accepted:4;
	uint8_t reserved0:8;
	uint8_t reserved1:8;
	uint8_t command_version:4;
} sd_response_R7_t;

typedef struct //1byte
{
	uint8_t card_locked:1;
	uint8_t lock_unlock_failed:1;
	uint8_t unspecified_error:1;
	uint8_t card_controller_error:1;
	uint8_t card_eec_failed:1;
	uint8_t wp_violation:1;
	uint8_t erase_parameter:1;
	uint8_t out_of_range:1;
} sd_status_t;

typedef struct //1byte
{
	uint8_t unspecified_error:1;
	uint8_t card_controller_error:1;
	uint8_t card_eec_failed:1;
	uint8_t out_of_range:1;
	uint8_t card_locked:1;
	uint8_t zero:3;
} sd_error_t;

typedef struct //4bytes
{
	uint8_t reserved0:4;       // 0..3
	uint8_t vdd_16_17:1;       // 4
	uint8_t vdd_17_18:1;       // 5
	uint8_t vdd_18_19:1;       // 6
	uint8_t vdd_19_20:1;       // 7
	uint8_t vdd_20_21:1;       // 8
	uint8_t vdd_21_22:1;       // 9
	uint8_t vdd_22_23:1;       // 10
	uint8_t vdd_23_24:1;       // 11
	uint8_t vdd_24_25:1;       // 12
	uint8_t vdd_25_26:1;       // 13
	uint8_t vdd_26_27:1;       // 14
	uint8_t vdd_27_28:1;       // 15
	uint8_t vdd_28_29:1;       // 16
	uint8_t vdd_29_30:1;       // 17
	uint8_t vdd_30_31:1;       // 18
	uint8_t vdd_31_32:1;       // 19
	uint8_t vdd_32_33:1;       // 20
	uint8_t vdd_33_34:1;       // 21
	uint8_t vdd_34_35:1;       // 22
	uint8_t vdd_35_36:1;       // 23
	uint8_t reserved1:7;       // 24..30
	uint8_t power_up_status:1; // 31
} sd_reg_OCR_t;

//#pragma pack(pop)


extern int8_t sd_ini(void);

extern int16_t sd_read_block(uint32_t addr, uint8_t* data, uint16_t size);

extern int16_t sd_write_block(uint32_t addr, uint8_t* data, uint16_t size);


#if defined(__cplusplus)
}
#endif //defined(__cplusplus)
#endif //_SD_SPI_H
