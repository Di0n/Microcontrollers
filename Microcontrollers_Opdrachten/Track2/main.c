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

ISR( INT1_vect )

{
	PORTD |= (1<<5);
}


ISR( INT2_vect )
{
	PORTD &= ~(1<<5);
}

int main(void)
{
    /* Replace with your application code */
    b2();
	return 0;
}

void b2()
{
	while (1)
	{
	}
}

