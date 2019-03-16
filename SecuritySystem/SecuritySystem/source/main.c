/*
 * SecuritySystem.c
 *
 * Created: 13-3-2019 11:03:19
 * Author : Dion van der Linden
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "../header/utils.h"
#include "../header/lcd.h"

#define PULSE_OUT 0
#define PULSE_IN 1
// Pulse out = 0
// Pulse in = 1
void write(int val);

volatile int pulse = 0;
int shittimer_enabled = 0;

// Rising edge -> start timer
ISR(INT0_vect)
{
	shittimer_enabled = 1;
}

// Falling edge -> stop timer
ISR(INT1_vect)
{
	shittimer_enabled = 0;
}

int main(void)
{
	DDRA = 0b00000101;		// A0 = ultrasoon input, A1 = ultrasoon trigger, A2 = IR input
	DDRD = 0b00000000;		// Output voor debuggen op de LEDs
	
	EICRA = 0b00001011;		// INT1 falling edge, INT0 rising edge
	EIMSK = 0b00000011;		// Enable INT1 & INT0
	
	LCD_Init();
	
	sei();
	
	long shittimer = 0;
	
	while(1)
	{
		while(shittimer_enabled)
		{
			shittimer++;
		}
		
		char temp;
		LCD_WriteString(ltoa(shittimer, &temp, 10));
	}
	
	return 0;
}

void write(int toggle)
{
	if (toggle == 1)
		PORTA |= (1<<PULSE_OUT);
	else if (toggle == 0)
		PORTA &= ~(1<<PULSE_OUT);
}
