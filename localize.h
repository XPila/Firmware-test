//localize.h - Text localization
#ifndef _LOCALIZE_H
#define _LOCALIZE_H


#define _n(s) (__extension__({static const char __c[] __attribute__((section(".progmem.data"))) = s; &__c[0];})) 
#define _i(s) _localize(__extension__({static const char __c[] __attribute__((section(".progmem.data"))) = s; &__c[0];})) 


#if defined(__cplusplus)
extern "C" {
#endif //defined(__cplusplus)

extern const char* _localize(const char* s);

#if defined(__cplusplus)
}
#endif //defined(__cplusplus)
#endif //_LOCALIZE_H
