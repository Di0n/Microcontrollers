/*
 * Microcontrollers_Opdrachten.c
 *
 * Created: 30-1-2019 11:02:15
 * Author : Dion van der Linden
 */ 

#include <avr/io.h>
#include "utils.h"

void b2();
void b4();
int main(void)
{
    DDRD = 0b11111111;			// All pins PORTD are set to output 
	
    while (1) 
    {
		b2();
    }
	
	return 0;
}

void b2()
{
	PORTD = 0b10000000;
	wait(500);
	PORTD = 0b01000000;	
	wait(500);
}

//int value = 0x01;
//int direction = 1;
void b4()
{
	static int direction = 1;
	static int value = 0x01;
	value = (direction == 1) ? value << 1 : value >> 1;

	PORTD = value;
	if (value == 0x80)
	{
		direction = 0;
	}
	else if (value == 0x01)
	{
		direction = 1;	
	}
	wait(500);
}
