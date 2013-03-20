/* ***************************************************************************************************************** //
//	Filename		:	UART.C
//	Title          	:	Library file for ATMega128 UARTs
//	Description		:	Full-function, easy-to-use library file for ATMega128 UARTs.
//	Author			:	Szeto Kwun Kuen
//	Created Date	:	2nd February, 2007
//	Revised Date    :	15th February, 2007
//	Version         :	20070215
//	Editor Tab 		:	4
// ***************************************************************************************************************** */

#include "UART.H"
#include <AVR/IO.H>
#include <AVR/INTERRUPT.H>
#include <AVR/PGMSPACE.H>



#define UART_buffer_lastAction_WRITE 1
#define UART_buffer_lastAction_READ 0

#define UART_state_NOERROR 0
#define UART_state_OVERFLOW 1


#if UART_char_SPACER == '\0'
#define UART_putchar_spacer(UART_isSpace) do {if (!UART_isSpace) UART_write('0');} while (0)
#define UART_nospace(UART_isSpace) UART_isSpace = 0
#elif UART_char_SPACER == '0'
#define UART_putchar_spacer(UART_isSpace) UART_write('0')
#define UART_nospace(UART_isSpace)
#else
#define UART_putchar_spacer(UART_isSpace) do {if (UART_isSpace) UART_write(UART_char_SPACER); else UART_write('0');} while (0)
#define UART_nospace(UART_isSpace) UART_isSpace = 0
#endif

#if UART_char_SIGN == '\0'
#define UART_putchar_sign()
#else
#define UART_putchar_sign() UART_write(UART_char_SIGN)
#endif

#define UART_putdigit(num, digit, UART_isSpace) do {\
	if (num < digit)\
		UART_putchar_spacer(UART_isSpace);\
	else {\
		char c = '0';\
		do {\
			num -= digit;\
			++c;\
		} while (num >= digit);\
		UART_write(c);\
		UART_nospace(UART_isSpace);\
	}\
} while (0)

#define UART_putsign(num) do {\
	if (num >= 0)\
		UART_putchar_sign();\
	else {\
		num = -num;\
		UART_write('-');\
	}\
} while (0)

#define UART_putnibble(hex) do {\
	switch (hex&0x0F) {\
		case 0x0F:	UART_write('F');\
					break;\
		case 0x0E:	UART_write('E');\
					break;\
		case 0x0D:	UART_write('D');\
					break;\
		case 0x0C:	UART_write('C');\
					break;\
		case 0x0B:	UART_write('B');\
					break;\
		case 0x0A:	UART_write('A');\
					break;\
		default:	UART_write('0'+(hex&0x0F));\
	}\
} while (0)



#if UART_TX_buffer_SIZE > 1
static volatile char UART_TX_buffer[UART_TX_buffer_SIZE];
static volatile unsigned char UART_TX_buffer_head, UART_TX_buffer_tail, UART_TX_buffer_lastAction;
#define UART_TX_buffer_isFull() (UART_TX_buffer_head == UART_TX_buffer_tail && UART_TX_buffer_lastAction != UART_buffer_lastAction_READ)
#define UART_TX_buffer_isEmpty() (UART_TX_buffer_head == UART_TX_buffer_tail && UART_TX_buffer_lastAction == UART_buffer_lastAction_READ)

SIGNAL(USART_TX_vect) {
	if (!UART_TX_buffer_isEmpty()) {
		UDR = UART_TX_buffer[UART_TX_buffer_tail];
		UART_TX_buffer_tail = (UART_TX_buffer_tail+1) % UART_TX_buffer_SIZE;
		UART_TX_buffer_lastAction = UART_buffer_lastAction_READ;
	}
	else {
		//no more char to send
	}
}

void UART_write(char c) {
	if (UART_TX_buffer_isEmpty()) {
		while (bit_is_clear(UCSRA, UDRE));
		UDR = c;
	}
	else {
		while (UART_TX_buffer_isFull());
		UART_TX_buffer[UART_TX_buffer_head] = c;
		UART_TX_buffer_head = (UART_TX_buffer_head+1) % UART_TX_buffer_SIZE;
		UART_TX_buffer_lastAction = UART_buffer_lastAction_WRITE;
	}
}


#elif UART_TX_buffer_SIZE == 1
static volatile char UART_TX_buffer;
static volatile unsigned char UART_TX_buffer_lastAction;
#define UART_TX_buffer_isFull() (UART_TX_buffer_lastAction != UART_buffer_lastAction_READ)
#define UART_TX_buffer_isEmpty() (UART_TX_buffer_lastAction == UART_buffer_lastAction_READ)

SIGNAL(USART_TX_vect) {
	if (!UART_TX_buffer_isEmpty()) {
		UDR = UART_TX_buffer;
		UART_TX_buffer_lastAction = UART_buffer_lastAction_READ;
	}
	else {
		//no more char to send
	}
}

void UART_write(char c) {
	if (UART_TX_buffer_isEmpty()) {
		while (bit_is_clear(UCSRA, UDRE));
		UDR = c;
	}
	else {
		while (UART_TX_buffer_isFull());
		UART_TX_buffer = c;
		UART_TX_buffer_lastAction = UART_buffer_lastAction_WRITE;
	}
}


#else
#define UART_TX_buffer_isFull() bit_is_clear(UCSRA, UDRE)

void UART_write(char c) {
	while (UART_TX_buffer_isFull());
	UDR = c;
}
#endif



void UART_putchar(char c) {
	UART_write(c);
	if (c == '\n')
		UART_write('\r');
}

void UART_puts(const char *str) {
	char c;
	for (; (c=*str) != '\0'; ++str)
		UART_putchar(c);
}

void UART_puts_P(const char *str) {
	char c;
	for (; (c=pgm_read_byte(str)) != '\0'; ++str)
		UART_putchar(c);
}
/*
void UART_putbit_u08(unsigned char bvar, unsigned char pos) {
	if (bvar>>pos & 0x01)
		UART_write(UART_char_BITSET);
	else
		UART_write(UART_char_BITCLEAR);
}

void UART_putbit_u16(unsigned int bvar, unsigned char pos) {
	if (pos < 8)
		UART_putbit_u08((unsigned char)bvar, pos);
	else
		UART_putbit_u08((unsigned char)(bvar>>8), pos-8);
}

void UART_putbit_u32(unsigned long bvar, unsigned char pos) {
	if (pos < 16)
		UART_putbit_u16((unsigned int)bvar, pos);
	else
		UART_putbit_u16((unsigned int)(bvar>>16), pos-16);
}

void UART_putbits_u08(unsigned char bvar) {
	unsigned char pos;
	for (pos = 8; pos; --pos) {
		unsigned char bit = bvar & 0x80;
		bvar <<= 1;
		if (bit)
			UART_write(UART_char_BITSET);
		else
			UART_write(UART_char_BITCLEAR);
	}
}

void UART_putbits_u16(unsigned int bvar) {
	UART_putbits_u08((unsigned char)(bvar>>8));
	UART_putbits_u08((unsigned char)bvar);
}

void UART_putbits_u32(unsigned long bvar) {
	UART_putbits_u16((unsigned int)(bvar>>16));
	UART_putbits_u16((unsigned int)bvar);
}
*/
void UART_putnum_u08(unsigned char num) {
	#if UART_char_SPACER == '0'
	#define UART_isSpace 0
	#else
	unsigned char UART_isSpace = 1;
	#endif
	UART_putdigit(num, 100, UART_isSpace);
	UART_putdigit(num, 10, UART_isSpace);
	UART_write('0'+num);
}

void UART_putnum_s08(signed char num) {
	UART_putsign(num);
	UART_putnum_u08((unsigned char)num);
}

void UART_putnum_u16(unsigned int num) {
	#if UART_char_SPACER == '0'
	#define UART_isSpace 0
	#else
	unsigned char UART_isSpace = 1;
	#endif
	UART_putdigit(num, 10000, UART_isSpace);
	UART_putdigit(num, 1000, UART_isSpace);
	UART_putdigit(num, 100, UART_isSpace);
	UART_putdigit(num, 10, UART_isSpace);
	UART_write('0'+num);
}

void UART_putnum_s16(signed int num) {
	UART_putsign(num);
	UART_putnum_u16((unsigned int)num);
}
/*
void UART_putnum_u32(unsigned long num) {
	#if UART_char_SPACER == '0'
	#define UART_isSpace 0
	#else
	unsigned char UART_isSpace = 1;
	#endif
	UART_putdigit(num, 1000000000, UART_isSpace);
	UART_putdigit(num, 100000000, UART_isSpace);
	UART_putdigit(num, 10000000, UART_isSpace);
	UART_putdigit(num, 1000000, UART_isSpace);
	UART_putdigit(num, 100000, UART_isSpace);
	UART_putdigit(num, 10000, UART_isSpace);
	UART_putdigit(num, 1000, UART_isSpace);
	UART_putdigit(num, 100, UART_isSpace);
	UART_putdigit(num, 10, UART_isSpace);
	UART_write('0'+num);
}

void UART_putnum_s32(signed long num) {
	UART_putsign(num);
	UART_putnum_u32((unsigned long)num);
}

void UART_puthex_u08(unsigned char hex) {
	UART_putnibble(hex>>4);
	UART_putnibble(hex);
}

void UART_puthex_u16(unsigned int hex) {
	UART_puthex_u08((unsigned char)(hex>>8));
	UART_puthex_u08((unsigned char)hex);
}

void UART_puthex_u32(unsigned long hex) {
	UART_puthex_u16((unsigned int)(hex>>16));
	UART_puthex_u16((unsigned int)hex);
}
*/
void UART_init(unsigned long baud) {
	unsigned int ubrr = F_CPU/16/baud - 1;

	unsigned char sreg = SREG;
	cli();

	UBRRH = ubrr>>8;
	UBRRL = ubrr;

	UCSRB = (1<<TXEN);
	#if UART_TX_buffer_SIZE != 0
	UCSRB |= (1<<TXCIE);
	#endif

	UCSRC = (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);

	#if UART_TX_buffer_SIZE > 1
	UART_TX_buffer_head = 0, UART_TX_buffer_tail = 0, UART_TX_buffer_lastAction = UART_buffer_lastAction_READ;
	#elif UART_TX_buffer_SIZE == 1
	UART_TX_buffer_lastAction = UART_buffer_lastAction_READ;
	#endif

	SREG = sreg;
}
