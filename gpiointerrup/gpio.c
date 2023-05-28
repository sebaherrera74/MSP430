/*
 * gpio.c
 *
 *  Created on: 26 may. 2023
 *      Author: sebah
 */

#include "gpio.h"
#include <msp430g2553.h>



//probar que pasaria si a un pin lo configuro como salida primero y depues como entrada?
//Que pasa si no congiguro un pin como salida y lo pongo directamente como entrada
void gpioInit(gpioport_t puerto,int pin ,gpioinit_t modo){  //Tendria que poner que puerto iniciar y si es entrada o salida , si es entrada fijarse el tema de pull
                       //puul down

if(puerto==PUERTO1){

    switch(modo){
        case output:
            P1DIR=0;  //Registro para indicar Si es entrada o es salida 0=entrada 1=salida
            P1DIR|=pin ;//P1.0 y P1.6 son salida
            break;

        case input:
            P1DIR=0;
            P1DIR&=pin;
            P1REN=0; //registro indica habilitación de resistencia pull-up y pull-down
            P1REN|=pin; //P1.3 habilita resistencia
            P1SEL=0; //vinculación a gpio
            P1SEL2=0; //vinculación a GPIO
            P1OUT=0;
            P1OUT|=pin;
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
        P1OUT|=pin;
    }
    else if(puerto==PUERTO2){
        P2OUT|=pin;
    }
}
//Apaga el pin pasado como parametro, si quiero apagar varios hago un "OR"
void DigitalOutputDeactivate(gpioport_t puerto,int pin){
    if(puerto==PUERTO1){
            P1OUT=P1OUT&(~pin);
        }
        else if(puerto==PUERTO2){
            P2OUT=P1OUT&(~pin);
        }
}

//Funciones para las entradas y falta la iniclizacion de los pines

bool DigitalReadInput(gpioport_t puerto,int pin){
    if (puerto==PUERTO1){
        if((P1IN&pin)==0){
            return true;
        }
    }
    else if (puerto==PUERTO2){
        if((P2IN&pin)==0){
            return true;
        }
    }
    return false;
}


