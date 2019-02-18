/*
 * lcd.c
 *
 * Created: 13-2-2019 14:01:28
 *  Author: Yannick
 */ 

#include <avr/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "utils.h"

#define LCD_E  3
#define LCD_RS 2

void init()
{
	// Init LCD module in 4 bits mode
	
	DDRC = 0xFF; // Port C in output mode
	PORTC = 0x00; // Port C all 0
	
	// Step 2
	PORTC = 0x28; // function set
	lcd_strobe_lcd_e();
	
	// Step 3
	PORTC = 0x28;  // Function set
	lcd_strobe_lcd_e();
	PORTC = 0x80;
	lcd_strobe_lcd_e();
	
	// Step 4
	PORTC = 0x00;
	lcd_strobe_lcd_e();
	PORTC = 0x60;
	lcd_strobe_lcd_e();
	
	PORTC = 0x1F;
	lcd_strobe_lcd_e();
}

void lcd_strobe_lcd_e()
{
	PORTC |= (1<<LCD_E);
	wait(1);
	PORTC &= ~(1<<LCD_E);
	wait(1);
}

void lcd_write_string(char *str)
{
	//while(*str)
		//lcd_write_data(*str++);
		for( ; *str; *str++)
			lcd_write_data(*str);
}

void lcd_write_data(unsigned char byte)
{
	// First nibble
	PORTC = byte;
	PORTC |= (1 << LCD_RS);
	
	// Second nibble
	PORTC = (byte << 4);
	PORTC |= (1 << LCD_RS);
	lcd_strobe_lcd_e();
}

void lcd_write_cmd(unsigned char byte)
{
	// First nibble
	PORTC = byte;
	PORTC &= ~(1 << LCD_RS);
	lcd_strobe_lcd_e();
	
	// Second nibble
	PORTC = (byte << 4);
	PORTC &= ~(1 << LCD_RS);
	lcd_strobe_lcd_e();	
}