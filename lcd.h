// ******************************************************************************************* //
//
//	Filename		:   LCD.h
//	Title        	:   RoboGolfer LCD Header File 
//	Author			:   Fan Wing Sze
//	Description		:   This file is the LCD Header File of the RoboGolfer Project.
//
// ******************************************************************************************* //

#ifndef _LCD_H_
#define _LCD_H_


// ================================================================================================================= //
// =========================                         Pin Configuration                     ========================= //
// ================================================================================================================= //
#define		LCDBUS			DATA_OUT
#define		LCDBUS_DIR		DATA_DIR

#define		LCD_EN			PD_5_OUT
#define		LCD_RS			PC_5_OUT
#define		LCD_RW			PC_4_OUT


#define		LCD_startup_delay()		_delay_us(20)
#define		LCD_com_delay()			_delay_ms(10)
#define		LCD_data_delay()		_delay_us(30)
#define		LCD_write_delay()		_delay_us(10)

#define		WAIT_BUSY_FLAG()  		_delay_us(5)


// ================================================================================================================= //
// =========================                         Constant Define                       ========================= //
// ================================================================================================================= //
#define		LCD_COMMAND		0
#define		LCD_DATA		1

#define		LCD_WRITE		0
#define		LCD_READ		1

#define		LCD_ENABLE		1
#define		LCD_DISABLE		0

#define		LCD_LINE1_HOME	0x80
#define		LCD_LINE2_HOME	0xC0


#define		LCD_SHOW_BINARY		1
#define		LCD_SHOW_CHAR		2
#define		LCD_SHOW_U08		3
#define		LCD_SHOW_U16		4


#define		LCD_MENU_PAGE_ONE	1
#define		LCD_MENU_PAGE_TWO	2

#define		LCD_MENU_NOTUPDATE	0x00
#define		LCD_MENU_UPDATING	0xF0
#define		LCD_MENU_UPDATED	0x0F


// ================================================================================================================= //
// =========================                         Function Prototype                    ========================= //
// ================================================================================================================= //
void LCD_init(void);
void LCD_update(void);
void LCD_menu_update(void);
void LCD_menu1_line1(void);
void LCD_menu1_line2(void);


// ================================================================================================================= //
// =========================                           Global Variables                    ========================= //
// ================================================================================================================= //
u08 LCD_menu_selection;		//store the selection of lcd menu
u08 LCD_menu_update_flag;	//store the update status of the lcd menu


#endif
