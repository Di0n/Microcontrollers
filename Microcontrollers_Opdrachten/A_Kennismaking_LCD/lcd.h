/*
 * lcd.h
 *
 * Created: 13-2-2019 14:04:42
 *  Author: Yannick
 */ 

#ifndef LCD_H_
#define LCD_H_

void lcd_strobe_lcd_e(void);
void init_4bits_mode(void);
void lcd_write_string(char *str);
void lcd_write_data(unsigned char byte);
void lcd_write_cmd(unsigned char byte);


#endif