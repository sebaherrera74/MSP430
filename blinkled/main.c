#include <msp430g2553.h>
//void delayloop(void);

/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	P1DIR |= 0XFF; //CONFIGURA TODOS LOS PINES DEL PUERTO1 COMO SALIDAS


	 while(1){
	     P1OUT=BIT0;
	     __delay_cycles(1000000);
	     P1OUT=BIT6;
	     __delay_cycles(1000000);
	     P1OUT=BIT6|BIT0;
	     __delay_cycles(1000000);
	 }
	
}
/*
void delayloop(void){

    unsigned int delay;

    for(delay=0xFFFF;delay>0;--delay);
}*/
