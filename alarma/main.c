
#include <msp430g2553.h>
#include "gpio.h"
#include <stdbool.h>
/**
 * main.c
 */



bool volatile alarmaActivada=false;
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	_EINT(); //habilita las interrupciones GIE
     gpioInit(PUERTO1, pin0,output);



     P1IE|=pin5; //habilita las interrupcione en P1.5
     P1IES&=pin5; //interrupcion por flanco de bajada
     P1IFG&=~pin5; //reinicia cualquier interrupcion pendiente
     _EINT(); //habilita las interrupciones GIE
     while(1)
	    {
         if (alarmaActivada==true){

             DigitalOutputActivate(PUERTO1,pin0);
             P1IE|=pin5;
             //alarmaActivada=false;
         }

         else if (alarmaActivada==false){

         DigitalOutputDeactivate(PUERTO1,pin0);
         //P1IE|=pin5;

	}
	    }
}

#pragma vector=PORT1_VECTOR
__interrupt void PORT1_IRQ(void)
{
    const char Int=P1IFG; //guarda el valor de P1IFG

    if(Int&pin5) //si la interrupcon sucedio en P1.5
    {
        P1IFG&=~pin5; //reincia la bandera de interrupcion

        //P1IES
        if(P1IES&pin5) //detecto un borde de bajada (boton presionado)
        {alarmaActivada=true;
        P1IFG&=~pin5; //reincia la bandera de interrupcion
        P1IES&=pin5;
        P1IE&=~pin5;
            //P1IES&=pin5;
          //  alarmaActivada=true;


        }
        else
        {
            P1IES|=pin5;
            alarmaActivada=false;
        }
    }
}
