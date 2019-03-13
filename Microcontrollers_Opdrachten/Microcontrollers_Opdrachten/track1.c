/*
 * track1.c
 *
 * Created: 6-2-2019 10:41:40
 *  Author: Dion van der Linden
 */ 
#include "track1.h"
#include <avr/io.h>
#include "utils.h"
#include "globals.h"


/*
 *	Switcht tussen lichtje 6 en 7.
 *	DDRD moet op 0b11111111 gezet worden.
 */
void b2()
{
	PORTD = 0b10000000;
	wait(500);
	PORTD = 0b01000000;
	wait(500);
}

/*
* Coding I/O
* Een LED laten knipperen als knop C0 is ingedrukt
*/
void b3() 
{

	
	DDRD = 0b11111111;			// All pins PORTD are set to output
	DDRC = 0b00000000;
	
	while (1)
	{
		if(PINC & 1)
		{
			PORTD = 0b10000000;			// Write 10101010b PORTD
			wait( 250 );
			PORTD = 0b00000000;			// Write 01010101b PORTD
			wait( 250 );
		}
		else
		{
			PORTD = 0b00000000;
		}
	}
}

/*
 *	Laat ledjes op PortD loopen van boven naar beneden
 *	DDRD moet op 0b11111111 gezet worden.
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
    * Coding LED patterns using lookup
	* Een lichtpatroon laten lopen met een C array
	*/
void b5()
{

	
	int index = 0;
	int light_sequence[10] = {
		0b10000001,		// Buiten naar binnen
		0b01000010,
		0b00100100,
		0b00011000,
			
		0b00111100,		// Helemaal opvullen
		0b01111110,
		0b11111111,
			
		0b11100111,		// Leegmaken vanaf binnen
		0b11000011,
		0b10000001
	};
		
	while (1)
	{
		PORTD = light_sequence[index];
			
		index++;
		if(index == 9) // skipping last one because it's a duplicate of the first
		{
			index = 0;
		}
			
		wait(2500);
	}


}

/*
 *	Laat led 7 knipperen op basis van frequentie.
 *	DDRC moet op 0x00 gezet worden
 */
void b6()
{
	static int prev_state = 0;					// Vorige staat van knop. 0 = uit, 1 = aan.
	static int speed_level = 0;					// 2 speed levels, 1 en 0.
	static BOOL led_on = TRUE;					// Led aan en uit toggle.
	
	const BOOL pushed = (PINC & 0b00000001);	// Is led ingedrukt.
	if (pushed && prev_state == 0)
	{
		speed_level = speed_level == 0 ? 1 : 0;	// Verander speed level en zet prev state op 1.
		prev_state = 1; 
	}
	else if (!pushed)
		prev_state = 0;
		
	int hz = speed_level == 0 ? 1000 : 250;		// HZ van knipper licht
	PORTD = (led_on) ? 0b10000000 : 0x00;		// Zet led uit of aan.
	
	wait(hz);
	
	led_on = !led_on;							//== TRUE ? FALSE : TRUE;
}

/*
 * Keuze opdracht, 3 state leds
 * 
*/
void b7b()
{
	int index;
	
	while(1)
	{
		for (index = 0; index < 6; index++)
		{
			setCharliePlexingLed(index);
			wait(2500);
		}
	}
}

void setCharliePlexingLed(int lednr) // Part of 7b
{
	switch(lednr)
	{
		case 0:						//1+
		DDRD  = 0b11111011;		//2+
		PORTD = 0b00000001;		//3x
		break;
		case 1:						//1-
		DDRD  = 0b11111011;		//2+
		PORTD = 0b00000010;		//3x
		break;
		case 2:						//1+
		DDRD  = 0b11111101;		//2x
		PORTD = 0b00000001;		//3-
		break;
		case 3:						//1-
		DDRD  = 0b11111101;		//2x
		PORTD = 0b00000100;		//3+
		break;
		case 4:						//1x
		DDRD  = 0b11111110;		//2+
		PORTD = 0b00000010;		//3-
		break;
		case 5:						//1x
		DDRD  = 0b11111110;		//2-
		PORTD = 0b00000100;		//3+
		break;
	}
}