/*
 * TFT_program.c
 *  Created on: Jul 24, 2025
 *      
 */

#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "MRCC_interface.h"
#include "MGPIO_interface.h"
#include "MSYSTICK_interface.h"
#include "MSPI_interface.h"
#include "TFT_interface.h"


void TFT_Init(void)
{

	u8 MADACTL=1<<7 | 1<<6;

	//reset
	MGPIO_SetPinValue(PORT_A,PIN_1,OUT_HIGH);
	MSYSYTICK_voidDelayus(100);
	MGPIO_SetPinValue(PORT_A,PIN_1,OUT_LOW);
	MSYSYTICK_voidDelayus(10);
	MGPIO_SetPinValue(PORT_A,PIN_1,OUT_HIGH);
	MSYSYTICK_voidDelayus(100);
	MGPIO_SetPinValue(PORT_A,PIN_1,OUT_LOW);
	MSYSYTICK_voidDelayus(100);
	MGPIO_SetPinValue(PORT_A,PIN_1,OUT_HIGH);
	MSYSYTICK_voidDelayms(120);
	//commands

	TFT_SendCommand(0x11);//sleepout
	MSYSYTICK_voidDelayms(150);
	TFT_SendCommand(0x3A);//COLMOD
	TFT_SendData(0x5);
	TFT_SendCommand(0x21);//INVERSIONS OFF
	TFT_SendCommand(0x36);//MADCTL
	TFT_SendData(MADACTL);
	TFT_SendCommand(0x29);//DISPLAYON


}
void TFT_SendData(u8 Data)
{

	MGPIO_SetPinValue(PORT_A,PIN_2,OUT_HIGH);
	MSPITrancieve(Data);
}


void TFT_SendCommand(u8 Command)
{

	MGPIO_SetPinValue(PORT_A,PIN_2,OUT_LOW);

	MSPITrancieve(Command);


}
void TFT_SendColor(u16 Color)
{

	MGPIO_SetPinValue(PORT_A,PIN_2,OUT_HIGH);

	u8 True_color=(u8)(Color>>8);
	u8 part2=(u8)(Color);
	MSPITrancieve(True_color);
	MSPITrancieve(part2);
}
void TFT_DrawRectangle(u8 Xstart,u8 Ystart,u16 Xend,u16 Yend,u16 Color)
{
	u32 pixel_number=(Xend-Xstart+1)*(Yend-Ystart+1);
	TFT_SendCommand(0x2A);//x
	TFT_SendData(0);
	TFT_SendData(Xstart);
	TFT_SendData((u8)(Xend>>8));
	TFT_SendData((u8)Xend);
	///////////
	TFT_SendCommand(0x2B);//y
	TFT_SendData(0);
	TFT_SendData(Ystart);
	TFT_SendData((u8)(Yend>>8));
	TFT_SendData((u8)Yend);
	TFT_SendCommand(0x2c);
	for(u32 i=0;i<pixel_number;i++)
	{
		TFT_SendColor(Color);
	}
}
void TFT_DrawPixel(u8 x,u8 y,u16 color)
{
	TFT_SendCommand(0x2A);//x
	TFT_SendData(0);
	TFT_SendData(x);
	TFT_SendData(0);
	TFT_SendData(x);
	///////////
	TFT_SendCommand(0x2B);//y
	TFT_SendData(0);
	TFT_SendData(y);
	TFT_SendData(0);
	TFT_SendData(y);
	TFT_SendCommand(0x2c);
	TFT_SendColor(color);

}



