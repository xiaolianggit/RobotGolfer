// ******************************************************************************************* //
//
//	Filename		:   Joypad.h
//	Title        	:   RoboGolfer joypad Header File 
//	Author			:   Fan Wing Sze
//	Description		:   This file is the joypad Header File of the RoboGolfer Project.
//
// ******************************************************************************************* //

#ifndef JOYPAD_H
#define JOYPAD_H


#define		JOYPAD_MASK 		0xFC

#define		JOYPAD_FORWARD		0x40
#define		JOYPAD_BACKWARD		0x80
#define		JOYPAD_LEFT			0x20
#define		JOYPAD_RIGHT		0x10


// ================================================================================================================= //
// =========================                         Pin Configuration                     ========================= //
// ================================================================================================================= //
#define		JOYPAD_EN			PD_7_OUT
#define		JOYPAD_IN_1			PA_4_IN
#define		JOYPAD_IN_2			PA_5_IN
#define		JOYPAD_SELECT		PORTC


// ================================================================================================================= //
// =========================                         Define Variables                      ========================= //
// ================================================================================================================= //
volatile u08 joypad_switch;		//the current status of all switches on joypad
volatile u08 D_Flip_Flop;


// ================================================================================================================= //
// =========================                         Function Prototype                    ========================= //
// ================================================================================================================= //
extern void update_switch(void);		//update the switches on joypad
extern void get_switch(u08 channel);


#endif
