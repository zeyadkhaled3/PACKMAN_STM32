/*
 * MGPIO_program.c
 *
 *  Created on: Jul 20, 2024
 *      Author: ahmed
 */


#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "MGPIO_private.h"
#include "MGPIO_interface.h"
void MGPIO_SetMode(u8 Copy_u8Port,u8 Copy_u8Pin,u8 Copy_u8Mode)
{

	switch (Copy_u8Port) {
	case PORT_A:
		GPIOA->MODER &=~(GPIO_MUSK<<(Copy_u8Pin*2));
		GPIOA->MODER |=(Copy_u8Mode<<(Copy_u8Pin*2));
		break;
	case PORT_B:
		GPIOB->MODER &=~(GPIO_MUSK<<(Copy_u8Pin*2));
		GPIOB->MODER |=(Copy_u8Mode<<(Copy_u8Pin*2));
		break;
	case PORT_C:
		GPIOC->MODER &=~(GPIO_MUSK<<(Copy_u8Pin*2));
		GPIOC->MODER |=(Copy_u8Mode<<(Copy_u8Pin*2));
		break;
	default:
		break;
	}

}

void MGPIO_SetOutputPinMode(u8 Copy_u8Port,u8 Copy_u8Pin,u8 Copy_u8OutMode,u8 Copy_u8Speed)
{

	switch (Copy_u8Port) {
	case PORT_A:

		//PUSH_PULL OR OPEN_DRAIN
		// if we have pin as 1 and we want to or it with 0 it have no action and it still 1 so want to clear first
		GPIOA->OTYPER &=~(1<<Copy_u8Pin);
		GPIOA->OTYPER |=(Copy_u8OutMode<<Copy_u8Pin);

		//SPEED
		GPIOA->OSPEEDR &=~(GPIO_MUSK<<(Copy_u8Pin*2));
		GPIOA->OSPEEDR |=(Copy_u8Speed<<(Copy_u8Pin*2));


		break;
	case PORT_B:
		//PUSH_PULL OR OPEN_DRAIN
		GPIOB->OTYPER &=~(1<<Copy_u8Pin);
		GPIOB->OTYPER |=(Copy_u8OutMode<<Copy_u8Pin);

		//SPEED
		GPIOB->OSPEEDR &=~(GPIO_MUSK<<(Copy_u8Pin*2));
		GPIOB->OSPEEDR |=(Copy_u8Speed<<(Copy_u8Pin*2));
		break;
	case PORT_C:
		//PUSH_PULL OR OPEN_DRAIN
		GPIOC->OTYPER &=~(1<<Copy_u8Pin);
		GPIOC->OTYPER |=(Copy_u8OutMode<<Copy_u8Pin);

		//SPEED
		GPIOC->OSPEEDR &=~(GPIO_MUSK<<(Copy_u8Pin*2));
		GPIOC->OSPEEDR |=(Copy_u8Speed<<(Copy_u8Pin*2));
		break;
	default:
		break;


	}
}


void MGPIO_SetPinValue(u8 Copy_u8Port,u8 Copy_u8Pin,u8  Copy_u8Data)
{
	switch (Copy_u8Port) {
	case PORT_A:
		GPIOA->ODR &=~(1<<Copy_u8Pin);
		GPIOA->ODR |=(Copy_u8Data<<Copy_u8Pin);
		break;
	case PORT_B:
		GPIOB->ODR &=~(1<<Copy_u8Pin);
		GPIOB->ODR |=(Copy_u8Data<<Copy_u8Pin);
		break;
	case PORT_C:
		GPIOC->ODR &=~(1<<Copy_u8Pin);
		GPIOC->ODR |=(Copy_u8Data<<Copy_u8Pin);
		break;
	default:
		break;
	}
}
void MGPIO_SetInputPinMode(u8 Copy_u8Port,u8 Copy_u8Pin,u8 Copy_u8InputMode)
{
	switch(Copy_u8Port)
	{
	case PORT_A:
		GPIOA->PUPDR &=~(3<<(2*Copy_u8Pin));
		GPIOA->PUPDR |=(Copy_u8InputMode<<(2*Copy_u8Pin));
		break;
	case PORT_B:
		GPIOB->PUPDR &=~(3<<(2*Copy_u8Pin));
		GPIOB->PUPDR |=(Copy_u8InputMode<<(2*Copy_u8Pin));
		break;
	case PORT_C:
		GPIOC->PUPDR &=~(3<<(2*Copy_u8Pin));
		GPIOC->PUPDR |=(Copy_u8InputMode<<(2*Copy_u8Pin));
		break;
	default:
		break;
	}


}


void MGPIO_GetPinValue(u8 Copy_u8Port,u8 Copy_u8Pin,u8 * Copy_pu8Data)
{
	u8 pin_value;

	switch(Copy_u8Port)
	{
	case PORT_A:
		pin_value=(GPIOA->IDR &=(1<<(Copy_u8Pin)));
		break;
	case PORT_B:
		pin_value=(GPIOB->IDR &=(1<<(Copy_u8Pin)));

		break;
	case PORT_C:
		pin_value=(GPIOC->IDR &=(1<<(Copy_u8Pin)));

		break;


	default:
		break;
	}
	*Copy_pu8Data=pin_value;

}
void MGPIO_SetPortValue(u8 Copy_u8Port,u8 Copy_u8Value)
{

	switch (Copy_u8Port) {
	case PORT_A:
		GPIOA->ODR &=~(255);
		GPIOA->ODR |=(Copy_u8Value);
		break;
	case PORT_B:
		GPIOB->ODR  &=~(255);
		GPIOB->ODR |=(Copy_u8Value);
		break;
	case PORT_C:
		GPIOC->ODR &=~(255);
		GPIOC->ODR |=(Copy_u8Value);
		break;
	default:
		break;
	}
}


void MGPIO_SetAlternativeFunction(u8 Copy_u8Port,u8 Copy_u8Pin,u8 Copy_u8AlternativeFunction)
{
	if(Copy_u8Pin>=0 && Copy_u8Pin<=7)
	{
		switch (Copy_u8Port) {
		case PORT_A:
			GPIOA->AFRL &=~((15)<<(Copy_u8Pin*4));
			GPIOA->AFRL |=(Copy_u8AlternativeFunction)<<(Copy_u8Pin*4);
			break;
		case PORT_B:
			GPIOB->AFRL &=~((15)<<(Copy_u8Pin*4));
			GPIOB->AFRL |=(Copy_u8AlternativeFunction)<<(Copy_u8Pin*4);
			break;

		default:
			break;
		}
	}
	else if(Copy_u8Pin>=8 && Copy_u8Pin<=15)
	{
		switch (Copy_u8Port) {
		case PORT_A:
			GPIOA->AFRH &=~((15)<<((Copy_u8Pin-8)*4));
			GPIOA->AFRH |=(Copy_u8AlternativeFunction)<<((Copy_u8Pin-8)*4);
			break;
		case PORT_B:
			GPIOB->AFRH &=~((15)<<((Copy_u8Pin-8)*4));
			GPIOB->AFRH |=(Copy_u8AlternativeFunction)<<((Copy_u8Pin-8)*4);
			break;

		default:
			break;
		}

	}

}


