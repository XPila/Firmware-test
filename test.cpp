//test.cpp
#include "main.h"
#include "rnd.h"

//class definitions here


//setup and loop (called from main.c)
extern "C"
{

void delay_50us(uint16_t us50)
{
	while (us50--)
		for (uint8_t i = 0; i < 200; i++)
		{ asm ("nop"); }
}
//#define PROG_MEM __attribute__(section(".progmem")) 
//#define _n(str) ((progmem const char*)str)
//#define _n(s) (__extension__({static char __c[] PROGMEM = (s); &__c[0];}))
//#define _n(s) (__extension__({static prog_char __c[] = (s); &__c[0];})) 

//static const char __attribute__((section(SECTION_TXT_N))) ___c1[] = "MAMLAS";
//static const char __attribute__((section(SECTION_TXT_N))) ___c0[] = "KRETEN";

//#define _n(s) PSTR(s)


//#define __n(s) (__extension__({static const char __c[] __attribute__((section(SECTION_TXT_N))) = "  "s; &__c[0];})) 


static const char __loc_data[] __attribute__((section("loc_data"))) = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};

uint16_t vals[ADC_CHAN_CNT];
uint8_t led_intensity;

void adc_ready(void)
{
	for (uint8_t i = 0; i < ADC_CHAN_CNT; i++)
		vals[i] = adc_val[i];
}

//#define IS_BIG_ENDIAN (*(uint16_t *)"\0\xff" < 0x100)
/*
#if (IS_BIG_ENDIAN == 1)
#define BIG_ENDIAN
#else //IS_BIG_ENDIAN
#define LITLE_ENDIAN
#endif //IS_BIG_ENDIAN
*/

//DUMP internal flash memory
void _dump_iflash_data(uint32_t address, uint16_t size)
{
	while (size)
	{
		fprintf_P(uart0io, PSTR("%04x "), address);
		for (uint8_t i = 0; (i < 16) && size-- ; i++)
		{
			fprintf_P(uart0io, PSTR("%02x "), pgm_read_byte((uint8_t*)(address+i)));
		}
		fputc('\n', uart0io);
		address += 16;
	}
}

void _dump_xflash_uid()
{
	fputs_P(PSTR("UID="), uart0io);
	for (uint8_t i = 0; i < 8; i++)
		fprintf_P(uart0io, PSTR("%02x"), w25x20cl_uid[i]);
	fputc('\n', uart0io);
}

//DUMP external flash memory
void _dump_xflash_data(uint32_t address, uint16_t size)
{
	uint8_t data[16];
	while (size)
	{
		w25x20cl_rd_data(address, data, (size >= 16)?16:size);
		fprintf_P(uart0io, PSTR("%04x "), address);
		for (uint8_t i = 0; (i < 16) && size-- ; i++)
			fprintf_P(uart0io, PSTR("%02x "), data[i]);
		fputc('\n', uart0io);
		address += 16;
	}
}

void _copy_iflash_to_xflash(uint32_t src_address, uint32_t dst_address, uint32_t size)
{
	uint16_t size_0 = (0x100 - (src_address & 0xff)) & 0xff; //size of block 0
	uint16_t pages = (size - size_0) >> 8; //number of full pages
	uint16_t size_n = size - size_0 - (pages << 8); //size of last block
	fprintf_P(uart0io, PSTR("size=%u\n"), size);
	fprintf_P(uart0io, PSTR("size_0=%d\n"), size_0);
	fprintf_P(uart0io, PSTR("pages=%d\n"), pages);
	fprintf_P(uart0io, PSTR("size_n=%d\n"), size_n);
//	return;
	if (size_0)
	{
		w25x20cl_enable_wr();
		fprintf_P(uart0io, PSTR("writing block 0, size=%d\n"), size_0);
		w25x20cl_page_program_P(dst_address, (uint8_t*)src_address, size_0); //copy block 0
		src_address += size_0;
		dst_address += size_0;
		while (w25x20cl_rd_status_reg() & W25_STATUS_BUSY);
		w25x20cl_disable_wr();
	}
	while (pages--)
	{
		w25x20cl_enable_wr();
		fprintf_P(uart0io, PSTR("writing block n, (%d) size=%d\n"), pages, 256);
		w25x20cl_page_program_P(dst_address, (uint8_t*)src_address, 256); //copy block 1..n-1
		src_address += 0x100;
		dst_address += 0x100;
		while (w25x20cl_rd_status_reg() & W25_STATUS_BUSY);
		w25x20cl_disable_wr();
	}
	if (size_n)
	{
		w25x20cl_enable_wr();
		fprintf_P(uart0io, PSTR("writing last block, size=%d\n"), size_n);
		w25x20cl_page_program_P(dst_address, (uint8_t*)src_address, size_n); //copy last block
		//src_address += size_n;
		//dst_address += size_n;
		while (w25x20cl_rd_status_reg() & W25_STATUS_BUSY);
		w25x20cl_disable_wr();
	}
}

//lang_table_header_t structure - (size= 16byte)
typedef struct
{
	uint32_t magic;      //+0 
	uint16_t size;       //+4
	uint16_t count;      //+6
	uint16_t checksum;   //+8
	uint16_t code;       //+10
	uint32_t reserved1;  //+12
} lang_table_header_t;

// Magic number at begin of lang table.
#define LANG_MAGIC 0x4bb45aa5

uint32_t lang_xflash_enum(uint32_t addr, lang_table_header_t* header)
{
	return 0;
}

void setup(void)
{
	fputs_P(PSTR("start\n"), uart0io);

	fputs_P(PSTR("start"), lcdio);

	_dump_xflash_uid();

	fputs_P(PSTR("internal flash:\n"), uart0io);
	_dump_iflash_data((uint32_t)(&__loc_data), 0x200);

	fputs_P(PSTR("external flash:\n"), uart0io);
	_dump_xflash_data(0x00000, 0x200);

	uint16_t size_total = 0;
	uint16_t ptr = (uint32_t)(&__loc_data);
	while (pgm_read_dword((uint32_t*)ptr) == LANG_MAGIC)
	{
		uint16_t lt_size = pgm_read_word((uint16_t*)(ptr + 4));
		uint16_t lt_count = pgm_read_word((uint16_t*)(ptr + 6));
		uint16_t lt_chsum = pgm_read_word((uint16_t*)(ptr + 8));
		uint16_t lt_code = pgm_read_word((uint16_t*)(ptr + 10));
		fprintf_P(uart0io, PSTR(" lt_size=%d (0x%04x)\n"), lt_size, lt_size);
		fprintf_P(uart0io, PSTR(" lt_count=%d\n"), lt_count);
		fprintf_P(uart0io, PSTR(" lt_chsum=%d\n"), lt_chsum);
		fprintf_P(uart0io, PSTR(" lt_code=0x%04x (%c%c)\n"), lt_code, lt_code >> 8, lt_code & 0xff);
		size_total += lt_size;
		ptr += lt_size;
	}
	fprintf_P(uart0io, PSTR("size_total=%u  (0x%04x)\n"), size_total, size_total);

	fputs_P(PSTR("xflash chip erase...\n"), uart0io);
	w25x20cl_enable_wr();
	w25x20cl_chip_erase();
	while (w25x20cl_rd_status_reg() & W25_STATUS_BUSY);
	w25x20cl_disable_wr();

	fputs_P(PSTR("copying iflash to xflash...\n"), uart0io);
	_copy_iflash_to_xflash((uint32_t)(&__loc_data), 0x00000, size_total);
//	_copy_iflash_to_xflash((uint32_t)(&__loc_data), 0x00000, 0x200);

/*
	uint8_t data[256];
	for (uint8_t i = 0; i < 10; i++) data[i] = 0x80;
	w25x20cl_enable_wr();
	w25x20cl_page_program(0x000100, data, 10);
	while (w25x20cl_rd_status_reg() & W25_STATUS_BUSY);
	w25x20cl_disable_wr();
	*/

	fputs_P(PSTR("external flash:\n"), uart0io);
	_dump_xflash_data(0x00000, 3*16384);

/*

	uint8_t data[256];
	for (uint8_t i = 0; i < 10; i++) data[i] = 0x80;
	w25x20cl_enable_wr();
	w25x20cl_page_program(0x000000, data, 10);
	while (w25x20cl_rd_status_reg() & W25_STATUS_BUSY);
	w25x20cl_disable_wr();

	fputs_P(PSTR("external flash:\n"), uart0io);
	_dump_xflash_data(0x00000, 0x100);





/*
	uint8_t data[256];
	uint32_t address;
	uint16_t size;
*/





//	const char* pc = __n("XXXTESTXXX");
/*
	fprintf_P(uart0io, PSTR("test1 %S\n"), _i("CAT"));
	fprintf_P(uart0io, PSTR("test2 %S\n"), _i("DOG"));
	fprintf_P(uart0io, PSTR("test3 %S\n"), _i("COW"));
	fprintf_P(uart0io, PSTR("test4 %S\n"), _i("FROG"));
	fprintf_P(uart0io, PSTR("test5 %S\n"), _i("MOUSE"));
	fprintf_P(uart0io, PSTR("test6 %S\n"), _i("I will start to print line and you will gradually lower the nozzle by rotating the knob, until you reach optimal height. Check the pictures in our handbook in chapter Calibration."));
*/

/*
	uint32_t val = 0x01020304;
#define pval ((uint8_t*)&val)
#ifdef _BIGENDIAN
	fprintf_P(lcdio, PSTR(ESC_H(0,0)"Big endian"ESC_H(0,1)"0x%02x%02x%02x%02x"), pval[0], pval[1], pval[2], pval[3]);
#else //_BIGENDIAN
	fprintf_P(lcdio, PSTR(ESC_H(0,0)"Litle endian"ESC_H(0,1)"0x%02x%02x%02x%02x"), pval[3], pval[2], pval[1], pval[0]);
#endif //_BIGENDIAN
	while (1);
*/

/*
	srand(100);
	int i = 0;
	while (1)
	{
		uint32_t time_us1 = timer0_us();
		int r = rand();
		uint32_t time_us2 = timer0_us();

		fprintf_P(uart0io, PSTR("rnd: %d %d %ld\n"), i, r, time_us2 - time_us1);
		i++;
	}
*/

/*
	for (uint8_t i = 0; i < ADC_CHAN_CNT; i++)
	{
		if ((i & 3) == 0)
			fprintf_P(lcdio, PSTR(ESC_H(0,%d)), (i >> 2));
		fprintf_P(lcdio, PSTR("%4d "), adc_chan(i));
	}
	while (1);*/

//	uint8_t ch = 0;
/*	while (1)
	{
		for (uint8_t i = 0; i < ADC_CHAN_CNT; i++)
		{
			if ((i & 3) == 0)
				fprintf_P(lcdio, PSTR(ESC_H(0,%d)), (i >> 2));
			fprintf_P(lcdio, PSTR("%4d "), vals[i] >> 4);
		}
	led_intensity++;
	if (led_intensity < 128) swpwm_val0 = led_intensity;
	else swpwm_val0 = 255 - led_intensity;
	uint8_t led_int1 = 2 * led_intensity;
	if (led_int1 < 128) swpwm_val1 = led_int1;
	else swpwm_val1 = 255 - led_int1;
	led_int1 = 4 * led_intensity;
	if (led_int1 < 128) swpwm_val2 = led_int1;
	else swpwm_val2 = 255 - led_int1;

//		adc_setmux(ch);
//		ADCSRA |= (1 << ADSC); //start conversion
//		adc_cycle();
//		swpwm_cycle();
//		swdelay_n40us(25);
//		swdelay_n40us(100);
//		if ((ch & 3) == 0)
//			fprintf_P(lcdio, PSTR(ESC_H(0,%d)), (ch >> 2));
//		fprintf_P(lcdio, PSTR("%4d "), ADC);

//		ch++;
//		ch &= 0x0f;
	}
*/
//	fprintf_P(lcdio, PSTR(ESC_2J"setup %S%S"), PSTR("xxx"), PSTR("yyy"));
//	fprintf_P(lcdio, PSTR(ESC_2J"mfr=%02x dev=%02x       uid=%02x%02x%02x%02x%02x%02x%02x%02x"), w25x20cl_mfrid, w25x20cl_devid, w25x20cl_uid[0], w25x20cl_uid[1], w25x20cl_uid[2], w25x20cl_uid[3], w25x20cl_uid[4], w25x20cl_uid[5], w25x20cl_uid[6], w25x20cl_uid[7]);
//	fprintf_P(lcdio, PSTR(ESC_2J"uid=%02x%02x%02x%02x%02x%02x%02x%02x"), w25x20cl_uid[0], w25x20cl_uid[1], w25x20cl_uid[2], w25x20cl_uid[3], w25x20cl_uid[4], w25x20cl_uid[5], w25x20cl_uid[6], w25x20cl_uid[7]);
//	fprintf_P(lcdio, _n(ESC_2J"uid=%02x%02x%02x%02x%02x%02x%02x%02x                   "), w25x20cl_uid[0], w25x20cl_uid[1], w25x20cl_uid[2], w25x20cl_uid[3], w25x20cl_uid[4], w25x20cl_uid[5], w25x20cl_uid[6], w25x20cl_uid[7]);
//	fputs_P(_n(ESC_2J), lcdio);
//	fputs_P(_i("hello world!"), lcdio);
//	fputs_P(_i("fuck you!"), lcdio);

//	uint8_t data[10];
//	for (uint8_t i = 0; i < 10; i++)
//		data[i] = i;

//	w25x20cl_enable_wr();

//	w25x20cl_page_program(0x000000, data, 10);

//	while (w25x20cl_rd_status_reg() & W25_STATUS_BUSY);

//	w25x20cl_disable_wr();

/*	for (uint8_t i = 0; i < 10; i++)
		data[i] = 0x00;

	w25x20cl_rd_data(0x000000, data, 10);
	for (uint8_t i = 0; i < 10; i++)
		fprintf_P(lcdio, PSTR("%02x"), data[i]);


	fprintf_P(lcdio, PSTR(ESC_H(0,1)"%02x %02x"), pat9125_PID1, pat9125_PID2);

	while(1)
	{
		uint32_t time_us1 = timer0_us();
		pat9125_update();
		uint32_t time_us2 = timer0_us();

		fprintf_P(lcdio, PSTR(ESC_H(0,3)"%3d %4d %4d %3d %2d"), time_us2 - time_us1, pat9125_x, pat9125_y, pat9125_b, pat9125_s);
		swdelay_n40us(100);
	}
*/
///	fprintf_P(lcdio, PSTR(ESC_2J"setup"));
//	delay_50us(20000);

//	uint32_t time = 0;
//	while (1)
	{
//		for (int c = 0; c = 10; c++)
//			delay_50us(5000); //
//		led_neg();
/*

		//get start time
		uint32_t time_us = timer0_us();

		//print long string to serial and meassure time
		fprintf_P(uart0io, PSTR("abcdefghijklmnopqrstuvwxyz cycle %ld\n"), timer0_ms);

		//get end time
		uint32_t time_us1 = timer0_us();

		int kbd = lcd_get();

		//calc delay
		uint32_t time = time_us1 - time_us;

*/

//		lcd_put('a');
		//print delay to LCD
		//lcd_cmd(LCD_CMD_SETDDRAMADDR, 1);
		//delay_50us(50);

		//get start time
//		uint32_t time_us = timer0_us();

//		fprintf_P(lcdio, PSTR(ESC_2J"abcdefghijklmnopqrst"ESC_H(0,1)"delay %ld us    "), time);

		//get end time
//		uint32_t time_us1 = timer0_us();
//		time = time_us1 - time_us;

//		lcd_cmd(LCD_CMD_SETDDRAMADDR+20);
		//fprintf_P(lcdio, PSTR("kbd %d"), kbd);
//		int uart_tx = rbuf_cnt(uart0_obuf);
//		fprintf_P(lcdio, PSTR("uart0 tx %d   "), uart_tx);
	}
}

void loop(void)
{
//	fputs_P(PSTR("loop\n"), uart0io);
//	puts_P(___c1);
//	puts_P(___c0);
//	delay_50us(2000000);
//	while (1);
}

} //extern "C"
