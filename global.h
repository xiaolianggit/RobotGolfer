// ******************************************************************************************* //
//
//	Filename		:   Global.h
//	Title        	:   RoboGolfer Main Header File 
//	Author			:   Fan Wing Sze
//	Description		:   This header file is the Main Header File of the RoboGolfer Project.
//
// ******************************************************************************************* //

#ifndef		__GLOBAL_H__
#define		__GLOBAL_H__


#define		F_CPU		18432000


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


#include "defineConstant.h"
#include "IOdef.h"

#include "adc.h"
#include "databus.h"
#include "delay.h"
#include "joypad.h"
#include "lcd.h"
#include "motor.h"
#include "servo.h"
#include "timer.h"
#include "map.h"
#include "moving.h"
#include "golfer.h"


void beep_sound(void);
void inherent_function(void);


#endif
