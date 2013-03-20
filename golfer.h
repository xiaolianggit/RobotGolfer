//

#ifndef		__GOLFER__
#define		__GOLFER__

//////////////////////////
#define DISTANCE_1	100	//
#define DISTANCE_2	100	//
						//
//////////////////////////
#define BALL_NUM	4

void Golfer_pickball(void);	//
void Golfer_pickup_front(void);	// 
u08 Golfer_detection(void);
void Golfer_sendball(void); //
void Golfer_shoot(void);	//
void Golfer_init(void);		//
void Golfer_goto(u08 destination_x, u08 destination_y); //
void Golfer_adjust_right(void);
void Golfer_pickup_only(void);
void Golfer_shoot_only(void);
void Golfer_turnto(u08 d);
void Golfer_pickup_fast(void);
void Golfer_pickup_special(void);
void Golfer_drop(void);
u08 Ball, shooted_ball, Ball_left; 
u08 detection_flag, result, step;
u08 result_flag;
u08 sequence;
#endif
