
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
#include "../header/utils.h"
#include "../header/lcd.h"

#define PULSE_OUT 0
#define PULSE_IN 1
// Pulse out = 0
// Pulse in = 1
void write(int val);


/*399999
	Timer resolution = 1 / F_CPU (8000000 = 8MHZ)
	Target frequency = 1/20
	Timer clock frequency = 1/1000000 -1 (8m op deze cpu)
	Timer resolution = 1 / input frequency (bijv 100hz) = .01s
*/
int main(void)
{
	// 0 = input 1 = output
	//DDRA = 0b00000101;//0x65; // 0b00000101
    /* Replace with your application code */
	
	//EICRA |= 0b00000011;
	//EIMSK |= 0b00000001;
	
	//sei();
	DDRB = 0b11111111;		// PORT B output
	TCCR1B |= (1 << CS10);	// geef de timer een klok (fcpu) 
	
	//LCD_Init();
	
	int times = 0;
    while (1) 
    {
		if (TCNT1 >= 49999)
		{
			//LCD_ClearDisplay();
			//LCD_SetCursorPos(0x00);
			//char str[25] = "Reached";
			//itoa(times, str, 25);
			//LCD_WriteString("Reached");
			PORTB ^= (1 << 0);
			TCNT1 = 0;
		}
		//Utils_Wait(100);
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
