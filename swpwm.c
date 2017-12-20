//swpwm.c

#include "swpwm.h"
#include <avr/io.h>
#include "io_atmega2560.h"


//chnnel 0
#if (SWPWM_CHAN_CNT > 0)
uint8_t swpwm_val0;
uint8_t swpwm_cnt0;
#define SWPWM_CHN0_INI   PIN_OUT(SWPWM_CHN0_PIN); PIN_CLR(SWPWM_CHN0_PIN); swpwm_val0 = 0; swpwm_cnt0 = 0;
#define SWPWM_CHN0_SET   if (swpwm_val0) PIN_SET(SWPWM_CHN0_PIN)
#define SWPWM_CHN0_CLR   if (swpwm_val0 == swpwm_cnt0) PIN_CLR(SWPWM_CHN0_PIN)
#define SWPWM_CHN0_CYC   if (swpwm_cnt0 >= SWPWM_CHN0_MAX) { swpwm_cnt0 = 0; SWPWM_CHN0_SET; } else { SWPWM_CHN0_CLR; swpwm_cnt0++; }
#else //(SWPWM_CHAN_CNT > 0)
#define SWPWM_CHN0_INI
#define SWPWM_CHN0_CYC
#endif //(SWPWM_CHAN_CNT > 0)

//chnnel 1
#if (SWPWM_CHAN_CNT > 1)
uint8_t swpwm_val1;
uint8_t swpwm_cnt1;
#define SWPWM_CHN1_INI   PIN_OUT(SWPWM_CHN1_PIN); PIN_CLR(SWPWM_CHN1_PIN); swpwm_val1 = 0; swpwm_cnt1 = 0;
#define SWPWM_CHN1_SET   if (swpwm_val1) PIN_SET(SWPWM_CHN1_PIN)
#define SWPWM_CHN1_CLR   if (swpwm_val1 == swpwm_cnt1) PIN_CLR(SWPWM_CHN1_PIN)
#define SWPWM_CHN1_CYC   if (swpwm_cnt1 >= SWPWM_CHN1_MAX) { swpwm_cnt1 = 0; SWPWM_CHN1_SET; } else { SWPWM_CHN1_CLR; swpwm_cnt1++; }
#else //(SWPWM_CHAN_CNT > 1)
#define SWPWM_CHN1_INI
#define SWPWM_CHN1_CYC
#endif //(SWPWM_CHAN_CNT > 1)

//chnnel 2
#if (SWPWM_CHAN_CNT > 2)
uint8_t swpwm_val2;
uint8_t swpwm_cnt2;
#define SWPWM_CHN2_INI   PIN_OUT(SWPWM_CHN2_PIN); PIN_CLR(SWPWM_CHN2_PIN); swpwm_val2 = 0; swpwm_cnt2 = 0;
#define SWPWM_CHN2_SET   if (swpwm_val2) PIN_SET(SWPWM_CHN2_PIN)
#define SWPWM_CHN2_CLR   if (swpwm_val2 == swpwm_cnt2) PIN_CLR(SWPWM_CHN2_PIN)
#define SWPWM_CHN2_CYC   if (swpwm_cnt2 >= SWPWM_CHN2_MAX) { swpwm_cnt2 = 0; SWPWM_CHN2_SET; } else { SWPWM_CHN2_CLR; swpwm_cnt2++; }
#else //(SWPWM_CHAN_CNT > 2)
#define SWPWM_CHN2_INI
#define SWPWM_CHN2_CYC
#endif //(SWPWM_CHAN_CNT > 2)

//chnnel 1
#if (SWPWM_CHAN_CNT > 3)
uint8_t swpwm_val3;
uint8_t swpwm_cnt3;
#define SWPWM_CHN3_INI   PIN_OUT(SWPWM_CHN3_PIN); PIN_CLR(SWPWM_CHN3_PIN); swpwm_val3 = 0; swpwm_cnt3 = 0;
#define SWPWM_CHN3_SET   if (swpwm_val3) PIN_SET(SWPWM_CHN3_PIN)
#define SWPWM_CHN3_CLR   if (swpwm_val3 == swpwm_cnt3) PIN_CLR(SWPWM_CHN3_PIN)
#define SWPWM_CHN3_CYC   if (swpwm_cnt3 >= SWPWM_CHN3_MAX) { swpwm_cnt3 = 0; SWPWM_CHN3_SET; } else { SWPWM_CHN3_CLR; swpwm_cnt3++; }
#else //(SWPWM_CHAN_CNT > 3)
#define SWPWM_CHN3_INI
#define SWPWM_CHN3_CYC
#endif //(SWPWM_CHAN_CNT > 3)


void swpwm_ini(void)
{
	SWPWM_CHN0_INI;
	SWPWM_CHN1_INI;
	SWPWM_CHN2_INI;
	SWPWM_CHN3_INI;
}

void swpwm_cyc(void)
{
	SWPWM_CHN0_CYC;
	SWPWM_CHN1_CYC;
	SWPWM_CHN2_CYC;
	SWPWM_CHN3_CYC;
}
