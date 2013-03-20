// ******************************************************************************************* //
//
//	Filename		:   Timer.c
//	Title        	:   RoboGolfer Timer File 
//	Author			:   Fan Wing Sze
//	Description		:   This file is initializing the timer of RoboGolfer
//
// ******************************************************************************************* //


#include "global.h"


//This function initialize the timer1 to 16 bit CTC mode
//WGM13 to WGM10 = 1100, so it is running in CTC mode with ICR1 at TOP, which will update OCR immediately
//set the compare output mode to normal port operation
//set the prescaler to clk/8
//enable the timer1 overflow interrupt and output compare match A interrupt
//please read p.67 to p.80 of ATMega16 datasheet for details
void Timer1_init(void)
{
	TCCR1A = 0b00100000;
	TCCR1B = 0b00011010;

	ICR1 = 	9216;					// trigger the overflow interrupt for every 2ms 4608
	OCR1A = MOTOR_PWM_PERIOD;		// trigger the output compare match A interrupt
	OCR1B = PWM_1_5ms;					// initialize PWM Generation

	TIMSK |= 0b00111000;			// enable Interrupt, please read p.109 of ATMega 16 datasheet for details
}
