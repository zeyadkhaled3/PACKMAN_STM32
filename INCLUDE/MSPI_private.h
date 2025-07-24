/*
 * MSPI_private.h
 *
 *  Created on: Aug 27, 2024
 *      Author: ahmed
 */

#ifndef MSPI_PRIVATE_H_
#define MSPI_PRIVATE_H_

typedef struct
{
	u32 SPI_CR1;
	u32 SPI_CR2;
	u32 SPI_SR;
	u32 SPI_DR;

}MSPI_t;



#define SPI1_BASE_ADDRESS 0x40013000
#define SPI2_BASE_ADDRESS 0x40003800
#define SPI3_BASE_ADDRESS 0x40003C00


#define SPI1    ((volatile MSPI_t*)(SPI1_BASE_ADDRESS))
#define SPI2    ((volatile MSPI_t*)(SPI2_BASE_ADDRESS))
#define SPI3    ((volatile MSPI_t*)(SPI3_BASE_ADDRESS))





#endif /* MSPI_PRIVATE_H_ */
