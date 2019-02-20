/*
 * B_Coding_ADC.c
 *
 * Created: 20-2-2019 10:33:07
 * Author : Dion van der Linden
 */ 

#include <avr/io.h>

// http://www.robotplatform.com/knowledge/ADC/adc_tutorial_2.html
// http://ww1.microchip.com/downloads/en/devicedoc/atmel-8151-8-bit-avr-atmega128a_datasheet.pdf
void adcInit(void)
{	// 7		6		5		4	  3		 2		 1	     0
	// [ADEN]|[ADSC]|[ADFR]|[ADIF]|[ADIE]|[ADPS2]|[ADPS1]|[ADPS0]
	// 7: ADC ENABLE 1/0
	ADCSRA = 0b11100110;
	ADMUX = 0b01100001;
}
int main(void)
{
	DDRF = 0x00; // Input
	DDRA = 0xFF; // Output;
	DDRB = 0xFF; // Output
	
	adcInit();

    while (1) 
    {
		PORTB = ADCL;
    }
	
	return 0;
}

