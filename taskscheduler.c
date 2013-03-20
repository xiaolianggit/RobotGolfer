// ******************************************************************************************* //
//
//	Filename		:   Taskschedular.c
//	Title        	:   RoboGolfer task schedular File 
//	Author			:   Fan Wing Sze
//	Description		:   This file containing two interrupt functions which mainly controlling the schedular and the pwm generation of RoboGolfer
//
// ******************************************************************************************* //

#include "global.h"

volatile u08 task_schedule = 0;
volatile u08 channel = 0;

//This is the schedular of the RoboGolfer, which will be triggered for every 2ms whenever the timer1 is overflowed
ISR (TIMER1_CAPT_vect)
{
	TIFR |= 0x08;				
	TCCR1A = 0x20;				// 0b00100000 Clear OC1B on compare match (Setoutput to low level)
	OCR1B = pwm_duty[channel];	//select channel for servo PWM
	TIMSK |= 0x08;				//enable COMPB

	sei();						//enable the global interrupt for the timer1 compare match interrupt

	if(++channel >= 8)
		channel = 0;
	Sensor_front_update();
	Sensor_back_update();
	Sensor_middle_update();
	switch(++task_schedule)
	{
	case 1:					//update front floor sensor, and switch for every 16ms
		IR_update();
		break;

	case 2:					//update back floor sensor, and switch for every 16ms

		break;

	case 3:					//update middle floor sensor, and switch for every 16ms
		break;

	case 4:
		LCD_update();		//update the first part of lcd data for every 16ms	
		break;

	case 5:					//update the remaining part of lcd data for every 16ms
		LCD_update();
		break;
	
	case 6:
		if(!SW_IN_2)
		{
			if(LCD_menu_update_flag == LCD_MENU_NOTUPDATE)		//check the update status of the lcd menu, so the lcd menu is updated once whenever button S5 pressed once
			{
				LCD_menu_update();
			}
		}
		else
		{
			LCD_menu_update_flag = LCD_MENU_NOTUPDATE;			//reset the update status after the update is finished
		}
		break;

	case 7:														//if button S3 is pressed, the lcd menu will change between two pages, this will update the first part of lcd menu
		if(LCD_menu_update_flag == LCD_MENU_UPDATING)
		{
			LCD_menu_update();
		}
		break;
	case 8:
		update_switch();	//update joypad switch for every 16ms

	default:
		task_schedule = 0;
		break;	
	}
}
