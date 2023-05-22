#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	//Set oscilador controlador digitsa a 1 Mhz
	BCSCTL1=CALBC1_1MHZ;
	DCOCTL=CALDCO_1MHZ;

	// Configure P1.3 pin
	P1DIR &= ~BIT3; 	// Set P1.3 as input (for pushbutton)
	 P1REN=0; //registro indica habilitación de resistencia pull-up y pull-down
	        P1REN|=BIT3; //P1.3 habilita resistencia
	// Configure P1.6 pin (Note: BIT6 is a symbol for the constant 0b01000000
	// When P1DIR=1 and P1SEL=1 and P1SEL2=0 for timer output TA0.1 on pin 6
	P1DIR |= BIT6; 	// Sets bit 6 while leaving the other bits untouched
	P1SEL |= BIT6; 	// Sets bit 6 while leaving the other bits untouched
	P1SEL2 &= ~BIT6; // Clears bit 6 while leaving the other bits untouched

	// Configure timer A for pulse-width modulation
	TA0CTL = TASSEL_2 + MC_1 + ID_0;
	// TASSEL_2 = SMCLK as input clock,
	// MC_1 = Mode Control 1
	// (counts "up" to TA0CCR0 then resets),
	// ID_0 = No clock frequency division
	TA0CCR0 = 10000;
	// Maximum count value determines frequency =
	// SMCLK/ClockDivide/TACCR0 (1 MHz/1/10000 = 100 Hz)
	TA0CCR1 = 500;
	// Initialize the duty cycle at 1.00% = TACCR1/TACCR0
	TA0CCTL1 = OUTMOD_7; // TA0.1 output high when counter < TA0CCR1
	while(1)
	{

	if ((P1IN&BIT3)!=0)
	{
	TA0CCR1 = 10000; // 25.00% duty cycle when P1.3 pushbutton pressed
	}
	else
	{

	   TA0CCR1 = 10000;

	}
	}
}

