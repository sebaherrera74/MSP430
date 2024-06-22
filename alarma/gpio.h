/*
 * gpio.h
 *
 *  Created on: 27 may. 2023
 *      Author: sebah
 */

#ifndef GPIO_H_
#define GPIO_H_


#include <stdbool.h>
//PX.x Puerto X->pORT1 o Port2 ,x->pin
#define pin0 BIT0
#define pin1 BIT1
#define pin2 BIT2
#define pin3 BIT3
#define pin4 BIT4
#define pin5 BIT5
#define pin6 BIT6
#define pin7 BIT7

#define GPIOOFF 0x0000

typedef enum {
    PUERTO1,
    PUERTO2
}gpioport_t ;

typedef enum {
    output,
    input
}gpioinit_t ;


void gpioInit(gpioport_t puerto,int pin,gpioinit_t modo);
void DigitalOutputActivate(gpioport_t puerto,int pin);
void DigitalOutputDeactivate(gpioport_t puerto,int pin);
bool DigitalReadInput(gpioport_t puerto,int pin);


#endif /* GPIO_H_ */
