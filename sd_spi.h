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

//#pragma pack(pop)


extern int8_t sd_init(void);

extern int16_t sd_read_block(uint32_t addr, uint8_t* data, uint16_t size);

extern int16_t sd_write_block(uint32_t addr, uint8_t* data, uint16_t size);

extern sd_response_t sd_cmd_00(uint32_t arg);



#if defined(__cplusplus)
}
#endif //defined(__cplusplus)
#endif //_SD_SPI_H
