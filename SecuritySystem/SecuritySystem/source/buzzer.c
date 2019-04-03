/*
 * buzzer.c
 *
 * Created: 31-3-2019 19:03:20
 *  Author: Yannick
 */ 

#include "../header/buzzer.h"

#define INTERVAL 2273

void buzzer_Start(void)
{
	ICR1 = INTERVAL;
	OCR1A = INTERVAL / 4;
	TCCR1A = 0b10000010;			// timer, compare output at OC1A=PB5
	TCCR1B = 0b00011010;			// fast PWM, TOP = ICR1, prescaler=8 (1MHz), RUN
}

void buzzer_Stop(void)
{
	TCCR1A = 0;
	TCCR1B = 0;
}

