// ******************************************************************************************* //
//
//	Filename		:   adc.c
//	Title        	:   RoboGolfer ADC File 
//	Author			:   Fan Wing Sze
//	Description		:   This file containing the analog to digital functions of the RoboGolfer Project.
//
// ******************************************************************************************* //

#include "Global.h"


//initialize the adc when power up
//Enable ADC and set the division to 128
//please read p.198 to p.215 of ATMega 16 datasheet for details
void ADC_init(void)
{	
	ADMUX = 0b00100000;
	ADCSRA = 0b10000111;
}

//Convert the VR voltage to digital voltage
//you can edit it for reading other adc channels
//please read p.211 to p.214 of ATMega 8535 datasheet for details
void ADC_update(void)
{
	u08 adc_wait=1;

	
	ADMUX = 0b00100000;				//select channel IR
	ADCSRA |= _BV(ADSC);			//start conversion of adc
	do {
		adc_wait = ADCSRA;
		adc_wait &= 0b01000000;
	} while(adc_wait != 0);			//wait until the conversion finish
	IR = ADCH;	

	adc_wait = 1;
	ADMUX = 0b00100011;				//select channel
	ADCSRA |= _BV(ADSC);			//start conversion of adc
	do {
		adc_wait = ADCSRA;
		adc_wait &= 0b01000000;
	} while(adc_wait != 0);			//wait until the conversion finish
	VR[1] = ADCH;					//store the value to adc_value

	adc_wait = 1;
	
	ADMUX = 0b00100010;				//select channel
	ADCSRA |= _BV(ADSC);			//start conversion of adc
	do {
		adc_wait = ADCSRA;
		adc_wait &= 0b01000000;
	} while(adc_wait != 0);			//wait until the conversion finish
	VR[0] = ADCH;					//store the value to adc_value


}

void IR_update(void)
{
	u08 adc_wait=1;

	
	ADMUX = 0b00100000;				//select channel IR
	ADCSRA |= _BV(ADSC);			//start conversion of adc
	do {
		adc_wait = ADCSRA;
		adc_wait &= 0b01000000;
	} while(adc_wait != 0);			//wait until the conversion finish
	IR = ADCH;	
}
