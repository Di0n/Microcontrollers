#define F_CPU 8000000L

#include "lcd.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

/******************************************************************/
int main( void )
/*
short:			main() loop, entry point of executable
inputs:
outputs:
notes:			Slow background task after init ISR
Version :    	DMK, Initial code
*******************************************************************/
{
	// Init I/O
	DDRD &= ~BIT(7); // set PORTD.7 for input	timer2Init();
	// Init LCD
	init_4bits_mode();

	// Write sample string
	// Loop forever
	while (1)
	{
		setNumber(tenthValue);
		_delay_ms( 10 );
	}

	return 1;
}

void setNumber(int i){
	lcd_write_string("%a", i);
}

ISR( TIMER2_OVF_vect )
{
	tenthValue++;			// Increment counter
}

// Initialize timer2
//
void timer2Init( void )
{
	OCR2 = CompareValue;		// Compare value of counter 2
	TIMSK |= BIT(7);			// T2 compare match interrupt enable
	SREG |= BIT(7);			// turn_on intr all
	TCCR2 = 0b00011111;		// Initialize T2: ext.counting, rising edge
	// 	compare output mode, CTC, RUN
}
