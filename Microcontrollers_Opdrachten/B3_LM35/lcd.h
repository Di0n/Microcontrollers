/*
 * lcd.h
 *
 * Created: 13-2-2019 14:04:42
 *  Author: Yannick
 */ 

#ifndef LCD_H_
#define LCD_H_

#define LCD_E 	3
#define LCD_RS	2


void lcd_strobe_lcd_e(void);
void lcd_init(void);
void lcd_write_string(char *str);
void lcd_write_data(unsigned char byte);
void lcd_write_cmd(unsigned char byte);
void lcd_set_cursor_pos(int pos);
void lcd_clear_display(void);

#endif