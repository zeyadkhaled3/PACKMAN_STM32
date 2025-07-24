/*
 * MSPI_program.c
 *
 *  Created on: Aug 27, 2024
 *      Author: ahmed
 */

#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "MSPI_private.h"
#include "MSPI_interface.h"
#include "MSYSTICK_interface.h"

void MSPI_MasterInit()
{

	SET(SPI1->SPI_CR1,1);//clk polarity

	SET(SPI1->SPI_CR1,2);//master select
	SET(SPI1->SPI_CR1,6);//SPI enable

}
void MSPI_SlaveInit()
{
	SET(SPI1->SPI_CR1,1);//clk polarity

	CLR(SPI1->SPI_CR1,2);//slave select

	SET(SPI1->SPI_CR1,6);//SPI enable

}
u8   MSPITrancieve(u8 Copy_u8Data)
{

	SPI1->SPI_DR=Copy_u8Data;

	while((GET(SPI1->SPI_SR,7))==1);
	return 0;
}
