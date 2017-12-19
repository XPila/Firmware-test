//adc.c

#include "adc.h"
#include <avr/io.h>


uint8_t adc_state;
uint8_t adc_count;
uint16_t adc_values[ADC_CHAN_CNT];


#ifdef ADC_CALLBACK
	extern void ADC_CALLBACK(void);
#endif //ADC_CALLBACK


void adc_init(void)
{
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	ADMUX |= (1 << REFS0);
	ADCSRA |= (1 << ADEN);
	adc_reset();
}

void adc_reset(void)
{
	adc_state = 0;
	adc_count = 0;
	for (uint8_t i = 0; i < ADC_CHAN_CNT; i++)
		adc_values[i] = 0;
}

void adc_setmux(uint8_t ch)
{
	ch &= 0x0f;
	if (ch & 0x08) ADCSRB |= (1 << MUX5);
	else ADCSRB &= ~(1 << MUX5);
	ADMUX = (ADMUX & ~(0x07)) | (ch & 0x07);
}

uint8_t adc_chan(uint8_t index)
{
	uint8_t chan = 0;
	uint16_t mask = 1;
	while (mask)
	{
		if ((mask & ADC_CHAN_MSK) && (index-- == 0)) break;
		mask <<= 1;
		chan++;
	}
	return chan;
}

void adc_cycle(void)
{
	if (adc_state & 0x80)
	{
		uint8_t index = adc_state & 0x0f;
		adc_values[index++] += ADC;
		if (index >= ADC_CHAN_CNT)
		{
			index = 0;
			adc_count++;
			if (adc_count >= ADC_OVRSAMPL)
			{
#ifdef ADC_CALLBACK
				ADC_CALLBACK();
#endif //ADC_CALLBACK
				adc_reset();
			}
		}
		adc_setmux(adc_chan(index));
		adc_state = index;
	}
	else
	{
		ADCSRA |= (1 << ADSC); //start conversion
		adc_state |= 0x80;
	}
}
