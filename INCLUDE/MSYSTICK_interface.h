/*
 * MSYSTICK_interface.h
 *
 *  Created on: Aug 2, 2024
 *      Author: ahmed
 */

#ifndef MSYSTICK_INTERFACE_H_
#define MSYSTICK_INTERFACE_H_



typedef enum
{
	SYSTICKEnable,
	SYSTICKDisable
}SYSTICKState;

void MSYSYTICK_voidInit(void);
void MSYSYTICK_voidStart(u32 Copy_u32Loadvalue);



void MSYSYTICK_voidDelayus(u32 Copy_u32Delayvalue);

void MSYSYTICK_voidDelayms(u32 Copy_u32Delayvalue);

u8   MSYSYTICK_voidReadFlag(void);

void MSYSYTICK_voidCtrlIntState(SYSTICKState Copy_State );

u32  MSTK_u32GetElapsedTime(void);

u32  MSTK_u32GetRemainingTime(void);
void MSYSTICK_voidInterruptms(u32 Copy_u32Delayvalue);
void MSYSTICK_voidInterruptus(u32 Copy_u32Delayvalue);

void MSYSTICK_voidCallBack(void (*ptr)(void));

void MSYSTICK_voidDisable(void);









#endif /* MSYSTICK_INTERFACE_H_ */
