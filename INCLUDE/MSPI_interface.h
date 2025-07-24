/*
 * MSPI_interface.h
 *
 *  Created on: Aug 27, 2024
 *      Author: ahmed
 */

#ifndef MSPI_INTERFACE_H_
#define MSPI_INTERFACE_H_

#define SPI_1 0
#define SPI_2 1
#define SPI_3 2
#define SPI_4 3

#define SPI_8Bit  0
#define SPI_16Bit 1

#define SPI_CLKPRE_2   0
#define SPI_CLKPRE_4   1
#define SPI_CLKPRE_8   2
#define SPI_CLKPRE_16  3
#define SPI_CLKPRE_32  4
#define SPI_CLKPRE_64  5
#define SPI_CLKPRE_128 6
#define SPI_CLKPRE_256 7


void MSPI_MasterInit();
void MSPI_SlaveInit();
u8   MSPITrancieve(u8 Copy_u8Data);


#endif /* MSPI_INTERFACE_H_ */
