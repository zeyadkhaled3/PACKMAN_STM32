/*
 * MGPIO_interface.h
 *
 *  Created on: Jul 20, 2024
 *      Author: ahmed
 */

#ifndef MGPIO_INTERFACE_H_
#define MGPIO_INTERFACE_H_

#define PORT_A 0
#define PORT_B 1
#define PORT_C 2


#define PIN_0   0
#define PIN_1   1
#define PIN_2   2
#define PIN_3   3
#define PIN_4   4
#define PIN_5   5
#define PIN_6   6
#define PIN_7   7
#define PIN_8   8
#define PIN_9   9
#define PIN_10  10
#define PIN_11  11
#define PIN_12  12
#define PIN_13  13
#define PIN_14  14
#define PIN_15  15


#define INPUT_MODE             0
#define OUTPUT_MODE  		   1
#define ALTERNATIVE_FUNC_MODE  2
#define ANALOG_MODE            3


#define OUT_PUSH_PULL   0
#define OUT_OPEN_DRAIN  1

#define OUT_LOW_SPEED   0
#define OUT_MED_SPEED   1
#define OUT_HIGH_SPEED  2
#define OUT_VHIGH_SPEED 3

#define OUT_LOW 0
#define OUT_HIGH 1



#define NO_PULL   0
#define PULL_UP   1
#define PULL_DOWN 2


#define GPIO_MUSK 3



void MGPIO_SetMode(u8 Copy_u8Port,u8 Copy_u8Pin,u8 Copy_u8Mode);

void MGPIO_SetOutputPinMode(u8 Copy_u8Port,u8 Copy_u8Pin,u8 Copy_u8OutMode,u8 Copy_u8Speed);

void MGPIO_SetPinValue(u8 Copy_u8Port,u8 Copy_u8Pin,u8  Copy_u8Data);

void MGPIO_SetInputPinMode(u8 Copy_u8Port,u8 Copy_u8Pin,u8 Copy_u8InputMode);

void MGPIO_GetPinValue(u8 Copy_u8Port,u8 Copy_u8Pin,u8 * Copy_pu8Data);

void MGPIO_SetPortValue(u8 Copy_u8Port,u8 Copy_u8Value);

void MGPIO_SetAlternativeFunction(u8 Copy_u8Port,u8 Copy_u8Pin,u8 Copy_u8AlternativeFunction);









#endif /* MGPIO_INTERFACE_H_ */
