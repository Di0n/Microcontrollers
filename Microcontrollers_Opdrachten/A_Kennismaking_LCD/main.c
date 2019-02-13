#include "utils.h"
#include "lcd.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>



int main( void )
/* 
short:			main() loop, entry point of executable
inputs:			
outputs:	
notes:			Slow background task after init ISR
Version :    	DMK, Initial code
*******************************************************************/
{
	// Init I/O
	DDRD = 0xFF;			// PORTD(7) output, PORTD(6:0) input	

	// Init LCD
	init();

	// Write sample string
	lcd_write_string("test12345678909876543211234567890");

	// Loop forever
	while (1)
	{
		PORTD ^= (1<<7);	// Toggle PORTD.7
		wait( 250 );								
	}

	return 1;
}
















































///*
 //* A_Kennismaking_LCD.c
 //*
 //* Created: 13-2-2019 11:37:08
 //* Author : Yannick van Dolen
 //*/ 
//
//#ifndef F_CPU
//#define F_CPU 8000000L 
//#endif
//
//#include "utils.h"
//#include <avr/io.h>
//
//void send_lcd_command(int command);
//void init_lcd();
//void lcd_writeChar( unsigned char dat );
//
//int main(void)
//{	
    //DDRC = 0xFF; // PORTC = output
	//
///*
//init:
//0x30(8bit)
//20 delay
//0x30
//20 delay
//0x30
//20 delay
//function set
//display clear
//entry mode */
//
	//send_lcd_command(0x30);
	//wait(20);
	//send_lcd_command(0x30);
	//wait(20);
	//send_lcd_command(0x30);
	//wait(20);
	//send_lcd_command(0x28);
	//wait(20);
	//send_lcd_command(0x01);
	//wait(20);
	//send_lcd_command(0x06);
	//wait(20);
	//send_lcd_command(0x0F);
	//
	//while (1) 
    //{
				//
    //}
//}
//
//void send_lcd_command(int command)
//{
	//PORTC = command;
//}
//
//void init_lcd()
//{
	//// return home	lcd_command( 0x02 );
	//// mode: 4 bits interface data, 2 lines, 5x8 dots	
	//send_lcd_command( 0x28 );
	//// display: on, cursor off, blinking off	
	//send_lcd_command( 0x0C );
	//// entry mode: cursor to right, no shift 	
	//send_lcd_command( 0x06 );
	//// RAM adress: 0, first position, line 1 	
	//send_lcd_command( 0x80 );
//
//}
//
//void lcd_writeChar( unsigned char dat )
//{
	//PORTC = dat & 0xF0;				// hoge nibble
	//PORTC = PORTC | 0x0C;			// data (RS=1),			
									//// start (EN=1)
	//wait(1);					// wait 1 ms
	//PORTC = 0x04;					// stop (EN = 0)
	//
	//PORTC = (dat & 0x0F) << 4;		// lage nibble
	//PORTC = PORTC | 0x0C;			// data (RS=1),
									//// start (EN=1)
	//wait(1);					// wait 1 ms
	//PORTC = 0x00;					// stop 				
									//// (EN=0 RS=0)
//}
//
