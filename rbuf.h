//rbuf.h
#ifndef _RBUF_H
#define _RBUF_H

#include <inttypes.h>


#define rbuf_l(ptr) (ptr[0])
#define rbuf_w(ptr) (ptr[1])
#define rbuf_r(ptr) (ptr[2])
#define rbuf_empty(ptr) (ptr[1] == ptr[2])


extern void rbuf_ini(uint8_t* ptr, uint8_t len);
extern int rbuf_put(uint8_t* ptr, uint8_t val);
extern int rbuf_get(uint8_t* ptr);


#endif //_RBUF_H