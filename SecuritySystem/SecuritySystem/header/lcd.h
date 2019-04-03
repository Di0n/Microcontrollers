/*
 * lcd.h
 *
 * Created: 13-3-2019 12:09:39
 *  Author: Dion van der Linden
 */ 


#ifndef LCD_H_
#define LCD_H_

void LCD_Init(void);
void LCD_WriteString(const char* str);
void LCD_WriteLine(const char* str, int line);
void LCD_ClearDisplay(void);
void LCD_SetCursorPos(unsigned char pos);

#endif /* LCD_H_ */