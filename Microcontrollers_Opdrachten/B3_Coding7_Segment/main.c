/*
 * B3_Coding7_Segment.c
 *
 * Created: 6-2-2019 14:51:05
 * Author : Dion van der Linden
 */ 

#include "utils.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


void display(int);


int main(void)
{
	// Init I/O
	DDRD = 0xFF;			// output
	DDRC = 0x00;			// input,   PORTD(7:4) output, PORTD(3:0) input	1111 0000
		
	int num = 0;				
	
    while (1) 
    {
		if ((0x01 & PINC) && (0x02 & PINC))
		{
			num = 0;
		}
		else if(0x01 & PINC)
		{
			num++;	
		}		
		else if(0x02 & PINC)
		{
			num--;	
		}
		
		display(num);
		wait(100);
	}
	
	return 0;
}

const int numbers[20] = {
	0b00111111, // 0
	0b00000110, // 1
	0b01011011, // 2
	0b01001111, // 3
	0b01100110, // 4
	0b01101101, // 5
	0b01111101, // 6
	0b00000111, // 7
	0b01111111, // 8
	0b01101111, // 9
	0b01110111, // A
	0b01111100, // B
	0b00111001, // C
	0b01011110, // D
	0b01111001, // E
	0b01110001, // F
};

void display(int num)
{
	if( num < 16 && num >=0 )
		PORTD = numbers[num];
	else
		PORTD = 0b01111011;	
}

