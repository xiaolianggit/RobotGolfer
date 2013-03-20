//

#include "global.h"


void Map_init(void)
{
	//initial array
	u08 i,j;
	for(i=0; i<MAP_X; i++)
		for(j=0; j<MAP_Y; j++)
		Map[i][j]=0;
}

void Map_setpoint(void)
{
	if(direction == NORTH)
		Map[position_x + 1][position_y + 1] = 1;
	
	if(direction == EAST)
		Map[position_x + 1][position_y - 1] = 1;

	if(direction == SOUTH)
		Map[position_x - 1][position_y - 1] = 1;

	if(direction == WEST)
		Map[position_x - 1][position_y + 1] = 1;

	Map_set++;
}

void Map_setposition_back(void)
{
	if(direction == NORTH)
		position_y--;
	
	if(direction == EAST)
		position_x--;

	if(direction == SOUTH)
		position_y++;

	if(direction == WEST)
		position_x++;
}

void Map_setposition_front(void)
{
	if(direction == NORTH)
		position_y++;
	
	if(direction == EAST)
		position_x++;

	if(direction == SOUTH)
		position_y--;

	if(direction == WEST)
		position_x--;
}

void Map_setgolfer(u08 x, u08 y)
{
	position_x = x;
	position_y = y;
}

