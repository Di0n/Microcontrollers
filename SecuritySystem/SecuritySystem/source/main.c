
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
#include "../header/buzzer.h"
#include <util/delay.h>

uint8_t alarm_trig;
uint16_t prev_dist;

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

// Doe iets
ISR(INT0_vect)
{
	alarm_trig = 0;
}

ISR(TIMER3_OVF_vect)
{
	//timerOverflow++;
}

int Init(void)
{
	LCD_Init();
	
	DDRB = 0b11111111;
	DDRE = 0b01000000;
	
	EICRA |= 0b00000100;
	EICRB |= 0b00000001;
	EIMSK |= 0b00010010;
	ETIMSK = (1 << TOIE3);
	sei();
	
	return 0;
}

int main(void)
{
	Init();
	
	int counter = 0;
	alarm_trig = 0;
	prev_dist = 0;
	
    while (1) 
    {		
		US_SendPulse();
		int16_t dist = 0;
		dist = US_GetDistance();
		
		char str[10];

		itoa(alarm_trig, str, 10);
		
		// Start the buzzer if movement is detected
		if(prev_dist != dist && counter > 20) /* Giving a 2 sec delay for startup */
			alarm_trig = 1;//buzzer_Start();
		
		if(alarm_trig == 0) // Stopping the buzzer
			buzzer_Stop();
		
		if(alarm_trig)
			buzzer_Start();
		else
			buzzer_Stop();
		
		fastPrint(str);
		
		prev_dist = dist;
		counter++;
		Utils_Wait(100);
    }

	return 0;
}
