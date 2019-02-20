/*
 * B3_LM35.c
 *
 * Created: 20-2-2019 12:49:56
 * Author : Yannick
 */ 

#include "utils.h"
#include <avr/io.h>
#include <stdlib.h>

#include "lcd.h"


// http://www.robotplatform.com/knowledge/ADC/adc_tutorial_2.html
// http://ww1.microchip.com/downloads/en/devicedoc/atmel-8151-8-bit-avr-atmega128a_datasheet.pdf
void adcInit(void)
{	
	ADMUX = 0b11100001;
	// 7		6		5		4	  3		 2		 1	     0
	// [ADEN]|[ADSC]|[ADFR]|[ADIF]|[ADIE]|[ADPS2]|[ADPS1]|[ADPS0]
	// 7: ADC ENABLE 1/0
	// 6: Start conversion
	// 5: Free running select
	// 4: Interrupt flag
	// 3: Interrupt Enable
	// 2~0: Prescaler select
	ADCSRA = 0b10000110;
}
int main(void)
{
	DDRF = 0x00; // Input
	DDRA = 0xFF; // Output;
	//DDRB = 0xFF; // Output
	
	adcInit();
	lcd_init();
	while (1)
	{
		//PORTB = ADCL;
		
		lcd_clear_display();
		lcd_set_cursor_pos(0);
		ADCSRA |= (1 << 6);
		
		while (ADCSRA & (1 << 6));
		
		const int val = ADCH; //(ADCH << 1);
		char str[8];
		itoa(val, str, 8);

		lcd_write_string(str);
		
		PORTA = val;
		wait(500);
	}
	
	return 0;
}
