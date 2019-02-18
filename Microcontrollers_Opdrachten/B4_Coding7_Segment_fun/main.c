/*
 * B4_Coding7_Segment_fun.c
 *
 * Created: 6-2-2019 16:15:50
 * Author : Dion van der Linden
 */ 

#include <avr/io.h>
#include "utils.h"
typedef struct
{
	unsigned char data;
	unsigned int delay;
} Pattern;

Pattern pattern[] =
{
	{0x00, 100}, {0x01, 100}, {0x02, 100}, {0x04, 100}, {0x10, 100}, {0x20, 100}, {0x40, 100}, {0x80, 100},
	{0x00, 100},
	{0xAA,  50}, {0x55,  50},
	{0xAA,  50}, {0x55,  50},8
	{0xAA,  50}, {0x55,  50},
	{0x00, 100},
	{0x81, 100}, {0x42, 100}, {0x24, 100}, {0x18, 100}, {0x0F, 200}, {0xF0, 200}, {0x0F, 200}, {0xF0, 200},
	{0x00, 0x00}
};

int main(void)
{

		DDRD = 0xFF;
		
		while (1)
		{
			// Set index to begin of pattern array
			int index = 0;
			// as long as delay has meaningful content
			while( pattern[index].delay != 0 ) {
				// Write data to PORTD
				PORTD = pattern[index].data;
				// wait
				wait(pattern[index].delay);
				// increment for next round
				index++;
			}
		}

	
	return 0;
}

