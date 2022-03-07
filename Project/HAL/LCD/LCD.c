/*
 * LCD.c
 */ 

#include <avr/delay.h>



#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_types.h"
#include "LCD.h"
#include "../../MCAL/DIO/DIO_TYPES.h"
#include "../../MCAL/DIO/DIO_REG.h"
#include "../../MCAL/DIO/DIO.h"
#define LCD_MODE	4 

//static uint8 InitStepFinished = 0 ; //3shan yeb2a bas ma2ry fel file daaa


void LCD_Initialize(void)
{
	#if LCD_MODE  ==  8 //init the pins dir in 8bit mode

	DIO_SetPinDirection(PORTD,Pin1, Output );
	DIO_SetPinDirection(PORTD,Pin2, Output );
	DIO_SetPinDirection(PORTD,Pin3, Output );
	DIO_SetPortDirection(PORTC,Output);

	_delay_ms(100);
	// send commands to lcd for init as 8 bit mode
	LCD_WriteCmd(0x38);		 // sad3et kadh fun write 0x38
	LCD_WriteCmd(0x0c);     //kadh close cursor
	LCD_WriteCmd(0x01);    //kadh clear lcd
	LCD_WriteCmd(0x06);   // kadh cursor right or inc
	LCD_WriteCmd(0x02);  // kadh 3malth return to home
	#elif LCD_MODE == 4 //init the pins dir in 4bit mode

	DIO_SetPinDirection(PORTB,Pin1, Output );
	DIO_SetPinDirection(PORTB,Pin2, Output );
	DIO_SetPinDirection(PORTB,Pin3, Output );

	DIO_SetPinDirection(PORTA, Pin4, Output);
	DIO_SetPinDirection(PORTA, Pin5, Output);
	DIO_SetPinDirection(PORTA, Pin6, Output);
	DIO_SetPinDirection(PORTA, Pin7, Output);

	_delay_ms(100);
	// send commands to lcd for init as 4 bit mode
	LCD_WriteCmd(0x33);
	LCD_WriteCmd(0x32);
	LCD_WriteCmd(0x28);

	LCD_WriteCmd(0x0c);     //kadh close cursor
	LCD_WriteCmd(0x01);    //kadh clear lcd
	LCD_WriteCmd(0x06);   // kadh cursor right or inc
	LCD_WriteCmd(0x02);  // kadh 3malth return to home
	#endif
}

void LCD_WriteCmd(uint8 Cmd)  // rs cmd reg walh data reg
{
	DIO_SetPinValue(PORTB,Pin1,LOW );
	DIO_SetPinValue(PORTB,Pin2,LOW );
	DIO_SetPinValue(PORTB,Pin3,LOW );

	PORTA_REG = ((Cmd & 0xf0)|(PORTA_REG & 0x0F));

	DIO_SetPinValue(PORTB,Pin3,HIGH);
	_delay_ms(1); // bta3 latch
	DIO_SetPinValue(PORTB,Pin3,LOW );

	PORTA_REG = (Cmd << 4)|(PORTA_REG & 0x0f);

	DIO_SetPinValue(PORTB,Pin3,HIGH);
	_delay_ms(1); // bta3 latch
	DIO_SetPinValue(PORTB,Pin3,LOW );

	_delay_ms(5);
}

void LCD_WriteData(uint8 Data)
{
	DIO_SetPinValue(PORTB,Pin1,HIGH ); // Rs High bass kadh htktb 3lah data reg
	DIO_SetPinValue(PORTB,Pin2,LOW );
	DIO_SetPinValue(PORTB,Pin3,LOW );

	PORTA_REG = (Data & 0xF0)|(PORTA_REG & 0x0F);

	DIO_SetPinValue(PORTB,Pin3,HIGH);
	_delay_ms(1); // bta3 latch
	DIO_SetPinValue(PORTB,Pin3,LOW );

	PORTA_REG = (Data << 4)|(PORTA_REG & 0x0F);

	DIO_SetPinValue(PORTB,Pin3,HIGH);
	_delay_ms(1); // bta3 latch
	DIO_SetPinValue(PORTB,Pin3,LOW );

	_delay_ms(5);
}

void LCD_WriteString(uint8* Str)
{
	uint8 i=0;
	while(Str[i] != '\0')
	{
		LCD_WriteData(Str[i]);
		i++;
	}
}

void LCD_GoToPos(uint8 Row , uint8  Col) // 3az akteb feh ay mkan ana 3ayzh
{
	uint8 pos[2]={0x80,0xc0};
	LCD_WriteCmd(pos[Row]+Col);
}

//////////////////////////////////////////////////////////////////////////

void LCD_StoreCustomChr(uint8* pattern , uint8 CGRAM_index)
{
	uint8 Address ; 
	uint8 index ;
	if (CGRAM_index <8 )
	{
		Address = CGRAM_index * 8 ;
		Address = SET_BIT (Address , 6);
		LCD_WriteCmd(Address);
		for (index = 0 ; index < 8 ; index ++)
		{
			LCD_WriteData(pattern[index]);
		}
	}
	LCD_WriteCmd(0x02);
}


void LCD_DisplayCustomChr(uint8 CGRAM_index , uint8 Row, uint8 Col)
{
	LCD_GoToPos( Row , Col);
	
	LCD_WriteData(CGRAM_index);
}