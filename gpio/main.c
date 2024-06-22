#include <msp430g2553.h>
#include <stdbool.h>
#include "gpio.h"

bool aux=false;
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer




    gpioInit(PUERTO1,pin0|pin1|pin2|pin6|pin3, output);
    gpioInit(PUERTO2,pin0, output);
    //gpioInit(PUERTO1,pin5, input);

    while(1)
            {
        DigitalOutputActivate(PUERTO1,pin0|pin1|pin2|pin3);
        DigitalOutputActivate(PUERTO2,pin0);
        aux=DigitalReadInput(PUERTO1,pin5);

        if (aux==false) //P1.3 está presionado
                   {
            DigitalOutputActivate(PUERTO1,pin6);
                   }
                   else //P1.3 no está presionado
                   {
                      DigitalOutputDeactivate(PUERTO1,pin6);
                   }
       __delay_cycles(1000000);

       DigitalOutputDeactivate(PUERTO1,pin3);
       __delay_cycles(1000000);

}
}



