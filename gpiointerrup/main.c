
/**
 * main.c.
 */

#include <msp430g2553.h>
#include "gpio.h"
/*Alarma , el problema consiste en detectar si hubo una interrupcion en el P1.5
 * si sucede eso activa un pin de salida en nivel alto
 */
#define DBOTON1 P1DIR
#define RBOTON1 P1REN
#define SBOTON1 P1SEL
#define S2BOTON1 P1SEL2
//habilitaci�n individual de interrupcion en cada pin del P1 y P2
#define EBOTON1 P1IE //  1= habilitado 0= deshabilitado
//Selecci�n de borde de interrupcion en cada pin del P1 y P2
/*
 *  ___                          __
 *     |   1=borde de bajada    |     0=borde de subida
 *     |__                    __|
 *
 */
#define ESBOTON1 P1IES // 1= borde de bajada (high-low) 0=borde de subida (low-high)
//PxIFG se actualiza incluso si no esta activada la interrupcion
#define IBOTON1 P1IFG //registro donde se guarda la bandera de interupcion 1= interrupcion pendiente
#define BOTON1 BIT5



#define DBOTON2 P2DIR
#define RBOTON2 P2REN
#define SBOTON2 P2SEL
#define S2BOTON2 P2SEL2
#define IBOTON2 P2IFG
#define EBOTON2 P2IE
#define ESBOTON2 P2IES
#define BOTON2 BIT3


#define DBOTON3 P2DIR //reset
#define RBOTON3 P2REN
#define IBOTON3 P2IFG
#define EBOTON3 P2IE
#define ESBOTON3 P2IES
#define SBOTON3 P2SEL
#define S2BOTON3 P2SEL2
#define BOTON3 BIT6


#define DLED P1DIR //LED
#define RLED P1REN
#define SLED P1SEL
#define S2LED P1SEL2
#define OLED P1OUT
#define LED BIT0



int contador1=0; //variable para indicar el conteo del boton 1
int contador2=0; //variable para indicar el conteo del boton 2
int led=0;  //estado del LED

int actualizarCONTEO1=0;//variable que idnica cuantas  veces
                    //se debe de actualizar la LCD
int actualizarCONTEO2=0;
int actualizarLED=0;
int actualizarRESET=0;


int main(void)
{

    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    DBOTON1&=BOTON1; //configura el boton1 como entrada P1.5
    RBOTON1&=BOTON1; //boton1 sin resistencia interna
    SBOTON1&=BOTON1;
    S2BOTON1&=BOTON1;

    DBOTON2&=~BOTON2; //configura el boton2 como entrada P2.3
    RBOTON2&=~BOTON2; //boton2 sin resistencia interna
    SBOTON2&=~BOTON2;
    S2BOTON2&=~BOTON2;

    DBOTON3&=~BOTON3; //configura el boton1 como entrada P2.6
    RBOTON3&=~BOTON3; //boton1 sin resistencia interna
    SBOTON3&=~BOTON3;
    S2BOTON3&=~BOTON3;

    DLED|=LED;        //LED como salida P1.0
    RLED&=~LED;       //LED sin resistencia interna
    SLED&=~LED;
    S2LED&=~LED;
    OLED&=~LED;       //valor inicial del LED 0V = apagado


    EBOTON1|=BOTON1; //habilita las interrupciones en P1.6 y P2.3
    EBOTON2|=BOTON2;
    EBOTON3|=BOTON3;
    ESBOTON1&=BOTON1; //interrupcion por flanco de bajada
    ESBOTON2|=BOTON2;
    ESBOTON3|=BOTON3;
    IBOTON1&=~BOTON1; //reinicia cualquier interrupcion pendiente
    IBOTON2&=~BOTON2;
    IBOTON3&=~BOTON3;

    _EINT(); //habilita las interrupciones GIE
    gpioInit(PUERTO1, pin0,output);
    while(1)
    {
        if((contador1%2)==0){
            DigitalOutputActivate(PUERTO1,pin0);
        }
        else{
            DigitalOutputDeactivate(PUERTO1,pin0);
        }

}
}

#pragma vector=PORT1_VECTOR
__interrupt void PORT1_IRQ(void)
{
    const char Int=IBOTON1; //guarda el valor de P1IFG

    if(Int&BOTON1) //si la interrupcon sucedio en P1.6
    {
        IBOTON1&=~BOTON1; //reincia la bandera de interrupcion
        //P1IES
        if(ESBOTON1&BOTON1) //detecto un borde de bajada (boton presionado)
        {
            contador1++;//aumenta el conteo del boton
            actualizarCONTEO1++;//indica que debe actualizar la pantalla
            led=1;//indica que debe prender el led
            //P1IES&=~BOTON1; //P1IES.6 =0
            ESBOTON1&=~BOTON1; //cambia la deteccion a borde de subida
        }
        else
        {//detecto un borde de subida (boton no presionado)
            led=0; //indica que debe apagar el led
            //P1IES.6=1;
            ESBOTON1|=BOTON1; //cambia deteccion a borde de bajada
        }
        actualizarLED++; //indica que se necesita actualizar la LCD
    }
}

#pragma vector=PORT2_VECTOR
__interrupt void PORT2_IRQ(void)
{
    const char Int=IBOTON2;
    if(Int&BOTON2) //detecta que el boton2 se ha presionado
    {
        IBOTON2&=~BOTON2; //reincia bandera (ya se proceso la int)
        contador2++;//aumenta el conteo del boton
        actualizarCONTEO2++;//indica que debe actualizar el contador2
    }
    if(Int&BOTON3) //detecta que e boton de reset (boton3) se ha presionado
    {
        IBOTON3&=~BOTON3; //reinicia la bandera
        contador1=0;//reinicia los 2 contadores
        contador2=0;
        actualizarRESET++;//indica que debe actualizar los 2 contadores
    }

}
