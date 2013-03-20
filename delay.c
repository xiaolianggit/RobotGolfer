// ******************************************************************************************* //
//
//	Filename		:   Delay.c
//	Title        	:   RoboGolfer delay File 
//	Author			:   Fan Wing Sze
//	Description		:   This file is the delay File of the RoboGolfer Project.
//
// ******************************************************************************************* //

#include "Global.h"


//delay for micro-second
void delay_us(u08 delay_time)
{
	u08 time = 0;
	while(time < delay_time)
	{
		_delay_us(1);
		time++;
	}
}


//delay for mili-second
void delay_ms(u08 delay_time)
{
	u08 time = 0;
	while(time < delay_time)
	{
		_delay_ms(1);
		time++;
	}
}

//delay for 250ms
void delay_250ms(u08 delay_time)
{
	u08 time = 0;
	while(time < delay_time)
	{
		delay_ms(250);
		time++;
	}
}


