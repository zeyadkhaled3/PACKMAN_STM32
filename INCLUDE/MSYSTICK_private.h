/*
 * MSYSTICK_private.h
 *
 *  Created on: Aug 2, 2024
 *      Author: ahmed
 */

#ifndef MSYSTICK_PRIVATE_H_
#define MSYSTICK_PRIVATE_H_


#define SYSTICK_BASE_ADRESS   (0xE000E010)


#define TickInt 1
#define CountFlag 16
#define ClockSource 2

#define AHB_DIVIDEBY8 0
#define AHB 1

typedef struct
{
	u32 STK_CTRL;
	u32 STK_LOAD;
	u32 STK_VAL;
	u32 STK_CALIB;

}MSYSTICK_t;


#define SYSTEM_TIMER       ((volatile MSYSTICK_t*)(SYSTICK_BASE_ADRESS))











#endif /* MSYSTICK_PRIVATE_H_ */
