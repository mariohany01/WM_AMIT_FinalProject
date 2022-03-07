/*
 * LCD.h
 */ 


#ifndef LCD_H_
#define LCD_H_

void LCD_Initialize(void);

void LCD_WriteCmd (uint8 Cmd);	//Teb3at el instruction

void LCD_WriteData (uint8 Data);

void LCD_WriteString (uint8* Str);

void LCD_GoToPos (uint8 Row , uint8 Col);

// Ashkal

void LCD_StoreCustomChr(uint8* pattern , uint8 CGRAM_index);


void LCD_DisplayCustomChr(uint8 CGRAM_index , uint8 Row, uint8 Col);





#endif /* LCD_H_ */