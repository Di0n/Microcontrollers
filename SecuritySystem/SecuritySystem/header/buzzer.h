/*
 * buzzer.h
 *
 * Created: 31-3-2019 19:03:34
 *  Author: Yannick
 */ 


#ifndef BUZZER_H_
#define BUZZER_H_

#include <avr/io.h>
#include <avr/interrupt.h>

void buzzer_Start(void);
void buzzer_Stop(void);



#endif /* BUZZER_H_ */