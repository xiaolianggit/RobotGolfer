#include "global.h"



u08 Golfer_detection(void)
{
	IR_update();
	if(IR > DISTANCE_1)
		return 1;
	return 0;
}

void Golfer_init(void)
{
	direction = EAST;
	position_x = 0;
	position_y = 0;
	Ball = 0;
	shooted_ball = 0;
	Map_set = 0;
//	Cannon_move(4000);
}

void Golfer_pickup_fast(void)
{
	Hand_close();
	if(Ball == 0)
	{
		Hand_up_2();
		delay_ms(50);
		Hand_pre_open();
		delay_ms(50);	
		Hand_up();
		Hand_open();
		Cannon_ready();
		Ball++;
	}else{
		Hand_up();
		Ball++;
	}

}

void Golfer_pickup_special(void)
{
	Golfer_backward_p();
	Golfer_forward_p(70);
	Hand_down();
	Hand_close();
	delay_ms(100);
	if(Ball == 0)
	{
		Hand_up_special();
		Hand_open(); 
		Ball++;
	}else{
		Hand_up_special();
		Ball++;
	}
}
void Golfer_drop(void)
{
	Golfer_forward_p(250);
	//Golfer_forward_p(250);
	Hand_drop();
	delay_ms(20);
	Hand_open();
	delay_ms(250);
	Ball--;
	///////////
	Golfer_backward_p2(150);
	Cannon_up_special();
	Hand_up_special2();
	delay_ms(250);

	
	Hand_pre_open();	
	delay_ms(250);
	Cannon_down();
	Hand_close();
	Golfer_forward_p(180);
	Hand_drop();
	delay_ms(20);
	Hand_open();
	Ball--;

}


void Golfer_pickup_only(void)
{
	Golfer_backward_p();
	Golfer_forward_p(70);
//	defl_adjust();
	Hand_down();
	Hand_close();
	if(Ball == 0)
	{
		Hand_up_2();
		delay_ms(50);
		Hand_pre_open();
		delay_ms(50);	
		Hand_up();
		Hand_open();
		//Cannon_ready();
		Ball++;
	}else if(Ball == 2){
		Hand_up();
		Ball++;
	}else{	//ball == 1
		Hand_up_special();
		Hand_open(); 
		Ball++;
	}
}

void Golfer_pickup_front(void)
{

	Golfer_backward_p();
	Golfer_forward_p(70);
//	defl_adjust();

	Hand_down();
	Hand_close();
	if(Ball == 0)
	{
		Hand_up_2();
		delay_ms(50);
		Hand_pre_open();
		delay_ms(50);	
		Hand_up();
		Hand_open();
	//	Cannon_ready();
		Ball++;
	}else if(Ball == 2){
		Hand_up();
		Ball++;
	}else{	//ball == 1
		Hand_up_special();
		Hand_open(); 
		Ball++;
	}
	defl_adjust();
	step = 1;
	line_tracking(FRONT_OBJECT_MODE,SPEED_DENOMINATOR_MID,step);
}


void Golfer_shoot(void)
{
	
	if(direction == SOUTH || direction == EAST)
		Golfer_turn_left_corner();
	if(direction == NORTH || direction == WEST)
		Golfer_turn_right_corner();

	line_tracking_OUT_GRID(SPEED_DENOMINATOR_LOW);
	Golfer_backward_p();	///////
	defl_adjust();
	Golfer_adjust_right();

	Hand_ready1();

	Cannon_ready();
	Cannon_move(ROTATE_CANNON_SHOOT_I);
	delay_ms(250);
	delay_ms(250);
	Cannon_shoot();					//shoot the 1st ball
	Cannon_stop();
	Ball--;
	shooted_ball++;
			//shoot the 2nd ball
	Hand_up_slow();
	Cannon_down_slow();
	delay_ms(50);
	Cannon_ready();
	Hand_ready1();


	delay_ms(250);
	delay_ms(250);
	Cannon_shoot();					//shoot the 2nd ball
	Cannon_stop();
	Ball--;
	shooted_ball++;
			//shoot the 3rd ball
	Hand_ready1();
	Cannon_down();
	delay_ms(50);

	Hand_up_2();
	delay_ms(50);
	Hand_pre_open();
	delay_ms(50);	
	Hand_up();
	Hand_open();
	Hand_ready1();
	Cannon_ready();
//special
	Hand_pre_open();
	Hand_up_slow();
	Cannon_down_slow();
	delay_ms(50);
	
	Cannon_ready();	
	Hand_ready1();
	Hand_open();


	delay_ms(250);
	delay_ms(250);
	Cannon_shoot();
	Cannon_stop();
	Cannon_move(ROTATE_CANNON_INIT);
	Ball--;	
	shooted_ball++;	
	Ball = 0;	
//	Golfer_adjust_left();
	defl_adjust();
	step = 1;
	line_backward_BACK_TO_GRID(SPEED_DENOMINATOR_LOW);//go back
}

void Golfer_sendball(void)
{
	if(direction != SOUTH)
	{
		Golfer_turnto(NORTH);
		step = (4 - position_y);
		line_tracking(FRONT_OBJECT_MODE, SPEED_DENOMINATOR_MID, step);
	}else{
		step = (4 - position_y);
		line_backward(BACK_COUNTING, SPEED_DENOMINATOR_MID, step);
	}
	
	Golfer_turnto(EAST);
	step = (4 - position_x);
	line_tracking(FRONT_OBJECT_MODE, SPEED_DENOMINATOR_MID, step);
	//not finish yet!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}

void Golfer_turnto(u08 d)
{
	switch (d-direction)
	{
	default:	break;
	case 0:	
			return; break; 
	case 1:
	case -3:
			Golfer_turn_left(0);
			break;
	case -2:
	case 2: 
			Golfer_turn_back();
			break;
	case 3:
	case -1: 
			Golfer_turn_right(0);
			break;
	}
	direction = d;
}

void Golfer_adjust_right(void)
{
	 u08 delay_time;
	 Motor_TurnRight((VR[0] / ADJUST_SPEED_DENOMINATOR), (VR[0] / ADJUST_SPEED_DENOMINATOR));
	 
	 	delay_time = 100;			//150
	 
	 
	 delay_ms(delay_time);
	 Motor_stop();
}


void Golfer_adjust_left(void)
{
	u08 delay_time;
	Motor_TurnLeft((VR[0] / ADJUST_SPEED_DENOMINATOR), (VR[0] / ADJUST_SPEED_DENOMINATOR));
	delay_time = 180;
	delay_ms(delay_time);
	Motor_stop();
}
