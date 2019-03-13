/*
 * utils.c
 *
 * Created: 13-3-2019 11:14:24
 *  Author: Dion van der Linden
 */ 
#include "../header/utils.h"
#include <util/delay.h>
void Utils_Wait(int ms)
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms(1);
	}
}
