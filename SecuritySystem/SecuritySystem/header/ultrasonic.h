/*
 * ultrasonic.h
 *
 * Created: 20-3-2019 14:46:40
 *  Author: Dion van der Linden
 */ 


#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "../header/globals.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>

void US_SendPulse(void);
void US_InterruptUpdate(void);
int16_t US_GetDistance(void);

#endif /* ULTRASONIC_H_ */