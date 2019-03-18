
/*
 * SecuritySystem.c
 *
 * Created: 13-3-2019 11:03:19
 * Author : Dion van der Linden
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../header/utils.h"
#include "../header/lcd.h"

#define PULSE_OUT 0
#define PULSE_IN 1
#define MS 8
//#define SECOND 50000
// Pulse out = 0
// Pulse in = 1
void write(int val);



volatile int count = 0;


void fastPrint(const char* str)
{
	LCD_ClearDisplay();
	LCD_SetCursorPos(0x00);
	LCD_WriteString(str);	
}
ISR( TIMER1_OVF_vect )
{
	count++;
}
/*
	399999
	Timer resolution = 1 / F_CPU (8000000 = 8MHZ)
	Target frequency = 1/20
	Timer clock frequency = 1/1000000 -1 (8m op deze cpu)
	Timer resolution = 1 / input frequency (bijv 100hz) = .01s

	Draaiend op 8mhz moet de timer tot 399999 tellen om 1/20 van een seconde te bereiken.
*/

int main(void)
{
	LCD_Init();
	LCD_ClearDisplay();
	
	DDRA = 0x01;
	PORTD = 0xFF;
	
	TCCR3B = ((1 << CS10) | (1 << CS11));
	TCNT3 = 0;
	
	sei();
	//int count = 0;
	int seconds = 0;
	int ms = 0;
    while (1) 
    {
		//if (TCNT1 >= 31248)
		//{
			////LCD_ClearDisplay();
			////LCD_SetCursorPos(0x00);
			////char str[25] = "Reached";
			////itoa(times, str, 25);
			////LCD_WriteString("Reached");
			//PORTB ^= (1 << 0);
			//TCNT1 = 0;
		//}
		
		
		PORTA |= (1 << PA0);
		Utils_Wait(15);
		PORTA &= (~(1 << PA0));
		
		if (TCNT3 >= MS)
		{
			ms++;
			if (ms >= 50)
			{
				seconds++;
				ms = 0;	
				
				char str[10];
				itoa(seconds, str, 10);
				fastPrint(str);
			}			
	
			TCNT3 = 0;
		}
		//
		//TCNT1 = 0;
		//TCCR1B = 0x41;
		//TIFR = 1 << ICF1;
		//TIFR = 1 << TOV1;
		//
		//sei();
		//fastPrint("1");
		//while ((TIFR & (1 << ICF1)) == 0);
		//fastPrint("2");
		//TCNT1 = 0;
		//TCCR1B = 0x01;
		//TIFR = 1 << ICF1;
		//TIFR = 1 << TOV1;
		//sei();
		//count = 0;
		//
		//while ((TIFR & (1 << ICF1)) == 0);
		//
		//fastPrint("3");
		//
		//long dataCount = ICR1 + (65535 * count);
		//
		//double distance = (double) dataCount / 466.47;
		//
		//char string[10];
		//dtostrf(distance, 2, 2, string);
		//strcat(string, "cm ");
		//LCD_ClearDisplay();
		//LCD_SetCursorPos(0x00);
		//LCD_WriteString("Dist = ");
		//LCD_WriteString(string);
		
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
