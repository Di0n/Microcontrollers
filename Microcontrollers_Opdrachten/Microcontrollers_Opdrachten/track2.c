/*
 * track2.c
 *
 * Created: 6-2-2019 10:48:19
 *  Author: Dion van der Linden
 */ 
#include "track2.h"
#include "utils.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

ISR( INT1_vect )
/*
short:			ISR INT0
inputs:
outputs:
notes:			Set PORTD.5
Version :    	DMK, Initial code
*******************************************************************/
{
	PORTD |= (1<<5);
}

/******************************************************************/
ISR( INT2_vect )
/*
short:			ISR INT1
inputs:
outputs:
notes:			Clear PORTD.5
Version :    	DMK, Initial code
*******************************************************************/
{
	PORTD &= ~(1<<5);
}
void t2b2()
{
	// Init I/O
	DDRA = 0xFF;			// output
	DDRD = 0xF0;			// input,   PORTD(7:4) output, PORTD(3:0) input	1111 0000
	
	
	// Init Interrupt hardware
	EICRA |= 0x0B;			// INT1 falling edge, INT0 rising edge	0000 1011
	EIMSK |= 0x06;			// Mask 0x06 = 0000 0110 aka INT1 & INT2					// Enable INT1 & INT0					0000 0011
	
	// 0x05 =	0001 0100
	// 0x14
	// Enable global interrupt system
	//SREG = 0x80;			// Of direct via SREG of via wrapper
	sei();

	while (1)
	{
		PORTD ^= (1<<7);	// Toggle PORTD.7
		wait(1);
	}
}
// Main
void run_track2()
{
	
}