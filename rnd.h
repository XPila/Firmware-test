//rnd.h
#ifndef _RND_H
#define _RND_H

#include <inttypes.h>


#if defined(__cplusplus)
extern "C" {
#endif //defined(__cplusplus)


extern void srand(uint32_t x);
extern int32_t rand(void);


#if defined(__cplusplus)
}
#endif //defined(__cplusplus)
#endif //_RND_H