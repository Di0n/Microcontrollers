/*
 * Track2.c
 *
 * Created: 6-2-2019 12:58:27
 * Author : Dion van der Linden
 */ 
#include "utils.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void b2();
void setDirection();

// Rising edge
ISR( INT1_vect )
{
	setDirection();
	//PORTD |= (1<<2);
}

// Falling edge
ISR( INT2_vect )
{
	setDirection();
	//PORTD |= ~(1<<1);
}

int main(void)
{
    /* Replace with your application code */
    b2();
	
	return 0;
}

void b2()
{
	// Init I/O
	DDRA = 0xFF;			// output 1111 1111 
	DDRD = 0x00;			// input,   PORTD(7:4) output, PORTD(3:0) input	0000 0000
	
	
	// Init Interrupt hardware
	EICRA |= 0b00101100;			// INT2 falling edge, INT1 rising edge	0010 1100
	EIMSK |= 0x06;			// Mask 0x06 = 0000 0110 aka INT1 & INT2					// Enable INT1 & INT0					0000 0011
	
	// Enable global interrupt system
	//SREG = 0x80;			// Of direct via SREG of via wrapper
	sei();
	
	while (1)
	{
		wait(1);
	}
}

void setDirection()
{
	static int direction = 1;							// Richting van loop 1 = links, 0 is rechts
	static int value = 0x01;							// 0b00010001
	value = (direction == 1) ? value << 1 : value >> 1;	// Richting bepaald

	PORTA = value;										// Zet portd op waarde
	if (value == 0x80)									// Verander van richting als waarde op uiterste links zit
	direction = 0;
	else if (value == 0x01)								// Verander van richting als waarde op uiterste rechts zit
	direction = 1;
}

