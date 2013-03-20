#include "global.h"

u08 line_tracking(u08 mode_no, u08 speed_den, u08 step_local)
{
	u08 L_speed, R_speed, VR_DETERMINED_speed;
	s08 fro_patt, back_patt, drift, defl;
	s16 diff = 0;
	u08 STEP_flag = 0, flag_local = 0, low_speed_flag = 0;
	u08 side_ball_detected = 0;
	u08 STEP = 0;

	if(step_local == 0)
	{
		return 0;
	}

	ADC_update();	
	delay_ms(20);

	fro_patt = patt_ana(front_sensor);
	back_patt = patt_ana(back_sensor);	
	past_defl = 0;
	past_front = 0;
	past_back = 0;

	VR_DETERMINED_speed = VR[0] / speed_den;

	if (back_patt == NO_LINE && low_speed_flag == 0)
	{
		low_speed_flag = 1;
		VR_DETERMINED_speed = VR[0] / SPEED_DENOMINATOR_VERY_LOW;
	}

	while (1)
	{
		L_speed = LEFT_SPEED_BASE + VR_DETERMINED_speed;
		R_speed = RIGHT_SPEED_BASE + VR_DETERMINED_speed;

		fro_patt = patt_ana(front_sensor);
		back_patt = patt_ana(back_sensor);

//		if(fro_patt == NO_LINE)
		{
//			Motor_stop();
//			break;  
		}

		if (back_patt != NO_LINE && low_speed_flag == 1)
		{
			low_speed_flag = 0;
			VR_DETERMINED_speed = VR[0] / speed_den;
		}

		if(fro_patt < 4 &&  fro_patt > -4)   //front sensor value valid
		{
			past_front = fro_patt;
		}
		else  //front sensor invalid
		{
			fro_patt = past_front;	
		}

		if(back_patt < 4 &&  back_patt > -4)   //back sensor value valid
		{
			past_back = back_patt;
		}
		else  //front sensor invalid
		{
			back_patt = past_back;	
		}


		drift = fro_patt + back_patt;  //for example, when fro = 1, back = -1 (left)
		defl = fro_patt - back_patt;	//drift = 0, defl = 2.`
										//another: fro = 1, back = 0
										//drift = 1, defl = 1

		diff = VR_DETERMINED_speed * (- 15 * drift - 35 * defl - 550 / VR_DETERMINED_speed * (defl - past_defl));

		L_speed = LEFT_SPEED_BASE + VR_DETERMINED_speed - diff / 230; 
		R_speed = RIGHT_SPEED_BASE + VR_DETERMINED_speed;

		if(L_speed > 100)
			L_speed = 100;
		Motor_forward(L_speed, R_speed);
		past_defl = defl;
		
		delay_us(100); // make a little delay 
		
		fro_patt = patt_ana(front_sensor);
		
		if((middle_sensor & 0b00101100) != 0b00000000)
		{
			Motor_stop();
			return FRONT_OBJECT_STOP * 10 + STEP;
		}
		
		if(((front_sensor & 0b10010000) == 0b10010000 || (front_sensor & 0b00001001) == 0b00001001) && STEP_flag == 0) // cross encounter
		{
			delay_ms(5);
			if ((front_sensor & 0b10010000) == 0b10010000 || (front_sensor & 0b00001001) == 0b00001001)
			{
				STEP_flag = 1;
			}
		}

		if(((front_sensor & 0b10010000) != 0b10010000 && (front_sensor & 0b00001001) != 0b00001001) && STEP_flag == 1)
		{
			STEP_flag = 2;
		}

		if((middle_sensor & 0b00000011) != 0 && STEP_flag == 2)
		{
			delay_ms(5);
			if((middle_sensor & 0b00000011) != 0)
			{
				STEP_flag = 0;
				STEP++;
				Map_setposition_front();
			}
		}

		
		if(mode_no == OBJECT_MODE || mode_no == SIDE_OBJECT_MODE)
		{
			if((front_sensor & 0b10000001) != 0 && side_ball_detected == 0)
			{
				if(1 == Golfer_detection())
				{
					side_ball_detected = 1;
				}
			}
		}
		
		if(side_ball_detected == 1)
		{
			Map_setpoint();
			side_ball_detected = 2;
			if(mode_no == SIDE_OBJECT_MODE)
			{
				STEP = step_local;
				Map_setposition_front();
			}
		}						

		////////////////////////////////////////////////
		//step check
		if (step_local == STEP)
		{
			STEP_flag = 3;

			if(flag_local == 0 && (middle_sensor & 0b00000011) != 0b00000000)
			{
				delay_ms(10);
				Motor_stop();
				Motor_backward(VR[0] / ADJUST_SPEED_DENOMINATOR, VR[0] / ADJUST_SPEED_DENOMINATOR);
				while((middle_sensor & 0b00000011) == 0b0000000)
				{
					;
				}
				Motor_stop();
				if(side_ball_detected == 2)
				{
					return SIDE_OBJECT_STOP * 10 + STEP;
				}
				else
				{
					return STEP_STOP * 10 + STEP;
				}				
			}

		}


	} // end of while loop

	Motor_stop();	
	


	return 0;
}

void line_tracking_INTO_GRID(u08 speed_den)
{
	u08 L_speed, R_speed, tracking_speed;
	s08 fro_patt = 0;

	ADC_update();	
	delay_ms(20);

	tracking_speed = VR[0] / speed_den;
	
	while(1)
	{
		fro_patt = patt_ana(front_sensor);
		L_speed = tracking_speed + fro_patt;
		R_speed = tracking_speed - fro_patt;
		
		Motor_forward(R_speed, L_speed);
		delay_us(100);

		if(fro_patt > 4)
		{
			Motor_stop();
			break;
		}
				
	}
	Motor_forward(tracking_speed, tracking_speed);
	while((front_sensor & 0b00111100) != 0);
	Motor_stop();

//	Motor_backward(VR[0] / ADJUST_SPEED_DENOMINATOR, VR[0] / ADJUST_SPEED_DENOMINATOR);
//	while((middle_sensor & 0b00000011) == 0b00000000)
	{
		;
	}
//	while((middle_sensor & 0b00000011) != 0b00000000)
	{
		;
	}
	Motor_stop();
}

void line_tracking_OUT_GRID(u08 speed_den)
{
	u08 L_speed, R_speed, VR_DETERMINED_speed;
	s08 fro_patt = 0;

	ADC_update();	
	delay_ms(20);

	VR_DETERMINED_speed = VR[0] / speed_den;
	
	while(1)
	{
		fro_patt = patt_ana(front_sensor);
		if(fro_patt > 4)
		{
			fro_patt = 0;
		}
		L_speed = LEFT_SPEED_BASE + VR_DETERMINED_speed + fro_patt;
		R_speed = RIGHT_SPEED_BASE + VR_DETERMINED_speed - fro_patt;
		
		Motor_forward(L_speed, R_speed);
		delay_us(100);

		if((middle_sensor & 0b00101100) != 0)
		{
			Motor_stop();
			return;
		}
	}

}
///////////////////////////////////////////////
void line_backward(u08 mode_no, u08 speed_den, u08 step_local)
{
	u08 L_speed, R_speed, VR_DETERMINED_speed;
	s08 fro_patt, back_patt, drift, defl;
	s16 diff = 0;
	u08 STEP = 0, STEP_flag = 0, flag_local = 0;

	if(step_local == 0)
	{
		return;
	}
	
	fro_patt = patt_ana(front_sensor);
	back_patt = patt_ana(back_sensor);	
	past_defl = 0;
	past_front = 0;
	past_back = 0;

	VR_DETERMINED_speed = VR[0] / speed_den;

	while (1)
	{
		L_speed = BACK_LEFT_SPEED_BASE + VR_DETERMINED_speed;
		R_speed = BACK_RIGHT_SPEED_BASE + VR_DETERMINED_speed;

		fro_patt = patt_ana(front_sensor);
		back_patt = patt_ana(back_sensor);
		

		if(fro_patt < 4 &&  fro_patt > -4)   //front sensor value valid
		{
			past_front = fro_patt;
		}
		else  //front sensor invalid
		{
			fro_patt = past_front;	
		}

		if(back_patt < 4 &&  back_patt > -4)   //back sensor value valid
		{
			past_back = back_patt;
		}
		else  //front sensor invalid
		{
			back_patt = past_back;	
		}


		drift = fro_patt + back_patt;  
		defl = back_patt - fro_patt;	


		diff = VR_DETERMINED_speed * (- 15 * drift - 35 * defl - 380 / VR_DETERMINED_speed * (defl - past_defl));

		L_speed = BACK_LEFT_SPEED_BASE + VR_DETERMINED_speed - diff / 210; 
		R_speed = BACK_RIGHT_SPEED_BASE + VR_DETERMINED_speed;
		
		if(L_speed > 100)
			L_speed = 100;

		Motor_backward(L_speed, R_speed);
		past_defl = defl;
		delay_us(100); // make a little delay  

		if(((back_sensor & 0b10010000) == 0b10010000 || (back_sensor & 0b00001001) == 0b00001001) && STEP_flag == 0)
		{
			delay_ms(5);
			if((back_sensor & 0b10010000) == 0b10010000 || (back_sensor & 0b00001001) == 0b00001001)
			{
				STEP_flag = 1;
			}
		
		}

		if(((back_sensor & 0b10010000) != 0b10010000 && (back_sensor & 0b00001001) != 0b00001001) && STEP_flag == 1)
		{
			STEP_flag = 2;
		}

		if((middle_sensor & 0b00000011) != 0 && STEP_flag == 2)
		{
			delay_ms(5);
			if((middle_sensor & 0b00000011) != 0)
			{
				STEP_flag = 0;
				STEP++;
				Map_setposition_back();	
			}
		}

		if (step_local == STEP)
		{
			STEP_flag = 3;

			if(flag_local == 0 && (middle_sensor & 0b00000011) != 0b00000000)
			{
				Motor_stop();
				Motor_forward(VR[0] / ADJUST_SPEED_DENOMINATOR, VR[0] / ADJUST_SPEED_DENOMINATOR);
				while((middle_sensor & 0b00000011) == 0b0000000)
				{
					;
				}
				while((middle_sensor & 0b00000011) != 0b0000000)
				{
					;
				}
				Motor_backward(VR[0] / ADJUST_SPEED_DENOMINATOR, VR[0] / ADJUST_SPEED_DENOMINATOR);
				while((middle_sensor & 0b00000011) == 0b0000000)
				{
					;
				}
				Motor_stop();
				return;				
			}

		}		
	}
	Motor_stop();
}

void line_backward_BACK_TO_GRID(u08 speed_den)
{
	u08 L_speed, R_speed, VR_DETERMINED_speed;
	s08 back_patt = 0;

	ADC_update();	
	delay_ms(20);

	VR_DETERMINED_speed = VR[0] / speed_den;
	
	while(1)
	{
		back_patt = patt_ana(back_sensor);
		L_speed = BACK_LEFT_SPEED_BASE + VR_DETERMINED_speed + back_patt;
		R_speed = BACK_RIGHT_SPEED_BASE + VR_DETERMINED_speed - back_patt;
		
		Motor_backward(L_speed, R_speed);
		delay_us(100);

		if(back_patt > 4)
		{
			Motor_stop();
			break;
		}
				
	}
	
	L_speed = BACK_LEFT_SPEED_BASE + VR_DETERMINED_speed;
	R_speed = BACK_RIGHT_SPEED_BASE + VR_DETERMINED_speed;
	Motor_backward(L_speed, R_speed);

	while(1)
	{
		if((back_sensor & 0b00111100) ==0 )
		{
			Motor_stop();
			break;
		}
	}
	Motor_stop();
}

//////////////////////////////////////////////
s08 patt_ana(u08 sensor_patt)  //positive: left shift
{
	s08 shift;
	switch(sensor_patt)
	{
	case 0b00000000:
		shift = NO_LINE;
		break;

	case 0b00111100:
	case 0b00011000:
	case 0b00001000:
	case 0b00010000:
		shift = NO_SHIFT;
		break;

	case 0b01111000:
	case 0b00111000:
	case 0b00110000:
	case 0b00100000:
		shift = SMALL_SHIFT_RIGHT;
		break;

	case 0b00011110:
	case 0b00011100:
	case 0b00001100:
	case 0b00000100:				
		shift = SMALL_SHIFT_LEFT;
		break;


	case 0b01110000:		
	case 0b01100000:
	case 0b01000000:
		shift = MEDIUM_SHIFT_RIGHT;
		break;

	case 0b00001110:
	case 0b00000110:
	case 0b00000010:
		shift = MEDIUM_SHIFT_LEFT;
		break;

	case 0b10000000:
	case 0b11000000:
	case 0b11100000:
		shift = LARGE_SHIFT_RIGHT;
		break;

	case 0b00000111:
	case 0b00000011:
	case 0b00000001:
		shift = LARGE_SHIFT_LEFT;
		break;

	case 0b01111110:
	case 0b11111111:
	case 0b01111111:
	case 0b11111110:
		shift = CROSS_ENCOUNTER;
		break;
	
	case 0b11110000:	
	case 0b11111000:
	case 0b11111100:
		shift = LEFT_T_ENCOUNTER;
		break;

	case 0b00001111:	
	case 0b00011111:
	case 0b00111111:
		shift = RIGHT_T_ENCOUNTER;
		break;

	default:
		shift = INVALID_SHIFT;
		break;
	} // end of switch
	
	return shift;			
}

//////////////////////////////////////////////
void defl_adjust()
{
	u08 L_speed, R_speed, tracking_speed;
	s08 fro_patt, back_patt, defl;

//first phase
	tracking_speed = VR[0] / SPEED_TURNING_DENOMINATOR;
	L_speed = tracking_speed;
	R_speed = tracking_speed;
	
	fro_patt = patt_ana(front_sensor);
	back_patt = patt_ana(back_sensor);

	if(fro_patt < 4 &&  fro_patt > -4)   //front sensor value valid
	{
	}
	else  //front sensor invalid
	{
		fro_patt = 0;	
	}
	
	if(back_patt < 4 &&  back_patt > -4)   //back sensor value valid
	{
	}
	else  //front sensor invalid
	{
		back_patt = 0;	
	}

	defl = fro_patt - back_patt;

	if(defl < 0) // left deflection
	{
		Motor_TurnLeft(L_speed, R_speed);
	}

	if(defl > 0) //right deflection
	{
		Motor_TurnRight(L_speed, R_speed);
	}

	while(1)
	{
		fro_patt = patt_ana(front_sensor);
		back_patt = patt_ana(back_sensor);


		if(fro_patt < 4 &&  fro_patt > -4)   //front sensor value valid
		{
			;
		}
		else  //front sensor invalid
		{
			Motor_stop();
			return;
		}
	
		if(back_patt < 4 &&  back_patt > -4)   //back sensor value valid
		{
			;
		}
		else  //front sensor invalid
		{
			Motor_stop();
			return;
		}

		defl = fro_patt - back_patt;
		
		if (defl == 0)
			break;
	}
	Motor_stop();

/////////////////////////////////////////////////////////////
///second phase
	tracking_speed = VR[0] / ADJUST_SPEED_DENOMINATOR;
	L_speed = tracking_speed;
	R_speed = tracking_speed;

	fro_patt = patt_ana(front_sensor);
	back_patt = patt_ana(back_sensor);


	if(fro_patt < 4 &&  fro_patt > -4)   //front sensor value valid
	{
	}
	else  //front sensor invalid
	{
		Motor_stop();
		return;	
	}
	
	if(back_patt < 4 &&  back_patt > -4)   //back sensor value valid
	{
	}
	else  //front sensor invalid
	{
//		Motor_TurnRight(13, 13);
//		delay_ms(50);
//		Motor_stop();
		Motor_stop();
		return;	
	}

	defl = fro_patt - back_patt;

	if(defl < 0) // left deflection
	{
		Motor_TurnLeft(L_speed, R_speed);
	}

	if(defl > 0) //right deflection
	{
		Motor_TurnRight(L_speed, R_speed);
	}

	while(1)
	{
		fro_patt = patt_ana(front_sensor);
		back_patt = patt_ana(back_sensor);


		if(fro_patt < 4 &&  fro_patt > -4)   //front sensor value valid
		{
			;
		}
		else  //front sensor invalid
		{
			Motor_stop();
			return;
		}
	
		if(back_patt < 4 &&  back_patt > -4)   //back sensor value valid
		{
			;
		}
		else  //front sensor invalid
		{
			Motor_stop();
			return;
		}

		defl = fro_patt - back_patt;
		
		if (defl == 0)
			break;
	}
	Motor_stop();
}

void Golfer_turn_left()
{
	u08 L_speed, R_speed;
	ADC_update();		//check the VR value
	delay_ms(20);

	L_speed = TURN_LEFT_LEFT_BASE - 2;
	R_speed = TURN_LEFT_RIGHT_BASE + 2;
	Motor_TurnLeft(L_speed, R_speed);		//motor.c
	while(1)
	{
		if((front_sensor & 0b00111100) == 0)
		break;
	}
	while(1)
	{
		if(front_sensor == 0b00111000 || front_sensor == 0b00011000)
		{
			break;
		}
	}
	Motor_stop();
	defl_adjust();

}

void Golfer_turn_left_corner()
{
	u08 L_speed, R_speed;
	ADC_update();		//check the VR value
	delay_ms(20);

	L_speed = TURN_LEFT_LEFT_BASE - 1;
	R_speed = TURN_LEFT_RIGHT_BASE + 0;
	Motor_TurnLeft(L_speed, R_speed);		//motor.c
	while(1)
	{
		if((front_sensor & 0b00011000) == 0)
		break;
	}
	while(1)
	{
		if(front_sensor == 0b00111000 || front_sensor == 0b00011000 || front_sensor == 0b00011100)
		{
			break;
		}
	}
	Motor_stop();
}

void Golfer_turn_left_special()
{
	u08 L_speed, R_speed;
	ADC_update();		//check the VR value
	delay_ms(20);

	L_speed = TURN_LEFT_LEFT_BASE - 2;
	R_speed = TURN_LEFT_RIGHT_BASE + 2;
	Motor_TurnLeft(L_speed, R_speed);		//motor.c

	while(1)
	{
		if(back_sensor==0b00111000 || back_sensor==0b00011100 || back_sensor==0b00011000)
		break;
	}
	Motor_stop();

//	Motor_forward(VR[0] / ADJUST_SPEED_DENOMINATOR, VR[0] / ADJUST_SPEED_DENOMINATOR);
//	while((middle_sensor & 0b00000010) == 0b00000000)
	{
		;
	}
//	Motor_stop();

	Motor_TurnLeft(L_speed - 1, R_speed + 1);
	while(1)
	{
		if((front_sensor & 0b00011000) == 0)
		break;
	}
	while(1)
	{
		if(front_sensor == 0b00111000 || front_sensor == 0b00011000)
		{
			break;
		}
	}
	Motor_stop();
}

void Golfer_turn_right()
{
	u08 L_speed, R_speed;
	ADC_update();		//check the VR value
	delay_ms(20);

	L_speed = TURN_RIGHT_LEFT_BASE;
	R_speed = TURN_RIGHT_RIGHT_BASE;
	Motor_TurnRight(L_speed, R_speed);		//motor.c
	while(1)
	{
		if((front_sensor & 0b00111100) == 0)
		break;
	}
	while(1)
	{
		if(front_sensor == 0b00011100 || front_sensor == 0b00011000)
		{
			break;
		}
	}
	Motor_stop();
	defl_adjust();
}

void Golfer_turn_right_corner()
{
	u08 L_speed, R_speed;
	ADC_update();		//check the VR value
	delay_ms(20);

	L_speed = TURN_RIGHT_LEFT_BASE;
	R_speed = TURN_RIGHT_RIGHT_BASE;
	Motor_TurnRight(L_speed, R_speed);		//motor.c
	while(1)
	{
		if((front_sensor & 0b00011000) == 0)
		break;
	}
	while(1)
	{
		if(front_sensor == 0b00011100 || front_sensor == 0b00011000)
		{
			break;
		}
	}

	Motor_stop();

//	L_speed = TURN_LEFT_LEFT_BASE * 7 / 8;
//	R_speed = TURN_LEFT_RIGHT_BASE * 7 / 8;
//	Motor_TurnLeft(L_speed, R_speed);
//	while(1)
//	{
//		if(front_sensor == 0b00111000 || front_sensor == 0b00011000)
//		break;
//	}	
//	Motor_stop();
}

void Golfer_turn_right_inverse()
{
	u08 L_speed, R_speed;
	ADC_update();		//check the VR value
	delay_ms(20);

	L_speed = TURN_RIGHT_LEFT_BASE - 5;
	R_speed = TURN_RIGHT_RIGHT_BASE + 5;
	Motor_TurnRight(L_speed, R_speed);		//motor.c

	while(1)
	{
		if(back_sensor==0b00111000 || back_sensor==0b00011100 || back_sensor==0b00011000)
		break;
	}
	Motor_stop();
}

void Golfer_backward_p(void)
{
	u08 L_speed, R_speed, VR_DETERMINED_speed;
	ADC_update();		//check the VR value
	delay_ms(20);

	VR_DETERMINED_speed = VR[0]/SPEED_DENOMINATOR_LOW;
		L_speed = BACK_LEFT_SPEED_BASE + VR_DETERMINED_speed;
		R_speed = BACK_RIGHT_SPEED_BASE + VR_DETERMINED_speed;
		Motor_backward(L_speed, R_speed);		//motor.c
		while((middle_sensor & 0b00101100) != 0b00000000)
		{
			;
		}
	Motor_stop();
	return;
}


void Golfer_backward_p2(u08 t)	//for drop
{
	u08 L_speed, R_speed, VR_DETERMINED_speed;
	ADC_update();		//check the VR value
	delay_ms(20);

	VR_DETERMINED_speed = VR[0]/SPEED_DENOMINATOR_LOW;
		L_speed = BACK_LEFT_SPEED_BASE + VR_DETERMINED_speed;
		R_speed = BACK_RIGHT_SPEED_BASE + VR_DETERMINED_speed;

	Motor_backward(L_speed, R_speed);
	delay_ms(t);
	Motor_stop();
}

void Golfer_forward_p(u08 t)
{
	u08 L_speed, R_speed, VR_DETERMINED_speed;
	ADC_update();		//check the VR value
	delay_ms(20);

	VR_DETERMINED_speed = VR[0]/SPEED_DENOMINATOR_LOW;
		L_speed = BACK_LEFT_SPEED_BASE + VR_DETERMINED_speed;
		R_speed = BACK_RIGHT_SPEED_BASE + VR_DETERMINED_speed;

	Motor_forward(L_speed, R_speed);
	delay_ms(t);
	Motor_stop();
}

void Golfer_turn_right_special()
{
	u08 L_speed, R_speed;
	ADC_update();		//check the VR value
	delay_ms(20);

	L_speed = TURN_RIGHT_LEFT_BASE ;
	R_speed = TURN_RIGHT_RIGHT_BASE;
	Motor_TurnRight(L_speed, R_speed + 2);		//motor.c

	while(1)
	{
		if(back_sensor==0b000111000 || back_sensor==0b00111000 || back_sensor==0b00011000)
		break;
	}
	Motor_stop();

//	Motor_forward(VR[0] / ADJUST_SPEED_DENOMINATOR, VR[0] / ADJUST_SPEED_DENOMINATOR);
//	while((middle_sensor & 0b00000001) == 0b00000000)
	{
		;
	}
//	Motor_stop();

	Motor_TurnRight(L_speed + 0, R_speed + 3);
	while(1)
	{
		if(front_sensor==0b00000000 || front_sensor==0b00000001 || front_sensor==0b10000001)
		break;
	}
	while(1)
	{
		if(front_sensor == 0b00011100 || front_sensor == 0b00011000)
		{
			break;
		}
	}
	Motor_stop();
}

void Golfer_turn_right_edge()
{
	u08 L_speed, R_speed, tracking_speed;
	ADC_update();		//check the VR value
	delay_ms(20);

	tracking_speed = VR[0]/SPEED_TURNING_DENOMINATOR;
	L_speed = tracking_speed;
	R_speed = tracking_speed;
	Motor_TurnRight(L_speed, R_speed);		//motor.c
	while(1)
	{
		if(patt_ana(front_sensor) == NO_LINE)
			break;
	}
	while(1)
	{
		if(back_sensor==0b00111000 || back_sensor==0b00011100 || back_sensor==0b00011000)
		break;
	}
	Motor_stop();
}

void Golfer_turn_back()
{
	Golfer_turn_right();
	defl_adjust();
	Motor_backward(VR[0] / ADJUST_SPEED_DENOMINATOR, VR[0] / ADJUST_SPEED_DENOMINATOR);
	while((middle_sensor & 0b00000011) == 0b0000000)
	{
		;
	}
	Golfer_turn_right();
	defl_adjust();
}

void no_line_forward(u08 speed_den)
{
	u08 L_speed, R_speed, VR_DETERMINED_speed, local_counter = 0;
	ADC_update();		//check the VR value
	delay_ms(20);

	VR_DETERMINED_speed = VR[0] / speed_den;

	L_speed = LEFT_SPEED_BASE + VR_DETERMINED_speed - 1;
	R_speed = RIGHT_SPEED_BASE + VR_DETERMINED_speed + 1;

	Motor_forward(L_speed, R_speed);

	while((middle_sensor & 0b00101100) == 0 && local_counter < 100)
	{
		local_counter++;
		delay_ms(5);
	}
	Motor_stop();
}

void no_line_backward(u08 speed_den)
{
	u08 L_speed, R_speed, VR_DETERMINED_speed;
	ADC_update();		//check the VR value
	delay_ms(20);

	VR_DETERMINED_speed = VR[0] / speed_den;

	L_speed = BACK_LEFT_SPEED_BASE + VR_DETERMINED_speed;
	R_speed = BACK_RIGHT_SPEED_BASE + VR_DETERMINED_speed;

	Motor_backward(L_speed,  R_speed);

	while((middle_sensor & 0b00000011) == 0);
	Motor_stop();
	Motor_forward(VR[0] / ADJUST_SPEED_DENOMINATOR , VR[0] / ADJUST_SPEED_DENOMINATOR);
	while((middle_sensor & 0b00000011) == 0b00000000)
	{
		;
	}
	while((middle_sensor & 0b00000011) != 0b00000000)
	{
		;
	}
	Motor_stop();
}

