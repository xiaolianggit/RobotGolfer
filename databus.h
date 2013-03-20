// ******************************************************************************************* //
//
//	Filename		:   Databus.h
//	Title        	:   RoboGolfer databus Header File 
//	Author			:   Fan Wing Sze
//	Description		:   This header file is the databus Header File of the RoboGolfer Project.
//
// ******************************************************************************************* //


#ifndef		__DATABUS_H__
#define		__DATABUS_H__


// ================================================================================================================= //
// =========================                         Constant Define                       ========================= //
// ================================================================================================================= //


// ================================================================================================================= //
// =========================                         Function Prototype                    ========================= //
// ================================================================================================================= //
void Databus_clear(void);				// clear the databus activities
void Motor_update(void);				// update motor
void Sensor_front_update(void);			// read status of front floor sensor
void Sensor_back_update(void);			// read status of back floor sensor
void Sensor_middle_update(void);		// read status of middle floor sensor


// ================================================================================================================= //
// =========================                           Global Variables                    ========================= //
// ================================================================================================================= //
volatile u08 front_sensor, back_sensor, middle_sensor;


#endif
