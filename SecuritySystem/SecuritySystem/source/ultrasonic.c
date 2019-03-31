/*
 * ultrasonic.c
 *
 * Created: 20-3-2019 14:46:50
 *  Author: Dion van der Linden
 */ 
#include "../header/ultrasonic.h"

#define TRIGGER_PIN PINE6
#define ECHO_PIN	PINE4

volatile int timerOverflow = 0;
volatile int flag = 0;
volatile int pulse = 0;

void US_InterruptUpdate(void)
{
	// Low to high
	if (flag == 0)
	{
		TCCR3B |=  (1 << CS11);
		flag = 1;
	}
	// High to low
	else
	{
		TCCR3B = 0;
		pulse = TCNT3;
		TCNT3 = 0;
		flag = 0;
	}
}
void US_SendPulse(void)
{
	PORTE &= ~(1 << TRIGGER_PIN);
	_delay_us(5);
	PORTE |= (1 << TRIGGER_PIN);
	_delay_us(15);
	PORTE &= (~(1 << TRIGGER_PIN));
}

int16_t US_GetDistance(void)
{
	return pulse /58;
}