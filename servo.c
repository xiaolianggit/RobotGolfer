// ******************************************************************************************* //
//
//	Filename		:   Servo.c
//	Title        	:   RoboGolfer Servo File 
//	Author			:   Fan Wing Sze
//	Description		:   This file is controlling the servos of RoboGolfer
//
// ******************************************************************************************* //


#include "global.h"

#define DELAY_PERIOD	100		//ms
///------------------------------------------------------------------------------------------------------///
///----------------------------     FUNCTIONS   ---------------------------------------------------------///
///------------------------------------------------------------------------------------------------------///

void Servo_init(void)
{
	for(u08 i=0; i<8; i++)
		pwm_duty[i] = PWM_1_5ms;

	rotate_cannon_servo_duty = ROTATE_CANNON_INIT;
	rotate_hands_servo_duty = ROTATE_HANDS_INIT;
	right_hand_duty = HAND_RIGHT_INIT;
	left_hand_duty = HAND_LEFT_INIT;
	cannon_servo_duty = CANNON_STOP;
}


//control the Clip close
void Hand_close(void)
{
	right_hand_duty = HAND_RIGHT_CLOSE;
	left_hand_duty = HAND_LEFT_CLOSE;
	delay_ms(DELAY_PERIOD);

}

//control the Clip open
void Hand_open(void)
{
	right_hand_duty = HAND_RIGHT_OPEN;
	left_hand_duty = HAND_LEFT_OPEN;
	delay_ms(DELAY_PERIOD);

}

void Hand_pre_open(void)
{
	right_hand_duty = HAND_RIGHT_PRE_OPEN;
	left_hand_duty = HAND_LEFT_PRE_OPEN;
	delay_ms(DELAY_PERIOD);
}

//control the Rotate Clip Servo up
void Hand_up(void)
{
	rotate_hands_servo_duty = ROTATE_HANDS_UP;
	delay_ms(DELAY_PERIOD);
	delay_ms(DELAY_PERIOD);

}

void Hand_up_slow(void)
{
	u16 i;
	for(i = ROTATE_HANDS_READY; i > (ROTATE_HANDS_UP + 20); i-= 20)
	{
		rotate_hands_servo_duty = i;
		delay_ms(8);
	}
	rotate_hands_servo_duty = ROTATE_HANDS_UP;
}
//control the Rotate Clip Servo up so that it can put the ball
void Hand_up_2(void)
{
  rotate_hands_servo_duty = ROTATE_HANDS_UP_2;
  	delay_ms(DELAY_PERIOD);
	delay_ms(100);
}

//control the Rotate Clip Servo down
void Hand_down(void)
{
	rotate_hands_servo_duty = ROTATE_HANDS_DOWN;
	delay_ms(DELAY_PERIOD);
	delay_ms(100);

}

void Hand_drop(void)
{
	rotate_hands_servo_duty = ROTATE_HANDS_DROP;
  	delay_ms(DELAY_PERIOD);
}

//control gun shooting angle
void Cannon_move(u16 position)
{
	rotate_cannon_servo_duty = position;
	delay_ms(8);			///

}

//control gun shoot or not
void Cannon_shoot(void)
{
	cannon_servo_duty = CANNON_SHOOT;
	delay_250ms(4);
	delay_ms(100);
}

void Cannon_shoot_only(void)
{
	cannon_servo_duty = CANNON_SHOOT;
}

void Cannon_stop(void)
{
	cannon_servo_duty = CANNON_STOP;
	delay_ms(DELAY_PERIOD);

}
//control the Cannon ready to shoot

void Cannon_down(void)
{

	Cannon_move(ROTATE_CANNON_INIT);
	delay_ms(50);
}

void Cannon_down_slow(void)
{

	u16 i;
	for(i = ROTATE_CANNON_SHOOT; i < (ROTATE_CANNON_INIT - 40); i+= 40)
	{
		Cannon_move(i);
	}
	Cannon_move(ROTATE_CANNON_INIT);

	
}	

void Cannon_ready(void)
{

u16 i;
	for(i = ROTATE_CANNON_INIT; i > (ROTATE_CANNON_SHOOT - 10); i-= 10)
	{
		Cannon_move(i);
	}
	Cannon_move(ROTATE_CANNON_SHOOT);

}

void Hand_ready1(void)			//for temp
{
	rotate_hands_servo_duty = ROTATE_HANDS_READY;
	delay_ms(DELAY_PERIOD);
}

void Hand_up_special(void)
{
	rotate_hands_servo_duty = ROTATE_HANDS_UP_SPECIAL;
	delay_ms(DELAY_PERIOD);
	delay_ms(DELAY_PERIOD);
	delay_ms(250);
}

void Hand_up_special2(void)
{
	rotate_hands_servo_duty = ROTATE_HANDS_UP_SPECIAL_2;
	delay_ms(DELAY_PERIOD);
}

void Cannon_up_special(void)
{
	u16 i;
	for(i = ROTATE_CANNON_INIT; i > (ROTATE_CANNON_SPECIAL - 10); i-= 10)
	{
		Cannon_move(i);
	}
	Cannon_move(ROTATE_CANNON_SPECIAL);
}
///------------------------------------------------------------------------------------------------------///
///-----------------------     3-8 Decoder PWM Generation ISR   -----------------------------------------///
///------------------------------------------------------------------------------------------------------///
ISR(TIMER1_COMPB_vect)
{
	sei();

	PORTB &= 0xE3;				//clear 3 decoder address bits
	PORTB |= (channel << 2);	//select channel

	TIMSK &= 0xF7;				//disable COMPB
	TCCR1A = 0x30;				//Set OC1B on compare match (Setoutput to high level)
	OCR1B = ICR1;
}
