#define F_CPU 8000000L


#include "lcd.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void setNumber(void);
int i;

ISR( INT1_vect )
{
	setNumber();
	//PORTD |= (1<<2);
}

// Falling edge
ISR( INT2_vect )
{
	setNumber();
	//PORTD |= ~(1<<1);
}
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
	DDRD = 0x00;

// Init Interrupt hardware
EICRA |= 0b00101100;			// INT2 falling edge, INT1 rising edge	0010 1100
EIMSK |= 0x06;			// Mask 0x06 = 0000 0110 aka INT1 & INT2					// Enable INT1 & INT0					0000 0011

// Enable global interrupt system
//SREG = 0x80;			// Of direct via SREG of via wrapper
sei();
	// Write sample string
	// Loop forever
	while (1)
	{
		
	}

	return 1;
}

void setNumber(){
	i++;
	lcd_write_string(i);
}




