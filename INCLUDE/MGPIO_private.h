/*
 * MGPIO_private.h
 *
 *  Created on: Jul 20, 2024
 *      Author: ahmed
 */
#ifndef MGPIO_PRIVATE_H_
#define MGPIO_PRIVATE_H_

#define GPIOA_BASE_ADRESS   0x40020000
#define GPIOB_BASE_ADRESS   0x40020400
#define GPIOC_BASE_ADRESS   0x40020800

typedef struct
{
	u32  MODER;
	u32  OTYPER;
	u32  OSPEEDR;
	u32  PUPDR;
	u32  IDR;
	u32  ODR;
	u32  BSRR;
	u32  LCKR;
	u32  AFRL;
	u32  AFRH;
}MGPIOX_t;


#define GPIOA       ((volatile MGPIOX_t*)(GPIOA_BASE_ADRESS))
#define GPIOB       ((volatile MGPIOX_t*)(GPIOB_BASE_ADRESS))
#define GPIOC       ((volatile MGPIOX_t*)(GPIOC_BASE_ADRESS))



#endif /* MGPIO_PRIVATE_H_ */
