#ifndef		DEFINE_CONSTANT_H
#define		DEFINE_CONSTANT_H

#include <avr\io.h>


// ================================================================================================================= //
// =========================                           Global Definitions                  ========================= //
// ================================================================================================================= //
#define		FALSE			0
#define		TRUE			(!FALSE)

#define 	PIN_INPUT		0
#define 	PIN_OUTPUT		1
#define		PORT_INPUT		0x00
#define		PORT_OUTPUT		0xFF

#define		_nop()						__asm__ __volatile__ ("nop")
#define		CLRBIT(address, bit)		((address) &= ~_BV(bit))
#define		SETBIT(address, bit)		((address) |= _BV(bit))


typedef struct {
	unsigned int lbyte:8;
	unsigned int hbyte:8;
} dbyte;
#define		HBYTE(var)		(((dbyte *)&var)->hbyte)
#define		LBYTE(var)		(((dbyte *)&var)->lbyte)


// ================================================================================================================= //
// =========================                           General Type Define                 ========================= //
// ================================================================================================================= //
typedef unsigned char 			u08;
typedef   signed char 			s08;
typedef unsigned int 			u16;    //  int = short = 16 bits
typedef   signed int 			s16;
typedef unsigned long  			u32;
typedef   signed long  			s32;


typedef struct {
	unsigned char b0:1, b1:1, b2:1, b3:1, b4:1, b5:1, b6:1, b7:1;
} bdata;
#define sbit(sfr)		(*(volatile bdata *)_SFR_ADDR(sfr))

// ================================================================================================================= //
// =========================                               Pin Define                      ========================= //
// ================================================================================================================= //

/* PORT A */
#if defined(PA0)
#define		PORTA_0		sbit(PORTA).b0
#define		PINA_0		sbit(PINA).b0
#define		DDRA_0		sbit(DDRA).b0
#endif
#if defined(PA1)
#define		PORTA_1		sbit(PORTA).b1
#define		PINA_1		sbit(PINA).b1
#define		DDRA_1		sbit(DDRA).b1
#endif
#if defined(PA2)
#define		PORTA_2		sbit(PORTA).b2
#define		PINA_2		sbit(PINA).b2
#define		DDRA_2		sbit(DDRA).b2
#endif
#if defined(PA3)
#define		PORTA_3		sbit(PORTA).b3
#define		PINA_3		sbit(PINA).b3
#define		DDRA_3		sbit(DDRA).b3
#endif
#if defined(PA4)
#define		PORTA_4		sbit(PORTA).b4
#define		PINA_4		sbit(PINA).b4
#define		DDRA_4		sbit(DDRA).b4
#endif
#if defined(PA5)
#define		PORTA_5		sbit(PORTA).b5
#define		PINA_5		sbit(PINA).b5
#define		DDRA_5		sbit(DDRA).b5
#endif
#if defined(PA6)
#define		PORTA_6		sbit(PORTA).b6
#define		PINA_6		sbit(PINA).b6
#define		DDRA_6		sbit(DDRA).b6
#endif
#if defined(PA7)
#define		PORTA_7		sbit(PORTA).b7
#define		PINA_7		sbit(PINA).b7
#define		DDRA_7		sbit(DDRA).b7
#endif

/* PORT B */
#if defined(PB0)
#define		PORTB_0		sbit(PORTB).b0
#define		PINB_0		sbit(PINB).b0
#define		DDRB_0		sbit(DDRB).b0
#endif
#if defined(PB1)
#define		PORTB_1		sbit(PORTB).b1
#define		PINB_1		sbit(PINB).b1
#define		DDRB_1		sbit(DDRB).b1
#endif
#if defined(PB2)
#define		PORTB_2		sbit(PORTB).b2
#define		PINB_2		sbit(PINB).b2
#define		DDRB_2		sbit(DDRB).b2
#endif
#if defined(PB3)
#define		PORTB_3		sbit(PORTB).b3
#define		PINB_3		sbit(PINB).b3
#define		DDRB_3		sbit(DDRB).b3
#endif
#if defined(PB4)
#define		PORTB_4		sbit(PORTB).b4
#define		PINB_4		sbit(PINB).b4
#define		DDRB_4		sbit(DDRB).b4
#endif
#if defined(PB5)
#define		PORTB_5		sbit(PORTB).b5
#define		PINB_5		sbit(PINB).b5
#define		DDRB_5		sbit(DDRB).b5
#endif
#if defined(PB6)
#define		PORTB_6		sbit(PORTB).b6
#define		PINB_6		sbit(PINB).b6
#define		DDRB_6		sbit(DDRB).b6
#endif
#if defined(PB7)
#define		PORTB_7		sbit(PORTB).b7
#define		PINB_7		sbit(PINB).b7
#define		DDRB_7		sbit(DDRB).b7
#endif

/* PORT C */
#if defined(PC0)
#define		PORTC_0		sbit(PORTC).b0
#define		PINC_0		sbit(PINC).b0
#define		DDRC_0		sbit(DDRC).b0
#endif
#if defined(PC1)
#define		PORTC_1		sbit(PORTC).b1
#define		PINC_1		sbit(PINC).b1
#define		DDRC_1		sbit(DDRC).b1
#endif
#if defined(PC2)
#define		PORTC_2		sbit(PORTC).b2
#define		PINC_2		sbit(PINC).b2
#define		DDRC_2		sbit(DDRC).b2
#endif
#if defined(PC3)
#define		PORTC_3		sbit(PORTC).b3
#define		PINC_3		sbit(PINC).b3
#define		DDRC_3		sbit(DDRC).b3
#endif
#if defined(PC4)
#define		PORTC_4		sbit(PORTC).b4
#define		PINC_4		sbit(PINC).b4
#define		DDRC_4		sbit(DDRC).b4
#endif
#if defined(PC5)
#define		PORTC_5		sbit(PORTC).b5
#define		PINC_5		sbit(PINC).b5
#define		DDRC_5		sbit(DDRC).b5
#endif
#if defined(PC6)
#define		PORTC_6		sbit(PORTC).b6
#define		PINC_6		sbit(PINC).b6
#define		DDRC_6		sbit(DDRC).b6
#endif
#if defined(PC7)
#define		PORTC_7		sbit(PORTC).b7
#define		PINC_7		sbit(PINC).b7
#define		DDRC_7		sbit(DDRC).b7
#endif

/* PORT D */
#if defined(PD0)
#define		PORTD_0		sbit(PORTD).b0
#define		PIND_0		sbit(PIND).b0
#define		DDRD_0		sbit(DDRD).b0
#endif
#if defined(PD1)
#define		PORTD_1		sbit(PORTD).b1
#define		PIND_1		sbit(PIND).b1
#define		DDRD_1		sbit(DDRD).b1
#endif
#if defined(PD2)
#define		PORTD_2		sbit(PORTD).b2
#define		PIND_2		sbit(PIND).b2
#define		DDRD_2		sbit(DDRD).b2
#endif
#if defined(PD3)
#define		PORTD_3		sbit(PORTD).b3
#define		PIND_3		sbit(PIND).b3
#define		DDRD_3		sbit(DDRD).b3
#endif
#if defined(PD4)
#define		PORTD_4		sbit(PORTD).b4
#define		PIND_4		sbit(PIND).b4
#define		DDRD_4		sbit(DDRD).b4
#endif
#if defined(PD5)
#define		PORTD_5		sbit(PORTD).b5
#define		PIND_5		sbit(PIND).b5
#define		DDRD_5		sbit(DDRD).b5
#endif
#if defined(PD6)
#define		PORTD_6		sbit(PORTD).b6
#define		PIND_6		sbit(PIND).b6
#define		DDRD_6		sbit(DDRD).b6
#endif
#if defined(PD7)
#define		PORTD_7		sbit(PORTD).b7
#define		PIND_7		sbit(PIND).b7
#define		DDRD_7		sbit(DDRD).b7
#endif

#ifdef _AVR_IOM128_H_
	/* PORT e		*/
	#if defined(PE0)
	#define		PORTE_0		sbit(PORTE).b0
	#define		PINE_0		sbit(PINE).b0
	#define		DDRE_0		sbit(DDRE).b0
	#endif
	#if defined(PE1)
	#define		PORTE_1		sbit(PORTE).b1
	#define		PINE_1		sbit(PINE).b1
	#define		DDRE_1		sbit(DDRE).b1
	#endif
	#if defined(PE2)
	#define		PORTE_2		sbit(PORTE).b2
	#define		PINE_2		sbit(PINE).b2
	#define		DDRE_2		sbit(DDRE).b2
	#endif
	#if defined(PE3)
	#define		PORTE_3		sbit(PORTE).b3
	#define		PINE_3		sbit(PINE).b3
	#define		DDRE_3		sbit(DDRE).b3
	#endif
	#if defined(PE4)
	#define		PORTE_4		sbit(PORTE).b4
	#define		PINE_4		sbit(PINE).b4
	#define		DDRE_4		sbit(DDRE).b4
	#endif
	#if defined(PE5)
	#define		PORTE_5		sbit(PORTE).b5
	#define		PINE_5		sbit(PINE).b5
	#define		DDRE_5		sbit(DDRE).b5
	#endif
	#if defined(PE6)
	#define		PORTE_6		sbit(PORTE).b6
	#define		PINE_6		sbit(PINE).b6
	#define		DDRE_6		sbit(DDRE).b6
	#endif
	#if defined(PE7)
	#define		PORTE_7		sbit(PORTE).b7
	#define		PINE_7		sbit(PINE).b7
	#define		DDRE_7		sbit(DDRE).b7
	#endif

	/* PORT F */
	#if defined(PF0)
	#define		PORTF_0		sbit(PORTF).b0
	#define		PINF_0		sbit(PINF).b0
	#define		DDRF_0		sbit(DDRF).b0
	#endif
	#if defined(PF1)
	#define		PORTF_1		sbit(PORTF).b1
	#define		PINF_1		sbit(PINF).b1
	#define		DDRF_1		sbit(DDRF).b1
	#endif
	#if defined(PF2)
	#define		PORTF_2		sbit(PORTF).b2
	#define		PINF_2		sbit(PINF).b2
	#define		DDRF_2		sbit(DDRF).b2
	#endif
	#if defined(PF3)
	#define		PORTF_3		sbit(PORTF).b3
	#define		PINF_3		sbit(PINF).b3
	#define		DDRF_3		sbit(DDRF).b3
	#endif
	#if defined(PF4)
	#define		PORTF_4		sbit(PORTF).b4
	#define		PINF_4		sbit(PINF).b4
	#define		DDRF_4		sbit(DDRF).b4
	#endif
	#if defined(PF5)
	#define		PORTF_5		sbit(PORTF).b5
	#define		PINF_5		sbit(PINF).b5
	#define		DDRF_5		sbit(DDRF).b5
	#endif
	#if defined(PF6)
	#define		PORTF_6		sbit(PORTF).b6
	#define		PINF_6		sbit(PINF).b6
	#define		DDRF_6		sbit(DDRF).b6
	#endif
	#if defined(PF7)
	#define		PORTF_7		sbit(PORTF).b7
	#define		PINF_7		sbit(PINF).b7
	#define		DDRF_7		sbit(DDRF).b7
	#endif

	/* PORT G */
	#if defined(PG0)
	#define		PORTG_0		sbit(PORTG).b0
	#define		PING_0		sbit(PING).b0
	#define		DDRG_0		sbit(DDRG).b0
	#endif
	#if defined(PG1)
	#define		PORTG_1		sbit(PORTG).b1
	#define		PING_1		sbit(PING).b1
	#define		DDRG_1		sbit(DDRG).b1
	#endif
	#if defined(PG2)
	#define		PORTG_2		sbit(PORTG).b2
	#define		PING_2		sbit(PING).b2
	#define		DDRG_2		sbit(DDRG).b2
	#endif
	#if defined(PG3)
	#define		PORTG_3		sbit(PORTG).b3
	#define		PING_3		sbit(PING).b3
	#define		DDRG_3		sbit(DDRG).b3
	#endif
	#if defined(PG4)
	#define		PORTG_4		sbit(PORTG).b4
	#define		PING_4		sbit(PING).b4
	#define		DDRG_4		sbit(DDRG).b4
	#endif
#endif


// ================================================================================================================= //
// =========================                               Pin Define                     ========================= //
// ================================================================================================================= //
#define		PA_0_OUT		sbit(PORTA).b0
#define		PA_1_OUT		sbit(PORTA).b1
#define		PA_2_OUT		sbit(PORTA).b2
#define		PA_3_OUT		sbit(PORTA).b3
#define		PA_4_OUT		sbit(PORTA).b4
#define		PA_5_OUT		sbit(PORTA).b5
#define		PA_6_OUT		sbit(PORTA).b6
#define		PA_7_OUT		sbit(PORTA).b7
#define		PA_0_IN			sbit(PINA).b0
#define		PA_1_IN			sbit(PINA).b1
#define		PA_2_IN			sbit(PINA).b2
#define		PA_3_IN			sbit(PINA).b3
#define		PA_4_IN			sbit(PINA).b4
#define		PA_5_IN			sbit(PINA).b5
#define		PA_6_IN			sbit(PINA).b6
#define		PA_7_IN			sbit(PINA).b7
#define		PA_0_DDR		sbit(DDRA).b0
#define		PA_1_DDR		sbit(DDRA).b1
#define		PA_2_DDR		sbit(DDRA).b2
#define		PA_3_DDR		sbit(DDRA).b3
#define		PA_4_DDR		sbit(DDRA).b4
#define		PA_5_DDR		sbit(DDRA).b5
#define		PA_6_DDR		sbit(DDRA).b6
#define		PA_7_DDR		sbit(DDRA).b7


#define		PB_0_OUT		sbit(PORTB).b0
#define		PB_1_OUT		sbit(PORTB).b1
#define		PB_2_OUT		sbit(PORTB).b2
#define		PB_3_OUT		sbit(PORTB).b3
#define		PB_4_OUT		sbit(PORTB).b4
#define		PB_5_OUT		sbit(PORTB).b5
#define		PB_6_OUT		sbit(PORTB).b6
#define		PB_7_OUT		sbit(PORTB).b7
#define		PB_0_IN			sbit(PINB).b0
#define		PB_1_IN			sbit(PINB).b1
#define		PB_2_IN			sbit(PINB).b2
#define		PB_3_IN			sbit(PINB).b3
#define		PB_4_IN			sbit(PINB).b4
#define		PB_5_IN			sbit(PINB).b5
#define		PB_6_IN			sbit(PINB).b6
#define		PB_7_IN			sbit(PINB).b7
#define		PB_0_DDR		sbit(DDRB).b0
#define		PB_1_DDR		sbit(DDRB).b1
#define		PB_2_DDR		sbit(DDRB).b2
#define		PB_3_DDR		sbit(DDRB).b3
#define		PB_4_DDR		sbit(DDRB).b4
#define		PB_5_DDR		sbit(DDRB).b5
#define		PB_6_DDR		sbit(DDRB).b6
#define		PB_7_DDR		sbit(DDRB).b7

#define		PC_0_OUT		sbit(PORTC).b0
#define		PC_1_OUT		sbit(PORTC).b1
#define		PC_2_OUT		sbit(PORTC).b2
#define		PC_3_OUT		sbit(PORTC).b3
#define		PC_4_OUT		sbit(PORTC).b4
#define		PC_5_OUT		sbit(PORTC).b5
#define		PC_6_OUT		sbit(PORTC).b6
#define		PC_7_OUT		sbit(PORTC).b7
#define		PC_0_IN			sbit(PINC).b0
#define		PC_1_IN			sbit(PINC).b1
#define		PC_2_IN			sbit(PINC).b2
#define		PC_3_IN			sbit(PINC).b3
#define		PC_4_IN			sbit(PINC).b4
#define		PC_5_IN			sbit(PINC).b5
#define		PC_6_IN			sbit(PINC).b6
#define		PC_7_IN			sbit(PINC).b7
#define		PC_0_DDR		sbit(DDRC).b0
#define		PC_1_DDR		sbit(DDRC).b1
#define		PC_2_DDR		sbit(DDRC).b2
#define		PC_3_DDR		sbit(DDRC).b3
#define		PC_4_DDR		sbit(DDRC).b4
#define		PC_5_DDR		sbit(DDRC).b5
#define		PC_6_DDR		sbit(DDRC).b6
#define		PC_7_DDR		sbit(DDRC).b7

#define		PD_0_OUT		sbit(PORTD).b0
#define		PD_1_OUT		sbit(PORTD).b1
#define		PD_2_OUT		sbit(PORTD).b2
#define		PD_3_OUT		sbit(PORTD).b3
#define		PD_4_OUT		sbit(PORTD).b4
#define		PD_5_OUT		sbit(PORTD).b5
#define		PD_6_OUT		sbit(PORTD).b6
#define		PD_7_OUT		sbit(PORTD).b7
#define		PD_0_IN			sbit(PIND).b0
#define		PD_1_IN			sbit(PIND).b1
#define		PD_2_IN			sbit(PIND).b2
#define		PD_3_IN			sbit(PIND).b3
#define		PD_4_IN			sbit(PIND).b4
#define		PD_5_IN			sbit(PIND).b5
#define		PD_6_IN			sbit(PIND).b6
#define		PD_7_IN			sbit(PIND).b7
#define		PD_0_DDR		sbit(DDRD).b0
#define		PD_1_DDR		sbit(DDRD).b1
#define		PD_2_DDR		sbit(DDRD).b2
#define		PD_3_DDR		sbit(DDRD).b3
#define		PD_4_DDR		sbit(DDRD).b4
#define		PD_5_DDR		sbit(DDRD).b5
#define		PD_6_DDR		sbit(DDRD).b6
#define		PD_7_DDR		sbit(DDRD).b7

#ifdef		_AVR_IOM128_H_
	#define		PE_0_OUT		sbit(PORTE).b0
	#define		PE_1_OUT		sbit(PORTE).b1
	#define		PE_2_OUT		sbit(PORTE).b2
	#define		PE_3_OUT		sbit(PORTE).b3
	#define		PE_4_OUT		sbit(PORTE).b4
	#define		PE_5_OUT		sbit(PORTE).b5
	#define		PE_6_OUT		sbit(PORTE).b6
	#define		PE_7_OUT		sbit(PORTE).b7
	#define		PE_0_IN			sbit(PINE).b0
	#define		PE_1_IN			sbit(PINE).b1
	#define		PE_2_IN			sbit(PINE).b2
	#define		PE_3_IN			sbit(PINE).b3
	#define		PE_4_IN			sbit(PINE).b4
	#define		PE_5_IN			sbit(PINE).b5
	#define		PE_6_IN			sbit(PINE).b6
	#define		PE_7_IN			sbit(PINE).b7
	#define		PE_0_DDR		sbit(DDRE).b0
	#define		PE_1_DDR		sbit(DDRE).b1
	#define		PE_2_DDR		sbit(DDRE).b2
	#define		PE_3_DDR		sbit(DDRE).b3
	#define		PE_4_DDR		sbit(DDRE).b4
	#define		PE_5_DDR		sbit(DDRE).b5
	#define		PE_6_DDR		sbit(DDRE).b6
	#define		PE_7_DDR		sbit(DDRE).b7

	#define		PF_0_OUT		sbit(PORTF).b0
	#define		PF_1_OUT		sbit(PORTF).b1
	#define		PF_2_OUT		sbit(PORTF).b2
	#define		PF_3_OUT		sbit(PORTF).b3
	#define		PF_4_OUT		sbit(PORTF).b4
	#define		PF_5_OUT		sbit(PORTF).b5
	#define		PF_6_OUT		sbit(PORTF).b6
	#define		PF_7_OUT		sbit(PORTF).b7
	#define		PF_0_IN			sbit(PINF).b0
	#define		PF_1_IN			sbit(PINF).b1
	#define		PF_2_IN			sbit(PINF).b2
	#define		PF_3_IN			sbit(PINF).b3
	#define		PF_4_IN			sbit(PINF).b4
	#define		PF_5_IN			sbit(PINF).b5
	#define		PF_6_IN			sbit(PINF).b6
	#define		PF_7_IN			sbit(PINF).b7
	#define		PF_0_DDR		sbit(DDRF).b0
	#define		PF_1_DDR		sbit(DDRF).b1
	#define		PF_2_DDR		sbit(DDRF).b2
	#define		PF_3_DDR		sbit(DDRF).b3
	#define		PF_4_DDR		sbit(DDRF).b4
	#define		PF_5_DDR		sbit(DDRF).b5
	#define		PF_6_DDR		sbit(DDRF).b6
	#define		PF_7_DDR		sbit(DDRF).b7

	#define		PG_0_OUT		sbit(PORTG).b0
	#define		PG_1_OUT		sbit(PORTG).b1
	#define		PG_2_OUT		sbit(PORTG).b2
	#define		PG_3_OUT		sbit(PORTG).b3
	#define		PG_4_OUT		sbit(PORTG).b4
	#define		PG_5_OUT		sbit(PORTG).b5
	#define		PG_6_OUT		sbit(PORTG).b6
	#define		PG_7_OUT		sbit(PORTG).b7
	#define		PG_0_IN			sbit(PING).b0
	#define		PG_1_IN			sbit(PING).b1
	#define		PG_2_IN			sbit(PING).b2
	#define		PG_3_IN			sbit(PING).b3
	#define		PG_4_IN			sbit(PING).b4
	#define		PG_5_IN			sbit(PING).b5
	#define		PG_6_IN			sbit(PING).b6
	#define		PG_7_IN			sbit(PING).b7
	#define		PG_0_DDR		sbit(DDRG).b0
	#define		PG_1_DDR		sbit(DDRG).b1
	#define		PG_2_DDR		sbit(DDRG).b2
	#define		PG_3_DDR		sbit(DDRG).b3
	#define		PG_4_DDR		sbit(DDRG).b4
	#define		PG_5_DDR		sbit(DDRG).b5
	#define		PG_6_DDR		sbit(DDRG).b6
	#define		PG_7_DDR		sbit(DDRG).b7
#endif

#endif
