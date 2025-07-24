/*
 * TFT_interface.h
 *
 *  Created on: Aug 29, 2024
 *      Author: ahmed
 */

#ifndef TFT_INTERFACE_H_
#define TFT_INTERFACE_H_

#define TFT_RED          0xf960
#define TFT_YELLOW       0xffe0
#define TFT_GREEN        0x07e1
#define TFT_ORANGE       0xfde0
#define TFT_WHITE        0xffff
#define TFT_BLACK        0x0000
#define TFT_VIOLET       0xb81f
#define TFT_PINK         0xf2bf
#define TFT_BLUE         0x01df
#define TFT_DARK_RED     0xc000
#define TFT_DARK_BLUE    0x0035
#define TFT_LIGHT_BLUE   0x04df
#define TFT_BROWN        0xa221
void TFT_Init(void);
void TFT_SendData(u8 Data);
void TFT_SendCommand(u8 Command);
void TFT_SendColor(u16 Color);
void TFT_DrawRectangle(u8 Xstart,u8 Ystart,u16 Xend,u16 Yend,u16 Color);
void TFT_DrawPixel(u8 x,u8 y,u16 color);

#endif /* TFT_INTERFACE_H_ */
