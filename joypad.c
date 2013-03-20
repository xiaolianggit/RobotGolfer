// ******************************************************************************************* //
//
//	Filename		:   Joypad.c
//	Title        	:   RoboGolfer joypad File 
//	Author			:   Fan Wing Sze
//	Description		:   This file is reading the joypad of the RoboGolfer Project.
//
// ******************************************************************************************* //

#include "Global.h"

volatile u08 joypad_switch;
volatile u08 D_Flip_Flop = 0;


//update selected switches on joypad
void get_switch(u08 channel)
{
	u08 pattern = (0x11<<channel);
	u08 pattern_high = (0x10<<channel);
	u08 pattern_low = (0x01<<channel);

	joypad_switch &= (~pattern);

	D_Flip_Flop &= JOYPAD_MASK;
	D_Flip_Flop |= channel;

	Databus_clear();
	DATA_DIR = PORT_OUTPUT;

	JOYPAD_SELECT = D_Flip_Flop;
	cli();
	JOYPAD_EN = 1;
	JOYPAD_EN = 0;
	sei();

	if(JOYPAD_IN_1)
		joypad_switch |= pattern_high;

	if(JOYPAD_IN_2)
		joypad_switch |= pattern_low;
}

//update all the switches on joypad
void update_switch(void)
{
	u08 pattern_high = 0x80;
	u08 pattern_low = 0x08;

	u08 select_channel = 0;

	joypad_switch = 0;
	
	Databus_clear();
	DATA_DIR = PORT_OUTPUT;

	while(select_channel < 4)
	{
		D_Flip_Flop &= JOYPAD_MASK;
		D_Flip_Flop |= select_channel;	//select the channel of multiplexer
		
		JOYPAD_SELECT = D_Flip_Flop;
		cli();							// avoid global interrupt
		JOYPAD_EN = 1;
		JOYPAD_EN = 0;					//trigger the flip flop (74HC574)
		sei();							// re-enable global interrupt
		
		_delay_us(1);

		if(JOYPAD_IN_1)
			joypad_switch |= pattern_high;
		pattern_high >>= 1;
		
		if(JOYPAD_IN_2)
			joypad_switch |= pattern_low;
		pattern_low >>=1;

		select_channel++;
	}
}
