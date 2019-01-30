/*
 * Microcontrollers_Opdrachten.c
 *
 * Created: 30-1-2019 11:02:15
 * Author : Dion van der Linden
 */ 

#include <avr/io.h>
#include "utils.h"
#include "globals.h"
void b2();
void b4();
void b6();

// Main entry point.
int main(void)
{
    DDRD = 0b11111111;			// All pins PORTD are set to output 
	DDRC = 0x00;
    while (1) 
    {
		b6();
    }

	return 0;
}

/*
 *	Switcht tussen lichtje 6 en 7.
 */
void b2()
{
	PORTD = 0b10000000;
	wait(500);
	PORTD = 0b01000000;	
	wait(500);
}

/*
 *	Laat ledjes op PortD loopen van boven naar beneden
 */
void b4()
{
	static int direction = 1;							// Richting van loop 1 = links, 0 is rechts
	static int value = 0x01;							// 0b00000001
	value = (direction == 1) ? value << 1 : value >> 1;	// Richting bepaald

	PORTD = value;										// Zet portd op waarde
	if (value == 0x80)									// Verander van richting als waarde op uiterste links zit
		direction = 0;
	else if (value == 0x01)								// Verander van richting als waarde op uiterste rechts zit
		direction = 1;	
		
	wait(500);
}
/*
 * Laat led 7 knipperen op basis van frequentie.
 */


int prev_state = 0;
void b6()
{
	static int speed_level = 0;
	static BOOL led_on = TRUE;
	
	const BOOL pushed = (PINC & 0b00000001);
	if (pushed && prev_state == 0)
	{
		speed_level = speed_level == 0 ? 1 : 0;
		prev_state = 1; 
	}
	else if (!pushed)
		prev_state = 0;
		
	int hz = speed_level == 0 ? 1000 : 250;
	PORTD = led_on == TRUE ? 0b10000000 : 0x00;
	wait(hz);
	led_on = led_on == TRUE ? FALSE : TRUE;
}
