//map.h

#ifndef __MAP__
#define	__MAP__

/////////
#define MAP_X	6
#define MAP_Y	6

#define POINT1_X	3
#define POINT1_Y	2

#define POINT2_X	2
#define POINT2_Y	3

#define POINT3_X	4
#define POINT3_Y	3


void Map_init(void);
void Map_nextline(void);
void Map_setline(u08 x);
void Map_setpoint(void);
void Map_calculation(u08 x, u08 y);
void Map_setposition_front(void);
void Map_setposition_back(void);
void Map_setgolfer(u08 x, u08 y);
u08 u_abs(u08 input);



////////////////////
 s08 VX;
 s08 VY;
 u08 Map[MAP_X + 1][MAP_Y + 1];
 u08 position_x, position_y, temp_x, temp_y; 
 u08 direction;
 u08 Map_set;


#endif
