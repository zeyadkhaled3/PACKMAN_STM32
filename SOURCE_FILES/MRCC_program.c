
#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"MRCC_private.h"
#include"MRCC_interface.h"
#include"MRCC_config.h"

void MRCC_voidInit(void)
{

	// HSI or HSE
	// CLOCK ON
	//WAIT FOR FLAG --> READY
	// SWITCH CLOCK


/**/
#if (SYS_CLK==HSE_CLOCK)
	#if HSE_TYPE==CRYSTAL_CLOCK

	CLR(RCC->RCC_CR,18);
	SET(RCC->RCC_CR,16);
	while(!GET(RCC->RCC_CR,17))
	{
		asm("NOP" );

	}
	RCC->RCC_CFGR&=~(0b11<<0);
	RCC->RCC_CFGR|=(0b01<<0);
	CLR(RCC->RCC_CR,0);
	#elif (HSE_TYPE==RC_CLOCK)


	SET(RCC->RCC_CR,18);


	#endif




#elif(SYS_CLK==HSI_CLOCK)




#endif
}
void MRCC_voidEnable_Clock_Periphral(u8 Copy_u8AddressBus,u8 Copy_u8Periphral)
{

switch(Copy_u8AddressBus)
{
case AHB1:
	SET(RCC->RCC_AHB1ENR,Copy_u8Periphral);
	break;
case AHB2:
	SET(RCC->RCC_AHB2ENR,Copy_u8Periphral);
	break;
case APB1:
	SET(RCC->RCC_APB1ENR,Copy_u8Periphral);
	break;
case APB2:
	SET(RCC->RCC_APB2ENR,Copy_u8Periphral);
	break;
default:
	break;
}

}

void MRCC_voidDisable_Clock_Periphral(u8 Copy_u8AddressBus,u8 Copy_u8Periphral)
{

	switch(Copy_u8AddressBus)
	{
	case AHB1:
		CLR(RCC->RCC_AHB1ENR,Copy_u8Periphral);
		break;
	case AHB2:
		CLR(RCC->RCC_AHB2ENR,Copy_u8Periphral);
		break;
	case APB1:
		CLR(RCC->RCC_APB1ENR,Copy_u8Periphral);
		break;
	case APB2:
		CLR(RCC->RCC_APB2ENR,Copy_u8Periphral);
		break;
	default:
		break;
	}



}




