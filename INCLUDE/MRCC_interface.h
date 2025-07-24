/*
 * MRCC_interface.h
 *
 *  Created on: Jul 19, 2024
 *      Author: ahmed
 */

#ifndef MRCC_INTERFACE_H_
#define MRCC_INTERFACE_H_



void MRCC_voidInit(void);
void MRCC_voidEnable_Clock_Periphral(u8 Copy_u8AddressBus,u8 Copy_u8Periphral);
void MRCC_voidDisable_Clock_Periphral(u8 Copy_u8AddressBus,u8 Copy_u8Periphral);

#define RC_CLOCK 0
#define CRYSTAL_CLOCK 1

#define HSE_CLOCK 1
#define HSI_CLOCK 0


#define AHB1 0
#define AHB2 1
#define APB1 2
#define APB2 3


#define AHB1_GPIOA 0
#define AHB1_GPIOB 1
#define AHB1_GPIOC 2
#define APB2_SYSCONFIG 14
#endif /* MRCC_INTERFACE_H_ */
