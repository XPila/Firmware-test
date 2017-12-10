//localize.c - Text localization

#include "localize.h"

//static const char str1[] PROGMEM = "ahoj svete!";
//static const char str2[] PROGMEM = "vyser si voko!";

//static const char* PROGMEM _table_n[] PROGMEM = {(const char*)0x10000, (const char*)0x1000a, (const char*)0x10017, (const char*)0};
//static const char* PROGMEM _table_i[] PROGMEM = {str2, str1, 0, 0};


const char* _localize(const char* s)
{
/*	for (int i = 0; i < 4; i++)
		if (s == _table_n[i])
			return (const char*)_table_i[i];
*/
//	return str1;
	return s;
}
