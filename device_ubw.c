#include <p18cxxx.h>
#include <usart.h>
#include "typedefs.h"
#include "usb.h"
#include "io_cfg.h"
#include "device.h"

#pragma udata

char buffer[DEVICE_SENDDATA_SIZE];				// Buffer for data transfer to USB port
unsigned int i;									// Temporary variable for loops
//unsigned char an8, an9, an11;

#pragma code
void getAD(char channel, char * buffer)
{
	ADCON0 &= 0b11000011;				// Clear CHS3:CHS0 (select channel
	ADCON0 |= channel << 2;				// Set channel

	ADCON0bits.GO = 1;	
					
	while (ADCON0bits.NOT_DONE);		// Wait for conversion

	buffer[0] = ADRESL;					
	buffer[1] = ADRESH;
}

void getDI() {
	//buffer[26]
	//if(!PORTAbits.RA4 ==  1)
	if(!PORTBbits.RB4 ==  1)
		buffer[26] |= 0b00000001;
	else buffer[26] &= 0b11111110;

	//if(!PORTCbits.RC0 ==  1)
	if(!PORTDbits.RD6 ==  1)
		buffer[26] |= 0b00000010;
	else buffer[26] &= 0b11111101;

	//if(!PORTCbits.RC1 ==  1)
	if(!PORTDbits.RD0 ==  1)
		buffer[26] |= 0b00000100;
	else buffer[26] &= 0b11111011;

	//if(!PORTCbits.RC2 ==  1)
	if(!PORTCbits.RC6 ==  1)
		buffer[26] |= 0b00001000;
	else buffer[26] &= 0b11110111;

	//if(!PORTDbits.RD0 ==  1)
	if(!PORTDbits.RD4 ==  1)
		buffer[26] |= 0b00010000;
	else buffer[26] &= 0b11101111;

	//if(!PORTDbits.RD1 ==  1)
	if(!PORTDbits.RD7 ==  1)
		buffer[26] |= 0b00100000;
	else buffer[26] &= 0b11011111;

	//if(!PORTDbits.RD2 ==  1)
	if(!PORTCbits.RC7 ==  1)
		buffer[26] |= 0b01000000;
	else buffer[26] &= 0b10111111;

	if(!PORTDbits.RD3 ==  1)
		buffer[26] |= 0b10000000;
	else buffer[26] &= 0b01111111;

	// buffer 27
	//if(!PORTCbits.RC6)
	if(!PORTAbits.RA4)
		buffer[27] |= 0b00000001;
	else buffer[27] &= 0b11111110;

	//if(!PORTCbits.RC7 ==  1)
	if(!PORTBbits.RB2 ==  1)
		buffer[27] |= 0b00000010;
	else buffer[27] &= 0b11111101;

	//if(!PORTDbits.RD4 ==  1)
	if(!PORTCbits.RC2 ==  1)
		buffer[27] |= 0b00000100;
	else buffer[27] &= 0b11111011;

	//if(!PORTDbits.RD6 ==  1)
	if(!PORTDbits.RD2 ==  1)
		buffer[27] |= 0b00001000;
	else buffer[27] &= 0b11110111;

	//if(!PORTDbits.RD7 ==  1)
	if(!PORTCbits.RC0 ==  1)
		buffer[27] |= 0b00010000;
	else buffer[27] &= 0b11101111;

	//if(!PORTBbits.RB2 ==  1)
	if(!PORTBbits.RB3 ==  1)
		buffer[27] |= 0b00100000;
	else buffer[27] &= 0b11011111;

	//if(!PORTBbits.RB3 ==  1)
	if(!PORTCbits.RC1 ==  1)
		buffer[27] |= 0b01000000;
	else buffer[27] &= 0b10111111;

	//if(!PORTBbits.RB4 ==  1)
	if(!PORTDbits.RD1 ==  1)
		buffer[27] |= 0b10000000;
	else buffer[27] &= 0b01111111;

/*
	//this code will make an analog input work like a digital

	an8 = (buffer[17]*256 + buffer[16]);
	an9 = (buffer[19]*256 + buffer[18]);
	an11 = (buffer[23]*256 + buffer[22]);

	if(an8 < 128) {				//not pressed
		buffer[27] |= 0b00100000;
	}
	else {						//pressed
		buffer[27] &= 0b11011111;
	}

	if(an9 < 128) {				//not pressed
		buffer[27] |= 0b01000000;
	}
	else {						//pressed
		buffer[27] &= 0b10111111;
	}

	if(an11 < 128) {				//not pressed
		buffer[27] |= 0b10000000;
	}
	else {						//pressed
		buffer[27] &= 0b01111111;
	}
*/
}



void UserInit(void) {
	for (i = 0; i < DEVICE_SENDDATA_SIZE; i++) {
	    buffer[i] = 0;
	}

	TRISA = 0xFF;
	TRISB = 0b00111111;

	ADCON0 = 0x01;					// AD Control Register 0: Enable (turn on ADC)
	//testing code here
	ADCON1 = 0x07;					// AD Control Register 1: Enable AN0-AN7 as analog
	//to here
	ADCON2 = 0x3C;					// AD Control Register 2: 20 TAD (accuracy), FOSC 4 (freq/4)
	ADCON2bits.ADFM = 1;			// ADC result right justified

	//analog inputs
	TRISAbits.TRISA0 = 1;
	TRISAbits.TRISA1 = 1;
	TRISAbits.TRISA2 = 1;
	TRISAbits.TRISA3 = 1;
	TRISAbits.TRISA5 = 1;
	TRISEbits.TRISE0 = 1;
	TRISEbits.TRISE1 = 1;

	//set up digital inputs
	TRISAbits.TRISA4 = 1;
	TRISCbits.TRISC0 = 1;
	TRISCbits.TRISC1 = 1;
	TRISCbits.TRISC2 = 1;
	TRISDbits.TRISD0 = 1;
	TRISDbits.TRISD1 = 1;
	TRISDbits.TRISD2 = 1;
	TRISDbits.TRISD3 = 1;
	TRISCbits.TRISC6 = 1;
	TRISCbits.TRISC7 = 1;
	TRISDbits.TRISD4 = 1;
	TRISDbits.TRISD6 = 1;
	TRISDbits.TRISD7 = 1;
	TRISBbits.TRISB2 = 1;
	TRISBbits.TRISB3 = 1;
	TRISBbits.TRISB4 = 1;

	//LED Pin
	TRISDbits.TRISD5 = 0; //pin d5 output
	LATDbits.LATD5 = 1; //on
}

void ProcessIO(void) {
    if((usb_device_state < CONFIGURED_STATE)||(UCONbits.SUSPND==1)) return;

	for (i = 0; i < 8; i++) {
	//for (i = 0; i < 13; i++) {
		getAD(i, buffer+2*i);
	}
	
	getDI();

    if(!mHIDTxIsBusy()) {
        HIDTxReport(buffer, DEVICE_SENDDATA_SIZE);
    }
}