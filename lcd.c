// ******************************************************************************************* //
//
//	Filename		:   LCD.c
//	Title        	:   RoboGolfer lcd File 
//	Author			:   Fan Wing Sze
//	Description		:   This file is controlling the lcd of RoboGolfer
//
// ******************************************************************************************* //

#include "Global.h"


u08 lcd_binary_data[8];
u08 lcd_print_data[16];


///------------------------------------------------------------------------------------------------------///
///----------------------------     BASIC FUNCTIONS   ---------------------------------------------------///
///------------------------------------------------------------------------------------------------------///

//write data to lcd through 4 bit communication
//the timing diagram can refer to LCD datasheet
void lcd_write_4b(u08 data, u08 data_type)
{
	LCDBUS_DIR = 0xFF;
	LCDBUS = 0;
	LCD_RS = data_type;
	LCD_RW = LCD_WRITE;
    LCD_EN = LCD_DISABLE;
	LCD_EN = LCD_ENABLE;
	LCDBUS |= (data&0x0F);	   
	LCD_write_delay();
	LCD_EN = LCD_DISABLE;
}


//convert the 8 bit data to 4 bit data and send to lcd
void LCD_write(u08 data, u08 data_type)
{
	Databus_clear();
	lcd_write_4b( ((data&0xF0)>>4), data_type);
	lcd_write_4b( (data&0x0F), data_type);
}

//initialize the lcd when power up
//the initialize sequence can be refered to the LCD datasheet
void LCD_init(void)
{
    Databus_clear();
	LCDBUS = PORT_OUTPUT;
	delay_ms(50);       				// Wait VCC is rise

	LCD_write(0x00, LCD_COMMAND);
	LCD_startup_delay();
	LCD_write(0x00, LCD_COMMAND);
	LCD_startup_delay();
	LCD_write(0x00, LCD_COMMAND);
	LCD_startup_delay();
	LCD_write(0x00, LCD_COMMAND);
	LCD_startup_delay();

	LCD_write(0x28, LCD_COMMAND);       // Function Set
	LCD_com_delay();
	LCD_write(0x0C, LCD_COMMAND);       // Display ON/OFF	
	LCD_com_delay();
	LCD_write(0x06, LCD_COMMAND);       // Entry Mode set
	LCD_com_delay();
	LCD_write(0x01, LCD_COMMAND);       // Display Clear
	LCD_com_delay();

	LCD_menu_selection = LCD_MENU_PAGE_ONE;
	LCD_menu1_line1();				//display line 1 of lcd menu 1
	_delay_us(30);
	LCD_menu1_line2();				//display line 2 of lcd menu 1
}

///------------------------------------------------------------------------------------------------------///
///----------------------------     CONTROL FUNCTIONS   -------------------------------------------------///
///------------------------------------------------------------------------------------------------------///

void LCD_home(u08 line)
{
	LCD_write(line, LCD_COMMAND);
	LCD_data_delay();
}

//convert the unsigned char variable into binary format
void u08tobinary(u08 data)
{
	u08 i, bit_pos=0x80;
	for (i=0;i<8;i++)
	{
	    if((data&bit_pos) !=0)
			lcd_binary_data[i] = '1';
		else
			lcd_binary_data[i] = '0';

		bit_pos=bit_pos>>1;
	}	
}

//convert the unsigned char variable into string format
void u08toStr(u08 value)
{
	lcd_binary_data[0] = value/100+'0';
	value = value%100;
	lcd_binary_data[1] = value/10+'0';
	value = value%10;
	lcd_binary_data[2] = value+'0';
	u08 i;
	for(i=3;i<8;i++)
	{
		lcd_binary_data[i] = ' ';
	}
}

//convert the unsigned int variable into string format
void u16toStr(u16 value)
{
	lcd_binary_data[0] = value/10000+'0';
	value = value%10000;
	lcd_binary_data[1] = value/1000+'0';
	value = value%1000;
	lcd_binary_data[2] = value/100+'0';
	value = value%100;
	lcd_binary_data[3] = value/10+'0';
	value = value%10;
	lcd_binary_data[4] = value+'0';
	u08 i;
	for(i=5;i<8;i++)
	{
		lcd_binary_data[i] = ' ';
	}
}

//Display the data to the lcd, for specific start position and end position
void print_data(u08 start_pos, u08 stop_pos)
{
	u08 i, number_of_display;
	if(stop_pos >= start_pos)
		number_of_display = stop_pos - start_pos + 1;
	else
		return;
	for(i=0;i<number_of_display;i++)
	{
		LCD_write(lcd_print_data[start_pos+i], LCD_DATA);
		LCD_data_delay();
	}
}

//update part one of the lcd data
void LCD_data_update(u08 start_pos, u16 data, u08 type)
{
	if(type == LCD_SHOW_BINARY)
	{
		u08tobinary(data);
	}
	else if(type == LCD_SHOW_U08)
	{
		u08toStr(data);
	}
	else if(type == LCD_SHOW_U16)
	{
		u16toStr(data);
	}
	else
	{
		return;
	}
	u08 i;
	for(i=0;i<8;i++)
	{
		lcd_print_data[i] = lcd_binary_data[i];
	}
	LCD_write(start_pos, LCD_COMMAND);
	LCD_data_delay();
	print_data(0, 7);
}

//update the lcd data, which is periodically called from schedular
void LCD_update(void)
{
	if(LCD_menu_selection == LCD_MENU_PAGE_ONE)					//check whether the lcd menu selection is page one
	{
		if(task_schedule == 4)				//check whether part 1 is updated
		{
		//	LCD_data_update(0x84, shooted_ball, LCD_SHOW_U08);
		//  LCD_data_update(0x84, sequence, LCD_SHOW_U08);
		//	LCD_data_update(0x84, position_x, LCD_SHOW_U08);	//update line 1 part 1
		//	LCD_data_update(0x84, position_y, LCD_SHOW_U08);
			LCD_data_update(0x84, front_sensor, LCD_SHOW_BINARY);
		//	LCD_data_update(0x84, result, LCD_SHOW_U08);

		}
		else if(task_schedule == 5)			//part 2 will be updated after part 1 is updated
		{
		//	LCD_data_update(0xC4, Map_set, LCD_SHOW_U08);
		//	LCD_data_update(0xC4, position_x, LCD_SHOW_U08);
			LCD_data_update(0xC4, back_sensor, LCD_SHOW_BINARY);
		//	LCD_data_update(0xC4, step, LCD_SHOW_U08);
		//	LCD_data_update(0xC4, Ball_left, LCD_SHOW_U08);
		//	LCD_data_update(0xC4, Ball, LCD_SHOW_U08);
		}
	}
	else														//update page two if the lcd menu selection is page two
	{
		if(task_schedule == 4)				//check whether part 1 is updated
		{
		//	LCD_data_update(0x84, position_x, LCD_SHOW_U08);													//update part 1
		//	LCD_data_update(0x84, step, LCD_SHOW_U08);
			LCD_data_update(0x84, middle_sensor, LCD_SHOW_BINARY);
		//	LCD_data_update(0x84, Ball_left, LCD_SHOW_U08);

		}
		else if(task_schedule == 5)			//part 2 will be updated after part 1 is updated
		{
		//LCD_data_update(0xC4, middle_sensor, LCD_SHOW_BINARY);
		//	LCD_data_update(0xC4, position_y, LCD_SHOW_U08);
		//	LCD_data_update(0xC4, STEP, LCD_SHOW_U08);
			LCD_data_update(0xC4, IR, LCD_SHOW_U08);
		//	LCD_data_update(0xC4, VR[0], LCD_SHOW_U08);

		}
	}
}

///------------------------------------------------------------------------------------------------------///
///----------------------------     MENU FUNCTIONS   ----------------------------------------------------///
///------------------------------------------------------------------------------------------------------///

void LCD_menu1_line1(void)
{
	LCD_write(LCD_LINE1_HOME, LCD_COMMAND);
	LCD_data_delay();
	LCD_write('C', LCD_DATA);   
	LCD_data_delay();
	LCD_write(':', LCD_DATA); 
	LCD_data_delay();
	LCD_write(' ', LCD_DATA); 
}

void LCD_menu1_line2(void)
{
	LCD_write(LCD_LINE2_HOME, LCD_COMMAND);
	LCD_data_delay();
	LCD_write('L', LCD_DATA);   
	LCD_data_delay();
	LCD_write(':', LCD_DATA);
	LCD_data_delay();
	LCD_write(' ', LCD_DATA); 
}

void LCD_menu2_line1(void)
{
	LCD_write(LCD_LINE1_HOME, LCD_COMMAND);
	LCD_data_delay();
	LCD_write('M', LCD_DATA);   
	LCD_data_delay();
	LCD_write(':', LCD_DATA); 
	LCD_data_delay();
	LCD_write(' ', LCD_DATA); 
}

void LCD_menu2_line2(void)
{
	LCD_write(LCD_LINE2_HOME, LCD_COMMAND);
	LCD_data_delay();
	LCD_write('V', LCD_DATA);  
	LCD_data_delay();
	LCD_write('R', LCD_DATA);
	LCD_data_delay();
	LCD_write('0', LCD_DATA);
	LCD_data_delay();
	LCD_write(' ', LCD_DATA); 
//	LCD_write(0xC8, LCD_COMMAND);
//	LCD_write('I', LCD_DATA);  
//	LCD_data_delay();
//	LCD_write('R', LCD_DATA);
//	LCD_data_delay();
//	LCD_write(':', LCD_DATA);
//	LCD_data_delay();
//	LCD_write(' ', LCD_DATA); 
}

//update the lcd menu
//this function would be called whenever the button S2 is pressed
void LCD_menu_update(void)
{
	if(LCD_menu_selection == LCD_MENU_PAGE_ONE)					//check whether the lcd menu selection is page one
	{
		if(task_schedule == 6)
		{
			LCD_menu2_line1();								//lcd menu two line 1 is updated
			LCD_menu_update_flag = LCD_MENU_UPDATING;
		}
		else if(task_schedule == 7)
		{
			LCD_menu2_line2();								//lcd menu two line 2 is updated
			LCD_menu_selection = LCD_MENU_PAGE_TWO;
			LCD_menu_update_flag = LCD_MENU_UPDATED;
		}
	}
	else														//the lcd menu selection is page two
	{
		if(task_schedule == 6)
		{
			LCD_menu1_line1();								//lcd menu one line 1 is updated
			LCD_menu_update_flag = LCD_MENU_UPDATING;
		}
		else if(task_schedule == 7)
		{
			LCD_menu1_line2();								//lcd menu one line 2 is updated
			LCD_menu_selection = LCD_MENU_PAGE_ONE;
			LCD_menu_update_flag = LCD_MENU_UPDATED;
		}
	}
}

