//swpwm.h
#ifndef _SWPWM_H
#define _SWPWM_H

#include <inttypes.h>
#include "config.h"


#if defined(__cplusplus)
extern "C" {
#endif //defined(__cplusplus)


//chnnel 0
#if (SWPWM_CHAN_CNT > 0)
extern uint8_t swpwm_val0;
extern uint8_t swpwm_cnt0;
#endif //(SWPWM_CHAN_CNT > 0)

//chnnel 1
#if (SWPWM_CHAN_CNT > 1)
extern uint8_t swpwm_val1;
extern uint8_t swpwm_cnt1;
#endif //(SWPWM_CHAN_CNT > 1)

//chnnel 2
#if (SWPWM_CHAN_CNT > 2)
extern uint8_t swpwm_val2;
extern uint8_t swpwm_cnt2;
#endif //(SWPWM_CHAN_CNT > 2)

//chnnel 3
#if (SWPWM_CHAN_CNT > 3)
extern uint8_t swpwm_val3;
extern uint8_t swpwm_cnt3;
#endif //(SWPWM_CHAN_CNT > 3)


extern void swpwm_ini(void);
extern void swpwm_cyc(void);


#if defined(__cplusplus)
}
#endif //defined(__cplusplus)
#endif //_SWPWM_H
