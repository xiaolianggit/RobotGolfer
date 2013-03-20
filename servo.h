// ******************************************************************************************* //
//
//	Filename		:   Servo.h
//	Title        	:   RoboGolfer Servo Header File 
//	Author			:   Fan Wing Sze
//	Description		:   This file is the Header File of controlling servo
//
// ******************************************************************************************* //


#ifndef		__SERVO_H__
#define		__SERVO_H__


// ================================================================================================================= //
// =========================                         Constant Define                       ========================= //
// ================================================================================================================= //
#define		CANNON_SHOOT				3410		//define the pulse width of left motor pwm to forward  3410
#define		CANNON_STOP					3550		//define the pulse width of left and right motor pwm to stop  3550

#define		HAND_RIGHT_INIT				3900		//define the initialize pulse width of right clip pwm  3431
#define		HAND_RIGHT_CLOSE			2800		//define the pulse width of right clip pwm to "clip close" position  2850
#define		HAND_RIGHT_OPEN				3900		//define the pulse width of right clip pwm to "clip open" position 4250
#define		HAND_RIGHT_PRE_OPEN			2900

#define		HAND_LEFT_INIT				2600		//define the initialize pulse width of left clip pwm  3131
#define		HAND_LEFT_CLOSE				3620		//define the pulse width of left clip pwm to "clip close" position  3600
#define		HAND_LEFT_OPEN				2600		//define the pulse width of left clip pwm to "clip open" position  2605
#define		HAND_LEFT_PRE_OPEN			3500

#define		ROTATE_CANNON_INIT			3550		//define the initialize pulse width of rotate bowl servo  3750
#define		ROTATE_CANNON_LOW_LIMIT		3350		//define the shortest pulse width of rotate bowl servo pwm 4350
#define		ROTATE_CANNON_HIGH_LIMIT	2766		//define the longest pulse width of rotate bowl servo pwm  2766
#define		ROTATE_CANNON_SPECIAL		3150		//3150

#define		ROTATE_HANDS_INIT			1950		//define the initialize pulse width of rotate clip servo  1510  
#define		ROTATE_HANDS_UP				1650		//define the pulse width of the rotate clip servo to upper position  1510
#define 	ROTATE_HANDS_UP_2			900			// 925
#define		ROTATE_HANDS_UP_SPECIAL		1350					// 1300 white ball
#define		ROTATE_HANDS_UP_SPECIAL_2	1050		//1130		//drop
#define		ROTATE_HANDS_DOWN			4120		//define the pulse width of the rotate clip servo to lower position  4205
#define 	ROTATE_HANDS_READY			2250		//before shoot
#define 	ROTATE_HANDS_DROP			1950


#define		ROTATE_CANNON_SHOOT			2840		//shooting within the range of sensor	2830
#define		ROTATE_CANNON_SHOOT_I		2880		//shooting for 1st time

#define		HANDS_CLOSE					0
#define		HANDS_OPEN					1


#define		PWM_1ms						2304
#define		PWM_1_5ms					3456
#define		PWM_2ms						4608


// ================================================================================================================= //
// =========================                         Function Prototype                    ========================= //
// ================================================================================================================= //
void Servo_init(void);				//initialize all the servos when power up
void Hand_close(void);				//control the Clip close
void Hand_open(void);				//control the Clip open
void Hand_up(void);					//control the Rotate Clip Servo up
void Hand_down(void);				//control the Rotate Clip Servo down
void Hand_up_2(void);				//control the Rotate Clip Servo up to put the ball
void Cannon_move(u16 position);
void Cannon_stop(void);				//control the Gun Stop
void Cannon_shoot(void);			//control the Gun Shoot
void Cannon_ready(void);
void Hand_pre_open(void);
void Cannon_down(void);
void Cannon_shoot_only(void);
void Hand_ready1(void);
void Hand_up_special(void);
void Hand_up_special2(void);
void Cannon_up_special(void);
void Hand_drop(void);
void Hand_up_slow(void);
void Cannon_down_slow(void);
// ================================================================================================================= //
// =========================                           Global Variables                    ========================= //
// ================================================================================================================= //
volatile u16 pwm_duty[8];

#define		left_hand_duty				pwm_duty[0]
#define		right_hand_duty				pwm_duty[1]
#define		rotate_hands_servo_duty		pwm_duty[2]
#define		rotate_cannon_servo_duty	pwm_duty[3]
#define		cannon_servo_duty			pwm_duty[4]


#endif
