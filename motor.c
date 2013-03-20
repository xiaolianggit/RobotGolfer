// ******************************************************************************************* //
//
//	Filename		:   Motor.c
//	Title        	:   RoboGolfer Motor File 
//	Author			:   Fan Wing Sze & Wong Ming Kin
//	Description		:   This file is controlling the motor of the RoboGolfer Project.
//
// ******************************************************************************************* //


#include "global.h"


///------------------------------------------------------------------------------------------------------///
///----------------------------     FUNCTIONS   ---------------------------------------------------------///
///------------------------------------------------------------------------------------------------------///

void set_motor_dir(u08 L_motor, u08 R_motor)
{
	motor_dir = (L_motor<<6);
	motor_dir |= (R_motor<<2);
	motor_dir &= 0xCC;

	D_Flip_Flop &= 0x33;
	D_Flip_Flop |= motor_dir;
}

void Motor_stop(void)	// Delay for a while before return the function
{
	set_motor_dir(MOTOR_STOP, MOTOR_STOP);
	L_motor_speed = R_motor_speed = 0;
	delay_ms(100);
}

//Call this function to set the RoboGolfer moves forward with respective speeds
void Motor_forward(u08 L_motor, u08 R_motor)
{
	set_motor_dir(MOTOR_FORWARD, MOTOR_BACKWARD);
	L_motor_speed = L_motor;
	R_motor_speed = R_motor;

}

//Call this function to set the RoboGolfer moves backward with respective speeds
void Motor_backward(u08 L_motor, u08 R_motor)
{
	set_motor_dir(MOTOR_BACKWARD, MOTOR_FORWARD);
	L_motor_speed = L_motor;
	R_motor_speed = R_motor;
}

//Call this function to set the RoboGolfer turns left with respective speeds
void Motor_TurnLeft(u08 L_motor, u08 R_motor)
{
	set_motor_dir(MOTOR_BACKWARD, MOTOR_BACKWARD);
	L_motor_speed = L_motor;
	R_motor_speed = R_motor;
}

void Motor_TurnRight(u08 L_motor, u08 R_motor)
{
	set_motor_dir(MOTOR_FORWARD, MOTOR_FORWARD);
	L_motor_speed = L_motor;
	R_motor_speed = R_motor;
}

//Call this function to set the RoboGolfer turns right with respective speeds
void Motor_adjust(void)
{
	;
}


///------------------------------------------------------------------------------------------------------///
///-----------------------     Software Generated PWM ISR   ---------------------------------------------///
///------------------------------------------------------------------------------------------------------///

ISR (TIMER1_COMPA_vect)
{
	static u08 time_tick = 0;

	OCR1A += MOTOR_PWM_PERIOD;
	if(OCR1A >= ICR1)
		OCR1A = MOTOR_PWM_PERIOD;

	if(++time_tick >= MOTOR_TICK)
	{
		time_tick = 0;

		D_Flip_Flop &= 0x33;
		D_Flip_Flop |= motor_dir;

		if(L_motor_speed == 0)
			D_Flip_Flop &= 0x3F;		//stop
		if(R_motor_speed == 0)
			D_Flip_Flop &= 0xF3;

		Databus_clear();				//motor update
		DATA_DIR = PORT_OUTPUT;
		PORTC = D_Flip_Flop;
		MOTOR_EN = 1;
		MOTOR_EN = 0;
	}
	else
	{
		u08 temp = D_Flip_Flop;
		if(L_motor_speed <= time_tick)
			D_Flip_Flop &= 0x3F;
		if(R_motor_speed <= time_tick)
			D_Flip_Flop &= 0xF3;

		if(D_Flip_Flop != temp)
		{
			Databus_clear();				//motor update
			DATA_DIR = PORT_OUTPUT;
			PORTC = D_Flip_Flop;
			MOTOR_EN = 1;
			MOTOR_EN = 0;
		}
	}	
}
