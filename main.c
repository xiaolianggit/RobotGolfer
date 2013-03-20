// ******************************************************************************************* //
//
//	Filename		:   Main.c
//	Title        	:   RoboGolfer Main File 
//	Author			:   Fan Wing Sze
//	Description		:   This file is the Main File of the RoboGolfer Project.
//
// ******************************************************************************************* //


///------------------------------------------------------------------------------------------------------///
///----------------------------   INCLUDE FILES ---------------------------------------------------------///
///------------------------------------------------------------------------------------------------------///

#include "Global.h"

///------------------------------------------------------------------------------------------------------///
///----------------------------     FUNCTIONS   ---------------------------------------------------------///
///------------------------------------------------------------------------------------------------------///

void IO_init(void)
{
	DDRA = 0b00000000;
	DDRB = 0b10011111;
	DDRC = 0b11111111;
	DDRD = 0b11110010;

	PORTA = 0b00000000;
	PORTB = 0b00000000;
	PORTC = 0b00000000;
	PORTD = 0b00000001;
}

//Call this function for controlling the robot manually
void inherent_function(void)
{
	ADC_update();
	

	if(!SW_IN_2 && !SW_IN_1)		//enter the line following mode when button S5 and S6 are pressed together
	{
		while(!SW_IN_2 || !SW_IN_1)
		{
			test_mode();
		}
		
	}
	else if(!SW_IN_1)				//enter the manual control mode when button S6 is pressed
	{
		while(!SW_IN_1);
		
		test_mode();
	}
}

int main(void)
{
	IO_init();
	Timer1_init();
	ADC_init();

	Motor_stop();
	Servo_init();
	LCD_init();

	sei();

	while(1)
	{
		inherent_function();
	}
	
	while(1);
	return 0;
}
