// ******************************************************************************************* //
//
//	Filename		:   Motor.h
//	Title        	:   RoboGolfer Motor Header File 
//	Author			:   Fan Wing Sze
//	Description		:   This file is the Motor Header File of the RoboGolfer Project.
//
// ******************************************************************************************* //


#ifndef		__MOTOR_H__
#define		__MOTOR_H__


// ================================================================================================================= //
// =========================                         Constant Define                       ========================= //
// ================================================================================================================= //
#define		MOTOR_PWM_PERIOD		46		// every 20us
#define		MOTOR_TICK				100 		// motor speed resolution is 40

#define		MOTOR_STOP				0
#define		MOTOR_FORWARD			2
#define		MOTOR_BACKWARD			1


#define		SPEED_FULL				20
#define		SPEED_TURN				10

#define		MOTOR_SMALL_L	0
#define 	MOTOR_SMALL_R	0

#define		TURN_DELAY_PERIOD	10		//delay 100ms


// ================================================================================================================= //
// =========================                         Function Prototype                    ========================= //
// ================================================================================================================= //
void Motor_stop(void);
void Motor_adjust(void);
void Motor_forward(u08 L_motor, u08 R_motor);
void Motor_backward(u08 L_motor, u08 R_motor);
void Motor_TurnLeft(u08 L_motor, u08 R_motor);
void Motor_TurnRight(u08 L_motor, u08 R_motor);


// ================================================================================================================= //
// =========================                           Global Variables                    ========================= //
// ================================================================================================================= //
volatile u08 motor_dir;
volatile u08 L_motor_speed, R_motor_speed;


#endif
