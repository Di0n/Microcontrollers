/*
 * B2.c
 *
 * Created: 20-2-2019 11:42:17
 * Author : Dion van der Linden
 */ 




#include <avr/io.h>

#include "utils.h"
#include "lcd.h"

// http://www.robotplatform.com/knowledge/ADC/adc_tutorial_2.html
// http://ww1.microchip.com/downloads/en/devicedoc/atmel-8151-8-bit-avr-atmega128a_datasheet.pdf
void adcInit(void)
{	// 7		6		5		4	  3		 2		 1	     0
	// [ADEN]|[ADSC]|[ADFR]|[ADIF]|[ADIE]|[ADPS2]|[ADPS1]|[ADPS0]
	// 7: ADC ENABLE 1/0
	// 6: Start conversion
	// 5: Free running select
	// 4: Interrupt flag
	// 3: Interrupt Enable
	// 2~0: Prescaler select
	ADCSRA = 0b10000110;
	ADMUX = 0b01100001;
}
int main(void)
{
	DDRF = 0x00; // Input
	DDRA = 0xFF; // Output;
	DDRB = 0xFF; // Output
	
	adcInit();
	lcd_init();
	
	lcd_write_string("Starting program");
	wait(5000);
	

	while (1)
	{
		ADCSRA |= (1 << 6);
		

		// Write sample string
		lcd_clear_display();
		//wait(1);
		lcd_set_cursor_pos(0);
		//wait(1);
		lcd_write_string("Starting conversion");
		wait(1000);
		while (ADCSRA & (1 << 6)) ;
		lcd_clear_display();
		//wait(1);
		lcd_set_cursor_pos(0);
		//wait(1);
		lcd_write_string("Done converting");
		//wait(1);
		PORTB = ADCL;
		PORTA = ADCH;
		wait(500);
	}
	
	return 0;
}

