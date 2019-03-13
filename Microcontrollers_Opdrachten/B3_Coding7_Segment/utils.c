/*
 * utils.c
 *
 * Created: 30-1-2019 11:14:35
 *  Author: Dion van der Linden
 */ 

#include "utils.h"
#include <util/delay.h>

void wait(int ms)
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}
	