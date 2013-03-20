// ******************************************************************************************* //
//
//	Filename		:   Logic.c
//	Title        	:   RoboGolfer Logic File 
//	Description		:   This file is containing the logic and strategy of the RoboGolfer Project.
//
// ******************************************************************************************* //

#include "global.h"

void demo_3(void);
void logic_part1(void);
void logic_part2(void);


//////////////////////////////////TEST_MODE//////////////////////////////////////

 void test_mode(void)
 {



#if 0	
	Golfer_init();
	line_tracking(OBJECT_MODE,SPEED_DENOMINATOR_MID,3);
	Golfer_pickup_special();
	line_tracking(OBJECT_MODE,SPEED_DENOMINATOR_MID,3);
	Golfer_pickup_special();
	line_tracking(OBJECT_MODE,SPEED_DENOMINATOR_MID,3);
	Golfer_drop();
#endif
#if 0	
	Golfer_init();
	line_tracking(OBJECT_MODE,SPEED_DENOMINATOR_MID,3);
	Golfer_pickup_only();
	line_tracking(OBJECT_MODE,SPEED_DENOMINATOR_MID,3);
	Golfer_pickup_only();
	line_tracking(OBJECT_MODE,SPEED_DENOMINATOR_MID,3);
	Golfer_pickup_only();
	line_tracking(OBJECT_MODE,SPEED_DENOMINATOR_MID,1);
	Golfer_shoot();
#endif

	demo_3();
//	no_line_forward(SPEED_DENOMINATOR_LOW);
//	logic_part2();
//	line_tracking(OBJECT_MODE,SPEED_DENOMINATOR_MID,1);
//	Golfer_turn_right_corner();
//	line_tracking(OBJECT_MODE,SPEED_DENOMINATOR_MID,1);
//	Golfer_turn_right();
//	line_tracking_OUT_GRID(SPEED_DENOMINATOR_LOW);
//	line_backward_BACK_TO_GRID(SPEED_DENOMINATOR_LOW);
//	Golfer_turn_right_special();
//	line_tracking(OBJECT_MODE,SPEED_DENOMINATOR_MID,1);
//	Motor_forward(LEFT_SPEED_BASE + 18, RIGHT_SPEED_BASE + 18);
//	Motor_backward(BACK_LEFT_SPEED_BASE + 18, BACK_RIGHT_SPEED_BASE + 18);
//	Motor_TurnLeft(TURN_LEFT_LEFT_BASE, TURN_LEFT_RIGHT_BASE);
//	Motor_TurnRight(TURN_RIGHT_LEFT_BASE, TURN_RIGHT_RIGHT_BASE);
 }
 

 void demo_3(void)
{
	Golfer_init();
	Map_init();

	step = 1;
	sequence = 10;
	line_backward_BACK_TO_GRID(SPEED_DENOMINATOR_LOW);
	Golfer_turn_right_special();
	direction = NORTH;

	logic_part1();
	logic_part2();

}



void logic_part1(void)
{
	//part1
// line1

	step = 4 - position_y;
	result = line_tracking(OBJECT_MODE,SPEED_DENOMINATOR_MID,step);
	if(result/10 ==  FRONT_OBJECT_STOP)
	{
		Golfer_pickup_only();

		step = 4 - position_y;
		line_tracking(OBJECT_MODE,SPEED_DENOMINATOR_MID,step);
	}
	
	if(Map[1][4] > 0)
	{
		sequence = 11;
		step = 1;
		line_backward(BACK_COUNTING,SPEED_DENOMINATOR_MID, step);
		Golfer_turnto(EAST);
		step = 1;
		line_tracking(OBJECT_MODE,SPEED_DENOMINATOR_MID,step);
		Golfer_turnto(NORTH);
		step = 1;
		result = line_tracking(OBJECT_MODE,SPEED_DENOMINATOR_MID,step);
		if(result/10 == FRONT_OBJECT_STOP)
			Golfer_pickup_front();

		if(Ball >= 3)
		{
			Golfer_sendball();
			Golfer_shoot();
			return;
		}
		Golfer_turnto(EAST);

	}else{
		
		Golfer_turn_right_corner();
		direction = EAST;
	}

//line2
	sequence = 20;////////////////
	step = 4 - position_x;
	result = line_tracking(OBJECT_MODE,SPEED_DENOMINATOR_MID,step);

	if(result/10 == FRONT_OBJECT_STOP)
	{
		sequence = 21;///////////////////
		Golfer_pickup_only();

		step = 4 - position_x;
		line_tracking(OBJECT_MODE,SPEED_DENOMINATOR_MID,step);
	}
	if(Map[4][3] > 0)
	{
		sequence = 22;
		step = 1;
		line_backward(BACK_COUNTING,SPEED_DENOMINATOR_MID, step);
		Golfer_turnto(SOUTH);
		step = 1;
		line_tracking(OBJECT_MODE,SPEED_DENOMINATOR_MID,step);
		Golfer_turnto(EAST);
		step = 1;
		result = line_tracking(OBJECT_MODE,SPEED_DENOMINATOR_MID,step);
		if(result/10 == FRONT_OBJECT_STOP)
			Golfer_pickup_front();
				
		if(Ball >= 3)
		{
			Golfer_sendball();
			Golfer_shoot();
			return;
		}

		Golfer_turnto(SOUTH);
		Map_setgolfer(4, 3);
	}else{
		sequence = 23;
		Golfer_turn_right_corner();
		direction = SOUTH;
		Map_setgolfer(4, 4);
	}
	

//line3
	sequence = 30;
	step = position_y - 0;
	result = line_tracking(OBJECT_MODE,SPEED_DENOMINATOR_MID,step);
	if(result/10 ==  FRONT_OBJECT_STOP)
	{
		sequence = 31;
		Golfer_pickup_front();

		if(Ball >= 3)
		{
			Golfer_sendball();
			Golfer_shoot();
			return;
		}

		step = position_y - 0;
		line_tracking(OBJECT_MODE,SPEED_DENOMINATOR_MID,step);
	}
	Golfer_turnto(WEST);
	Map_setgolfer(4, 0);

//line4
	sequence = 40;////////////////////
	
	step = position_x - 1;
	result = line_tracking(OBJECT_MODE,SPEED_DENOMINATOR_MID,step);
	if(result/10 == FRONT_OBJECT_STOP)
	{
		sequence = 41;/////////////
		Golfer_pickup_front();

		if(Ball >= 3)
		{
			Golfer_sendball();
			Golfer_shoot();
			return;
		}

		step = position_x - 1;
		line_tracking(OBJECT_MODE,SPEED_DENOMINATOR_MID,step);
	}
	Map_setgolfer(1, 0);
	if(Map[1][1] > 0)
	{
		sequence = 42;
		step = 1;
		line_backward(BACK_COUNTING, SPEED_DENOMINATOR_MID, step);
		Map_setgolfer(2, 0);
	}
	Golfer_turnto(NORTH);

//
	sequence = 50;
	if(position_x == 2)
	{
		sequence = 51;
		step = 1;
		line_tracking(OBJECT_MODE,SPEED_DENOMINATOR_MID,step);
		Golfer_turnto(WEST);
		step = 1;
		result = line_tracking(OBJECT_MODE,SPEED_DENOMINATOR_MID,step);
		if(result/10 == FRONT_OBJECT_STOP)
			Golfer_pickup_front();
		Golfer_turnto(NORTH);
		
		if(Ball >= 3)
		{
			Golfer_sendball();
			Golfer_shoot();
			return;
		}

	}else{	//position_x == 1
		sequence = 52;
		step = 1;
		line_tracking(OBJECT_MODE,SPEED_DENOMINATOR_MID,step);
	}
	//line5
	sequence = 53;
	step = 3 - position_y;
	result = line_tracking(OBJECT_MODE,SPEED_DENOMINATOR_MID,step);
	if(result/10 == FRONT_OBJECT_STOP)
	{
		Golfer_pickup_front();

		if(Ball >= 3)
		{
			Golfer_sendball();
			Golfer_shoot();
			return;
		}

		step = 3 - position_y;
		result = line_tracking(OBJECT_MODE,SPEED_DENOMINATOR_MID,step);
	}
	Golfer_turnto(EAST);
	step = 1;
	result = line_tracking(OBJECT_MODE,SPEED_DENOMINATOR_MID,step);
	if(result/10 == FRONT_OBJECT_STOP)
	{
		Golfer_pickup_front();

		if(Ball >= 3)
		{
			Golfer_sendball();
			Golfer_shoot();
			return;
		}
	}
	Golfer_turnto(SOUTH);
	
	//line6
	sequence = 60;
	step = position_y - 1;
	result = line_tracking(OBJECT_MODE,SPEED_DENOMINATOR_MID,step);
	if(result/10 == FRONT_OBJECT_STOP)
	{
		Golfer_pickup_front();

		if(Ball >= 3)
		{
			Golfer_sendball();
			Golfer_shoot();
			return;
		}

		step = position_y - 1;
		result = line_tracking(OBJECT_MODE,SPEED_DENOMINATOR_MID,step);
	}
	Golfer_turnto(EAST);

	step = 1;
	result = line_tracking(OBJECT_MODE,SPEED_DENOMINATOR_MID,step);
	if(result/10 == FRONT_OBJECT_STOP)
	{
		Golfer_pickup_front();

		if(Ball >= 3)
		{
			Golfer_sendball();
			Golfer_shoot();
			return;
		}
	}
	Golfer_turnto(NORTH);

	//line7
	sequence = 70;
	step = 3 - position_y;
	result = line_tracking(OBJECT_MODE,SPEED_DENOMINATOR_MID,step);
	if(result/10 == FRONT_OBJECT_STOP)
	{
		Golfer_pickup_front();

		if(Ball >= 3)
		{
			Golfer_sendball();
			Golfer_shoot();
			return;
		}

		step = position_y - 1;
		result = line_tracking(OBJECT_MODE,SPEED_DENOMINATOR_MID,step);
	}
	sequence = 72;
	Golfer_sendball();
	Golfer_shoot();
	return;

	//over
}

void logic_part2(void)		//
{
	
//part2
	//catch the balls in boarder.
	sequence = 180;//////////////////////
	Golfer_turn_left_special();
	direction = WEST;
	Map_setgolfer(4, 4);
	step = position_x - 1;
	result = line_tracking(SIDE_OBJECT_MODE,SPEED_DENOMINATOR_MID, step);

	if((position_x == 1 || position_x == 3) && result/10 == SIDE_OBJECT_STOP)			///with line
	{
		sequence = 181;//////////////////////
		Golfer_turn_right();
		line_tracking(FRONT_OBJECT_MODE, SPEED_DENOMINATOR_MID, 1);
		Golfer_pickup_special();
		line_backward(BACK_COUNTING,SPEED_DENOMINATOR_MID,1);
		position_x--;
		direction = NORTH;
	}else{											//without line
		; //keep going and do nothing
	}
	
	if(position_x == 3)
	{
		Golfer_turnto(WEST);
		step = position_x - 1;
		result = line_tracking(SIDE_OBJECT_MODE,SPEED_DENOMINATOR_MID, step);
	}else if(direction != NORTH){
		step = position_x - 1;
		result = line_tracking(SIDE_OBJECT_MODE,SPEED_DENOMINATOR_MID, step);
	}else{
		result = 10*STEP_STOP;
	}
	

	if(position_x == 1 && result/10 == SIDE_OBJECT_STOP)			///with line
	{
		sequence = 182;//////////////////////
		Golfer_turn_right();
		line_tracking(FRONT_OBJECT_MODE, SPEED_DENOMINATOR_MID, 1);
		Golfer_pickup_special();
		step = 1;
		line_backward(BACK_COUNTING,SPEED_DENOMINATOR_MID,step);
		position_x--;
		direction = NORTH;
	}else{											//without line
		; //keep going and do nothing
	}


	step = position_x - 1;
	line_tracking(SIDE_OBJECT_MODE,SPEED_DENOMINATOR_MID, step);


	if(direction == NORTH)
	{
		step = 1;
		line_backward(BACK_COUNTING,SPEED_DENOMINATOR_MID,step);
	}else{	
		Golfer_turnto(SOUTH);		// (1, 4)
		step = 1;
		line_tracking(FRONT_OBJECT_MODE,SPEED_DENOMINATOR_MID, step);
	}


	sequence = 183;///////////////
	Map[0][5] = 2 - (Map[1][5] + Map[2][5] + Map[3][5]);
	Map_setgolfer(1,3);	

	if(Map[2][5] > 0)
	{
		sequence = 184;
		Golfer_turnto(EAST);
		step = 1;
		line_tracking(FRONT_OBJECT_MODE,SPEED_DENOMINATOR_MID, step);
		Golfer_turnto(NORTH);
		step = 1;
		line_tracking(FRONT_OBJECT_MODE,SPEED_DENOMINATOR_MID, step);
		no_line_forward(SPEED_DENOMINATOR_VERY_LOW);
		Golfer_pickup_special();
		no_line_backward(SPEED_DENOMINATOR_VERY_LOW);
		
		Golfer_turnto(WEST);
		step = 1;
		line_tracking(FRONT_OBJECT_MODE,SPEED_DENOMINATOR_MID, step);
		Golfer_turnto(SOUTH);
		step = 1;
		line_tracking(FRONT_OBJECT_MODE,SPEED_DENOMINATOR_MID, step);
		Map_setgolfer(1, 3);
	}

	if(Map[0][5] > 0)
	{
		sequence = 185;
		Golfer_turnto(WEST);
		step = 1;
		line_tracking(FRONT_OBJECT_MODE,SPEED_DENOMINATOR_MID, step);
		Golfer_turnto(NORTH);
		step = 1;
		line_tracking(FRONT_OBJECT_MODE,SPEED_DENOMINATOR_MID, step);
		no_line_forward(SPEED_DENOMINATOR_VERY_LOW);
		Golfer_pickup_special();
		no_line_backward(SPEED_DENOMINATOR_VERY_LOW);
		Golfer_turnto(EAST);
		step = 1;
		line_tracking(FRONT_OBJECT_MODE,SPEED_DENOMINATOR_MID, step);
		Golfer_turnto(SOUTH);
		step = 1;
		line_tracking(FRONT_OBJECT_MODE,SPEED_DENOMINATOR_MID, step);
		Map_setgolfer(1, 3);
	}
	
	sequence = 190;
	if(direction != NORTH)
	{
		Golfer_turnto(SOUTH);
		step = position_y - 0;
		line_tracking(FRONT_OBJECT_MODE,SPEED_DENOMINATOR_MID, step);
	}else{		// NORTH
		step = position_y - 0;
		line_backward_BACK_TO_GRID(SPEED_DENOMINATOR_LOW);
	}

	Golfer_turnto(WEST);
	step = 1;
	line_tracking(FRONT_OBJECT_MODE,SPEED_DENOMINATOR_MID, step);

	////
	Golfer_turn_left_corner();
	line_tracking_OUT_GRID(SPEED_DENOMINATOR_MID);
	Golfer_drop();
	line_backward_BACK_TO_GRID(SPEED_DENOMINATOR_LOW);
	Golfer_turn_left_special();	

	step = 4;
	direction = EAST;
	line_tracking(FRONT_OBJECT_MODE,SPEED_DENOMINATOR_MID, step);
	Golfer_turnto(NORTH);
	step = 3 - position_y;
	line_tracking(SIDE_OBJECT_MODE,SPEED_DENOMINATOR_MID, step);

	if(position_y == 2)
	{
		sequence = 191;
		Golfer_turn_right();
		line_tracking(FRONT_OBJECT_MODE, SPEED_DENOMINATOR_MID, 1);
		Golfer_pickup_special();
		step = 1;
		line_backward(BACK_COUNTING,SPEED_DENOMINATOR_MID,step);
		position_y++;
		Golfer_turn_left();
	}

	step = 3 - position_y;
	line_tracking(FRONT_OBJECT_MODE,SPEED_DENOMINATOR_MID, step);
	
	if(position_y == 2)
	{
		sequence = 191;
		Golfer_turn_right();
		line_tracking(FRONT_OBJECT_MODE, SPEED_DENOMINATOR_MID, 1);
		Golfer_pickup_special();
		step = 1;
		line_backward(BACK_COUNTING,SPEED_DENOMINATOR_MID,step);
		position_y++;
		Golfer_turn_left();
	}
	
	step = 3 - position_y;
	line_tracking(FRONT_OBJECT_MODE,SPEED_DENOMINATOR_MID, step);
	
	step = 1;
	line_backward(BACK_COUNTING,SPEED_DENOMINATOR_MID,step);
	Golfer_turnto(WEST);

	Map_setgolfer(4, 2);
	
	Map[5][0] = 2 - (Map[5][1] + Map[5][2] + Map[5][3]);

	if(Map[5][3] > 0)
		{
			Golfer_turnto(WEST);
			step = 1;
			line_tracking(FRONT_OBJECT_MODE,SPEED_DENOMINATOR_MID, step);
			Map_setgolfer(3 ,2);
			
			Golfer_turnto(NORTH);
			step = 1;
			line_tracking(FRONT_OBJECT_MODE,SPEED_DENOMINATOR_MID, step);
			Golfer_turnto(EAST);
			step = 1;
			line_tracking(FRONT_OBJECT_MODE,SPEED_DENOMINATOR_MID, step);
			no_line_forward(SPEED_DENOMINATOR_VERY_LOW);
			Golfer_pickup_special();
			no_line_backward(SPEED_DENOMINATOR_VERY_LOW);
			Golfer_turnto(SOUTH);
			step = 1;
			line_tracking(FRONT_OBJECT_MODE,SPEED_DENOMINATOR_MID, step);
			Map_setgolfer(4, 2);
		}	
	
	if(Map[5][1] > 0)
	{
		
		if(position_x == 4)
		{
			Golfer_turnto(WEST);
			step = 1;
			line_tracking(FRONT_OBJECT_MODE,SPEED_DENOMINATOR_MID, step);
		}
		Golfer_turnto(SOUTH);
		step = 1;
		line_tracking(FRONT_OBJECT_MODE,SPEED_DENOMINATOR_MID, step);
		Golfer_turnto(EAST);
		step = 1;
		line_tracking(FRONT_OBJECT_MODE,SPEED_DENOMINATOR_MID, step);
		no_line_forward(SPEED_DENOMINATOR_VERY_LOW);
		Golfer_pickup_special();
		no_line_backward(SPEED_DENOMINATOR_VERY_LOW);
		Golfer_turnto(SOUTH);
		step = 1;
		line_tracking(FRONT_OBJECT_MODE,SPEED_DENOMINATOR_MID, step);
		Map_setgolfer(4, 0);
	}

	
	if(Map[5][0] > 0)
	{
		if(position_y == 2)  //(4,2)
		{
			Golfer_turnto(SOUTH);
			step = position_y - 0;
			line_tracking(FRONT_OBJECT_MODE,SPEED_DENOMINATOR_MID, step);
			Golfer_turnto(EAST);
			step = 1;
			line_tracking(FRONT_OBJECT_MODE,SPEED_DENOMINATOR_MID, step);
			Golfer_pickup_special();
			step = 1;
			line_backward(BACK_COUNTING,SPEED_DENOMINATOR_MID,step);
			Golfer_turnto(NORTH);
			Map_setgolfer(4,0);
		
		}else{		//(4,0)
			Golfer_turnto(EAST);
			step = 1;
			line_tracking(FRONT_OBJECT_MODE,SPEED_DENOMINATOR_MID, step);
			Golfer_pickup_special();
			step = 1;
			line_backward(BACK_COUNTING,SPEED_DENOMINATOR_MID,step);
			Golfer_turnto(NORTH);
			Map_setgolfer(4,0);
		}
	}

		if(position_y == 2)		//(4, 2)
		{
			Golfer_turnto(SOUTH);
			step = position_y - 0;
			line_tracking(FRONT_OBJECT_MODE,SPEED_DENOMINATOR_MID, step);
		}
	
		Golfer_turnto(WEST);
		step = position_x - 0;
		line_tracking(FRONT_OBJECT_MODE,SPEED_DENOMINATOR_MID, step);

		Golfer_turn_left_corner();
		line_tracking_OUT_GRID(SPEED_DENOMINATOR_MID);
		Golfer_drop();
		line_backward_BACK_TO_GRID(SPEED_DENOMINATOR_LOW);
		Golfer_turn_left_special();	
}



