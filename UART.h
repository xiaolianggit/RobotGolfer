#ifndef UART_H
#define UART_H


/* ***************************************************************************************************************** //
//	Filename		:	UART.H
//	Title          	:	Library file for ATMega128 UARTs
//	Description		:	Full-function, easy-to-use library file for ATMega128 UARTs.
//	Author			:	Szeto Kwun Kuen
//	Created Date	:	2nd February, 2007
//	Revised Date    :	5th April, 2007
//	Version         :	20070405
//	Editor Tab 		:	4
// ***************************************************************************************************************** */



// ================================================================================================================= //
// =========================                    Step-by-step guide                         ========================= //
// ================================================================================================================= //

//1. include "UART.H" in the program


//2. set the F_CPU (the clock frequency) in the project
//(i.e. 18432000 Hz)


//3. enable UART0 or not
//0 = disable (the functions relating to that UART will be unavailable)
//1 = enable
#define UART_ENABLE 1


//4. set the transmit buffer size
//data are put in the buffer as they send/receive
#define UART_TX_buffer_SIZE 0


//5. set spacer
//e.g. UART_char_SPACER = ' ' gives spacing in front to give "   12"
//e.g. UART_char_SPACER = '0' gives spacing in front to give "00012"
//e.g. UART_char_SPACER = '\0' gives no spacing in front, i.e."12"		(which makes the number unaligned, but useful for sending data across MCU)
#define UART_char_SPACER ' '


//6. set spacer for positive sign
//e.g. UART_char_SIGN = ' ' gives spacing in front to give " 00012"
//e.g. UART_char_SIGN = '+' gives spacing in front to give "+00012"
//e.g. UART_char_SIGN = '\0' gives no spacing in front i.e."00012"		(which makes the number unaligned)
#define UART_char_SIGN '+'


//7. Set the character for logic 1 and 0
//e.g. UART_char_BITCLEAR = '0' gives "01011001"
//e.g. UART_char_BITCLEAR = ' ' gives " 1 11  1"
#define UART_char_BITSET '1'
#define UART_char_BITCLEAR '0'


//8. the functions below are now usable



// ================================================================================================================= //
// =========================                       Public  Functions                       ========================= //
// ================================================================================================================= //

// ----------------------------------------------------------------------------------------------------------------- //
// 	Function		:	void UART_init(unsigned long baud)
//						void UART1_init(unsigned long baud)
// 	Description		:	Initialize UART0 or UART1 if enabled
// 	Var.Access		:	
// 	Pre-req.		:	
// 	Post-req.		:	
// 	Commend			:	
// ----------------------------------------------------------------------------------------------------------------- //
void UART_init(unsigned long baud);


// ----------------------------------------------------------------------------------------------------------------- //
// 	Function		:	void UART_write(char c)
//						void UART1_write(char c)
// 	Description		:	Wait and write a byte to UART
// 	Var.Access		:	
// 	Pre-req.		:	
// 	Post-req.		:	
// 	Commend			:	It will loop infinitely until the buffer is not full.
// ----------------------------------------------------------------------------------------------------------------- //
void UART_write(char c);


// ----------------------------------------------------------------------------------------------------------------- //
// 	Function		:	void UART_putchar(char c)
//						void UART1_putchar(char c)
// 	Description		:	Wait and put a character to UART
//						This function is recommended over UART_write()
// 	Var.Access		:	
// 	Pre-req.		:	
// 	Post-req.		:	
// 	Commend			:	It will loop infinitely until the buffer is not full.
//						The '\n' character will be expended to "\r\n" ("CR-LF")
//						in order to feed a newline
// ----------------------------------------------------------------------------------------------------------------- //
void UART_putchar(char c);


// ----------------------------------------------------------------------------------------------------------------- //
// 	Function		:	void UART_puts(const char *str)
//						void UART1_puts(const char *str)
// 	Description		:	Put a string of character located in RAM
// 	Var.Access		:	
// 	Pre-req.		:	
// 	Post-req.		:	
// 	Commend			:	The '\n' character will be expended to "\r\n" ("CR-LF")
//						in order to feed a newline
// ----------------------------------------------------------------------------------------------------------------- //
void UART_puts(const char *str);


// ----------------------------------------------------------------------------------------------------------------- //
// 	Function		:	void UART_puts_P(const char *str)
//						void UART1_puts_P(const char *str)
// 	Description		:	Put a string of character located in program ROM
// 	Var.Access		:	
// 	Pre-req.		:	
// 	Post-req.		:	
// 	Commend			:	By default, all the "" strings we use are located
//						in RAM. e.g. puts("qwertyuiop"), the string "qwertyuiop"
//						are in RAM even it will never be modified.
//						It is advised to define a macro function
//						"#define puts(str) UART_puts_P(PSTR(str))"
//						to store the program string in ROM to save a lot of RAM.
// ----------------------------------------------------------------------------------------------------------------- //
void UART_puts_P(const char *str);


// ----------------------------------------------------------------------------------------------------------------- //
// 	Function		:	void UART_putbit(bvar, pos)
//						void UART1_putbit(bvar, pos)
// 	Description		:	Put the state of a bit ('0' or '1')
//						bvar = the bit variable
//						pos = the position of the bit in that variable
// 	Var.Access		:	
// 	Pre-req.		:	
// 	Post-req.		:	
// 	Commend			:	
// ----------------------------------------------------------------------------------------------------------------- //
void UART_putbit_u08(unsigned char bvar, unsigned char pos);
void UART_putbit_u16(unsigned int bvar, unsigned char pos);
void UART_putbit_u32(unsigned long bvar, unsigned char pos);


// ----------------------------------------------------------------------------------------------------------------- //
// 	Function		:	void UART_putbits(bvar)
//						void UART1_putbits(bvar)
// 	Description		:	Put the state of all bits ('0' or '1')
// 	Var.Access		:	
// 	Pre-req.		:	
// 	Post-req.		:	
// 	Commend			:	
// ----------------------------------------------------------------------------------------------------------------- //
void UART_putbits_u08(unsigned char bvar);
void UART_putbits_u16(unsigned int bvar);
void UART_putbits_u32(unsigned long bvar);


// ----------------------------------------------------------------------------------------------------------------- //
// 	Function		:	void UART_putnum(num)
//						void UART1_putnum(num)
// 	Description		:	Put the decimal value of a variable
// 	Var.Access		:	
// 	Pre-req.		:	
// 	Post-req.		:	
// 	Commend			:	
// ----------------------------------------------------------------------------------------------------------------- //
void UART_putnum_u08(unsigned char num);
void UART_putnum_s08(signed char num);
void UART_putnum_u16(unsigned int num);
void UART_putnum_s16(signed int num);
void UART_putnum_u32(unsigned long num);
void UART_putnum_s32(signed long num);


// ----------------------------------------------------------------------------------------------------------------- //
// 	Function		:	void UART_puthex(hex)
//						void UART1_puthex(hex)
// 	Description		:	Put the hexadecimal value of a variable
// 	Var.Access		:	
// 	Pre-req.		:	
// 	Post-req.		:	
// 	Commend			:	
// ----------------------------------------------------------------------------------------------------------------- //
void UART_puthex_u08(unsigned char hex);
void UART_puthex_u16(unsigned int hex);
void UART_puthex_u32(unsigned long hex);


// ================================================================================================================= //
// =========================                           Constants                           ========================= //
// ================================================================================================================= //
#define EOF (-1)


#endif
