#include <msp430g2553.h>


/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
    P1DIR=0;  //Registro para indicar Si es entrada o es salida 0=entrada 1=salida
    P1DIR|=BIT0|BIT1 ;//P1.0 y P1.6 son salida

    P1OUT=0; //Registro para entradas indica 1=pull-up 0=pull-down si PxREN=1 en el pin
    P1OUT|=BIT1|BIT0; //Registro para las salidas que indica el nivel del pin 1=3.3V 0=0V
            //P1.3 tiene pull-up y P1.0 =3.3V P1.6=0V;
    while(1)
            {
        P1OUT=BIT0|BIT1;
        __delay_cycles(100000);
        P1OUT=0;
        __delay_cycles(100000);
            }

	
}
