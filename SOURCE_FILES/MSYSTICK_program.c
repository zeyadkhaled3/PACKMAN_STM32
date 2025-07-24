/*
 * MSYSTICK_program.c
 *
 *  Created on: Aug 2, 2024
 *      Author: ahmed
 */

#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "MSYSTICK_private.h"
#include "MSYSTICK_config.h"
#include "MSYSTICK_interface.h"

static void (*Global_SYSTICKPtr)(void);

void MSYSYTICK_voidInit(void)
{
#if SYSTICK_SOURCE==AHB

	SYSTEM_TIMER->STK_CTRL |=1<<ClockSource;

#elif SYSTICK_SOURCE==AHB_DIVIDEBY8

	SYSTEM_TIMER->STK_CTRL &=~(1<<ClockSource);

#endif

}

void MSYSYTICK_voidStart(u32 Copy_u32Loadvalue)
{
	SYSTEM_TIMER->STK_LOAD=Copy_u32Loadvalue;
	SYSTEM_TIMER->STK_VAL=0;
	SYSTEM_TIMER->STK_CTRL |=1;

}

void MSYSYTICK_voidDelayus(u32 Copy_u32Delayvalue)
{
	SYSTEM_TIMER->STK_CTRL &=~(1);

#if SYSTICK_SOURCE==AHB
	MSYSYTICK_voidCtrlIntState(SYSTICKDisable);
	MSYSYTICK_voidStart(16*Copy_u32Delayvalue);
	while(MSYSYTICK_voidReadFlag()==0);

#elif SYSTICK_SOURCE==AHB_DIVIDEBY8

	MSYSYTICK_voidCtrlIntState(SYSTICKDisable);
	MSYSYTICK_voidStart(2*Copy_u32Delayvalue);
	while(MSYSYTICK_voidReadFlag()==0);
#endif
	SYSTEM_TIMER->STK_CTRL &=~(1);

}

void MSYSYTICK_voidDelayms(u32 Copy_u32Delayvalue)
{
	SYSTEM_TIMER->STK_CTRL &=~(1);

#if SYSTICK_SOURCE==AHB

	MSYSYTICK_voidCtrlIntState(SYSTICKDisable);
	MSYSYTICK_voidStart(16000*Copy_u32Delayvalue);
	while(MSYSYTICK_voidReadFlag()==0);
#elif SYSTICK_SOURCE==AHB_DIVIDEBY8
	MSYSYTICK_voidCtrlIntState(SYSTICKDisable);
	MSYSYTICK_voidStart(2000*Copy_u32Delayvalue);
	while(MSYSYTICK_voidReadFlag()==0);


#endif

	SYSTEM_TIMER->STK_CTRL &=~(1);




}

u8   MSYSYTICK_voidReadFlag(void)
{
	u8 flag=((SYSTEM_TIMER->STK_CTRL)>>CountFlag)&1;
	if(flag==1)
	{
		u8 dummy=GET(SYSTEM_TIMER->STK_CTRL,CountFlag);
		dummy++;
	}
	return flag;
}

void MSYSYTICK_voidCtrlIntState(SYSTICKState Copy_State )
{
	switch(Copy_State)
	{
	case SYSTICKEnable:
		SYSTEM_TIMER->STK_CTRL |=1<<TickInt;
		break;
	case SYSTICKDisable:
		SYSTEM_TIMER->STK_CTRL &=~(1<<TickInt);
		break;
	}
}

u32  MSTK_u32GetElapsedTime(void)
{

	return ((SYSTEM_TIMER->STK_LOAD)-(SYSTEM_TIMER->STK_VAL));
}

u32  MSTK_u32GetRemainingTime(void)
{

	return (SYSTEM_TIMER->STK_VAL);
}






/////




void MSYSTICK_voidInterruptms(u32 Copy_u32Delayvalue)
{
	SYSTEM_TIMER->STK_CTRL &=~(1);

#if SYSTICK_SOURCE==AHB


	SYSTEM_TIMER->STK_LOAD=16000*Copy_u32Delayvalue;
	SYSTEM_TIMER->STK_VAL=0;
	SYSTEM_TIMER->STK_CTRL |=2;
	SYSTEM_TIMER->STK_CTRL |=1;
#elif SYSTICK_SOURCE==AHB_DIVIDEBY8

	SYSTEM_TIMER->STK_LOAD=2000*Copy_u32Delayvalue;
	SYSTEM_TIMER->STK_VAL=0;
	SYSTEM_TIMER->STK_CTRL |=2;
	SYSTEM_TIMER->STK_CTRL |=1;

#endif


}
///set callback Systick
void MSYSTICK_voidInterruptus(u32 Copy_u32Delayvalue)
{
	SYSTEM_TIMER->STK_CTRL &=~(1);

#if SYSTICK_SOURCE==AHB


	SYSTEM_TIMER->STK_LOAD=16*Copy_u32Delayvalue;
	SYSTEM_TIMER->STK_VAL=0;
	SYSTEM_TIMER->STK_CTRL |=2;
	SYSTEM_TIMER->STK_CTRL |=1;
#elif SYSTICK_SOURCE==AHB_DIVIDEBY8

	SYSTEM_TIMER->STK_LOAD=2*Copy_u32Delayvalue;
	SYSTEM_TIMER->STK_VAL=0;
	SYSTEM_TIMER->STK_CTRL |=2;
	SYSTEM_TIMER->STK_CTRL |=1;

#endif


}

void MSYSTICK_voidCallBack(void (*ptr)(void))
{
	Global_SYSTICKPtr=ptr;

}




void SysTick_Handler(void){
	Global_SYSTICKPtr();
	///flag is cleared automatically
	//SYSTEM_TIMER->STK_CTRL |=1<<CountFlag;
	//SYSTEM_TIMER->STK_CTRL &=~(1);

}



void MSYSTICK_voidDisable(void)
{

	SYSTEM_TIMER->STK_CTRL &=~(1);

}








