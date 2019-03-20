
/*
 * SecuritySystem.c
 *
 * Created: 13-3-2019 11:03:19
 * Author : Dion van der Linden
 */ 

#include "../header/globals.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../header/utils.h"
#include "../header/lcd.h"
#include "../header/ultrasonic.h"
#include <util/delay.h>


void fastPrint(const char* str)
{
	LCD_ClearDisplay();
	LCD_SetCursorPos(0x00);
	LCD_WriteString(str);	
}

/*
	399999
	Timer resolution = 1 / F_CPU (8000000 = 8MHZ)
	Target frequency = 1/20
	Timer clock frequency = 1/1000000 -1 (8m op deze cpu)
	Timer resolution = 1 / input frequency (bijv 100hz) = .01s

	Draaiend op 8mhz moet de timer tot 399999 tellen om 1/20 van een seconde te bereiken.
*/

// Change in logic level
ISR(INT4_vect)
{
	US_InterruptUpdate();
}

ISR(TIMER1_OVF_vect)
{
	//timerOverflow++;
}

int Init(void)
{
	LCD_Init();
	
	DDRE = 0b01000000;
	
	EICRB |= 0b00000001;
	EIMSK |= 0b00010000;
	TIMSK = (1 << TOIE1);
	//TCCR1B |= ((1 << CS10));
	sei();
	
	return 0;
}

int main(void)
{
	Init();
    while (1) 
    {		
		US_SendPulse();
		int16_t dist = 0;
		dist = US_GetDistance();
		
		char str[10];

		itoa(count, str, 10);
		
		fastPrint(str);
		
		Utils_Wait(100);
    }

	return 0;
}
