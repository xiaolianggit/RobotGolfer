// ******************************************************************************************* //
//
//	Filename		:   IOdef.h
//	Title        	:   RoboGolfer Main Header File 
//	Author			:   Fan Wing Sze & Wong Ming Kin
//	Description		:   This header file is the I/O Pin Definition of the RoboGolfer Project.
//
// ******************************************************************************************* //

#ifndef		__IODEF_H__
#define		__IODEF_H__


#define		IR_1				PA_0_IN
#define		IR_2				PA_1_IN		// Infra-red Distance Sensor inputs, ADC
#define		VR_IN_1				PA_2_IN
#define		VR_IN_2				PA_3_IN		// Variable Resistors inputs, ADC
#define		MR_FB				PA_6_IN
#define		ML_FB				PA_7_IN		// Motor Speed Software-generated PWM outputs

#define		BUZZER_OUT			PB_7_OUT	// Buzzer output
#define		DECODER_ADD1		PB_2_OUT
#define		DECODER_ADD2		PB_3_OUT
#define		DECODER_ADD3		PB_4_OUT	// PWM Generation Decoder Address outputs

#define		DATA_OUT			PORTC		// define the data output of databus
#define		DATA_DIR			DDRC		// define the data direction of databus
#define		DATA_IN				PINC		// define the data input of databus

#define		ENCODER_EN1			PD_2_OUT
#define		ENCODER_EN2			PD_3_OUT
#define		DECODER_EN			PD_4_OUT	// PWM Generation Decoder Enable output
#define		SW_IN_1				PB_5_IN			
#define		SW_IN_2				PB_6_IN		// Push Buttons inputs, low enable
#define		MOTOR_EN			PD_7_OUT	// Motor Enable output, high enable

#define		FLOOR_BACK			PB_0_DDR
#define		FLOOR_MID			PD_6_DDR
#define		FLOOR_FRONT			PB_1_DDR	// Floor Sensors Enable outputs, low enable

#endif
