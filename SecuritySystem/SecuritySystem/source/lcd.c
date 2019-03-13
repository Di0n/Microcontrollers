/*
 * lcd.c
 *
 * Created: 13-3-2019 12:12:10
 *  Author: Dion van der Linden
 */ 
#include "../header/lcd.h"

#include <avr/io.h>
#include <avr/interrupt.h>

#include "../header/utils.h"

#define LCD_E 3
#define LCD_RS 2

void StrobeLcd(void);
void WriteData(unsigned char byte);
void WriteCommand(unsigned char byte);


void LCD_Init(void)
{
	// PORTC output mode and all low (also E and RS pin)
	DDRC = 0xFF;
	PORTC = 0x00;

	// Step 2 (table 12)
	PORTC = 0x28;	// function set
	StrobeLcd();

	// Step 3 (table 12)
	PORTC = 0x20;   // function set
	StrobeLcd();
	PORTC = 0x80;
	StrobeLcd();

	// Step 4 (table 12)
	PORTC = 0x00;   // Display on/off control
	StrobeLcd();
	PORTC = 0xF0;
	StrobeLcd();

	// Step 4 (table 12)
	PORTC = 0x00;   // Entry mode set
	StrobeLcd();
	PORTC = 0x60;
	StrobeLcd();
}

void LCD_WriteString(const char* str)
{
	for (; *str; str++)
	{
		WriteData(*str);	
	}
}

void LCD_SetCursorPos(unsigned char pos)
{
	/*for (int i = 0; i < pos; i++)
		lcd_write_command(0x14);*/
	WriteCommand(pos);
	Utils_Wait(1);
}

void LCD_ClearDisplay(void)
{
	WriteCommand(0x01);
	Utils_Wait(1);
}

void WriteData(unsigned char byte)
{
	// First nibble.
	PORTC = byte;
	PORTC |= (1<<LCD_RS);
	StrobeLcd();

	// Second nibble
	PORTC = (byte<<4);
	PORTC |= (1<<LCD_RS);
	StrobeLcd();
}

void WriteCommand(unsigned char byte)
{
	// First nibble.
	PORTC = byte;
	PORTC &= ~(1<<LCD_RS);
	StrobeLcd();

	// Second nibble
	PORTC = (byte<<4);
	PORTC &= ~(1<<LCD_RS);
	StrobeLcd();
}

void StrobeLcd(void)
{
	PORTC |= (1<<LCD_E);	// E high
	Utils_Wait(25);			// nodig
	PORTC &= ~(1<<LCD_E);  	// E low
	Utils_Wait(25);			// nodig?
}

