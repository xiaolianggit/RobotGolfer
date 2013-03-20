//
#ifndef	_MOVING_H_
#define	_MOVING_H_	


/////////////////////////////////////
void test_mode(void);
u08 line_tracking(u08 mode_no, u08 speed_den, u08 step_local);
void line_tracking_INTO_GRID(u08 speed_den);
void line_tracking_OUT_GRID(u08 speed_den);
void line_backward(u08 mode_no, u08 speed_den, u08 step_local);
void line_backward_BACK_TO_GRID(u08 speedd_den);
void defl_adjust();
s08 patt_ana(u08 sensor_patt);
void Golfer_turn_right();
void Golfer_turn_right_corner();
void Golfer_turn_right_special();
void Golfer_turn_right_edge();
void Golfer_turn_right_inverse();
void Golfer_turn_left();
void Golfer_turn_left_corner();
void Golfer_turn_left_special();
void Golfer_turn_left_edge();
void Golfer_turn_back();
void Golfer_backward_p(void);
void Golfer_forward_p(u08 t);
void no_line_forward(u08 speed_den);
void no_line_backward(u08 speed_den);
void Golfer_adjust_left(void);
void Golfer_backward_p2(u08 t);	//for drop

/////////////////////////////////////

#define SPEED_DENOMINATOR   4	//define the denominator to control the motor speed
#define SPEED_TURNING_DENOMINATOR	7	//
#define ADJUST_SPEED_DENOMINATOR	8            //6
#define SPEED_DENOMINATOR_MID	10
#define SPEED_DENOMINATOR_LOW	20
#define SPEED_DENOMINATOR_VERY_LOW	25
//=======================================//

#define LEFT_SPEED_BASE			20
#define RIGHT_SPEED_BASE		19
#define BACK_LEFT_SPEED_BASE	18
#define BACK_RIGHT_SPEED_BASE	21
#define	TURN_LEFT_LEFT_BASE		30
#define TURN_LEFT_RIGHT_BASE	26
#define TURN_RIGHT_LEFT_BASE	27
#define TURN_RIGHT_RIGHT_BASE	25

//tracking mode
#define OBJECT_MODE			7
#define FRONT_OBJECT_MODE	8
#define SIDE_OBJECT_MODE	9

//backward mode
#define BACK_COUNTING		0

//Stop mode:
#define FRONT_OBJECT_STOP	10
#define SIDE_OBJECT_STOP	11
#define STEP_STOP			12
#define NO_LINE_STOP		13
///////////////////////////////////////////
#define adjust_delay		50

//=======================================//
//Direction definition
#define EAST	0
#define NORTH	1
#define WEST	2
#define SOUTH	3
//======================================//
//Define moving constant
#define NO_SHIFT			0
#define SMALL_SHIFT_LEFT	1
#define MEDIUM_SHIFT_LEFT	2
#define LARGE_SHIFT_LEFT	3
#define SMALL_SHIFT_RIGHT	-1
#define MEDIUM_SHIFT_RIGHT	-2
#define LARGE_SHIFT_RIGHT	-3
#define INVALID_SHIFT		10
#define CROSS_ENCOUNTER		11
#define RIGHT_T_ENCOUNTER	12
#define LEFT_T_ENCOUNTER	13
#define NO_LINE				9

s08 past_defl, past_front, past_back;
#endif
