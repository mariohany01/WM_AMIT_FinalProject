/*
 * APP_G_LCD.c

 */ 

#include "../HAL/G_LCD/Image.h"
#include <avr/delay.h>


int G_LCD()
{
	
	GLCD_Init();
	GLCD_ClearAll();		
	
	int Duty_cycle = 90;
	
	
	GLCD_String_Letter(2,"Duty Cycle : 90 %");
	GLCD_String_Letter(3,"Frequency  : 00 KHZ");
		GLCD_ClearAll();
	_delay_ms(3000);
	GLCD_ClearAll();	
	
	if (Duty_cycle == 0 )
	{
		GLCD_String_IMG(Zero);
		
	}
	
	else if (Duty_cycle <= 10)
	{
		GLCD_String_IMG(One);
		
	}	
	
	else if (Duty_cycle <= 20)
	{
		GLCD_String_IMG(Eleven);
	}
	
	else if (Duty_cycle <= 30)
	{
		GLCD_String_IMG(Twenty_One);
	}
	
	else if (Duty_cycle <= 40)
	{
		GLCD_String_IMG(Thirty_One);
	}		
	
	else if (Duty_cycle <= 50)
	{
		GLCD_String_IMG(Forty_One);
	}
	
	else if (Duty_cycle <= 60)
	{
		GLCD_String_IMG(Fifty_One);
		
	}	
	
	else if (Duty_cycle <= 70)
	{
		GLCD_String_IMG(Sixty_One);
	}

	else if (Duty_cycle <= 80)
	{
		GLCD_String_IMG(Seventy_One);
	}
	
	else if (Duty_cycle <= 90)
	{
		GLCD_String_IMG(Eighty_One);
	}
	
	else if (Duty_cycle <= 100)
	{
		GLCD_String_IMG(Ninty_One);
	}
	GLCD_String_Letter(2,"LCD Graph For Given   Duty cycle :");

	while(1);
}