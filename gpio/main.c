#include <msp430g2553.h>

//PX.x Puerto X->pORT1 o Port2 ,x->pin
#define pin10 BIT0
#define pin11 BIT1
#define pin12 BIT2
#define GPIOOFF 0x0000
/*
typedef enum{
    pin10,
    pin11,
    pin12

}gpiopin_t;*/
typedef enum {
    PUERTO1,
    PUERTO2
}gpioport_t ;

typedef enum {
    output,
    input
}gpioinit_t ;

//typedef enum{
//};
void gpioInit(gpioport_t puerto,int pin,gpioinit_t modo);
void DigitalOutputActivate(gpioport_t puerto,int pin);

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

    gpioInit(PUERTO1,pin10|pin11|pin12, output);
    gpioInit(PUERTO2,pin10, output);
    while(1)
            {

        DigitalOutputActivate(PUERTO1,pin10);
        __delay_cycles(1000000);
        DigitalOutputActivate(PUERTO1,pin11);
        __delay_cycles(1000000);
        DigitalOutputActivate(PUERTO2,pin10);
        __delay_cycles(1000000);
        P2OUT=0;
            }
}


void gpioInit(gpioport_t puerto,int pin ,gpioinit_t modo){  //Tendria que poner que puerto iniciar y si es entrada o salida , si es entrada fijarse el tema de pull
                       //puul down

if(puerto==PUERTO1){
    switch(modo){
        case output:
            P1DIR=0;  //Registro para indicar Si es entrada o es salida 0=entrada 1=salida
            P1DIR|=pin ;//P1.0 y P1.6 son salida
            P1OUT=0; //Registro para entradas indica 1=pull-up 0=pull-down si PxREN=1 en el pin
            P1OUT|=pin; //Registro para las salidas que indica el nivel del pin 1=3.3V 0=0V
                    //P1.3 tiene pull-up y P1.0 =3.3V P1.6=0V;
            break;
         default:
             break;
    }
}
else if(puerto==PUERTO2){
    switch(modo){
    case output:
        P2DIR=0;  //Registro para indicar Si es entrada o es salida 0=entrada 1=salida
        P2DIR|=BIT0;//P1.0 y P1.6 son salida
        P2OUT=0; //Registro para entradas indica 1=pull-up 0=pull-down si PxREN=1 en el pin
        P1OUT|=BIT0; //Registro para las salidas que indica el nivel del pin 1=3.3V 0=0V
                       //P1.3 tiene pull-up y P1.0 =3.3V P1.6=0V;
     break;
     default:
         break;

    }
}
}

void DigitalOutputActivate(gpioport_t puerto,int pin){
    if(puerto==PUERTO1){
        P1OUT=pin;
    }
    else if(puerto==PUERTO2){
        P2OUT=pin;
    }
}

