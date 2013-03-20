// ******************************************************************************************* //
//
//	Filename		:   Databus.c
//	Title        	:   RoboGolfer databus File 
//	Author			:   Fan Wing Sze
//	Description		:   This file containing the databus activities of the RoboGolfer Project.
//
// ******************************************************************************************* //

#include "Global.h"


void Databus_clear(void)
{
	PORTB &= 0xFC;						//disable all floor sensors
	PORTD &= 0x1F;
}

void Motor_update(void)
{
	Databus_clear();					//free databus
	DATA_DIR = PORT_OUTPUT;				//set the databus direction to output
	PORTC = motor_dir;
	MOTOR_EN = 0;						//a pulse for enable
	MOTOR_EN = 1;
	MOTOR_EN = 0;
}

void Sensor_front_update(void)
{
	DATA_DIR = PORT_INPUT;				//enable front floor sensor
	FLOOR_FRONT = 0;
	_delay_us(1);
	front_sensor = DATA_IN;
	FLOOR_FRONT = 1;
    u08 i, temp = 0b00000000, mask_1 = 0b00000001, mask_2 = 0b10000000;
    for (i = 0; i < 4; i++)				//switch the sequence of front_sensor
    {
        temp |= ((front_sensor & (mask_1 << i)) << (7 - 2 * i));
        temp |= ((front_sensor & (mask_2 >> i)) >> (7 - 2 * i));
    }
    front_sensor = temp;
}

void Sensor_back_update(void)
{
	DATA_DIR = PORT_INPUT;				//enable back floor sensor
	FLOOR_BACK = 0;
	_delay_us(1);
	back_sensor = DATA_IN;
	FLOOR_BACK = 1;
}

void Sensor_middle_update(void)			//enable on board sensor
{
	DATA_DIR = PORT_INPUT;
	FLOOR_MID = 0;
	_delay_us(1);
	middle_sensor = DATA_IN;
	FLOOR_MID = 1;
}
