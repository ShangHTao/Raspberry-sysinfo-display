#ifndef __OLED_H
#define __OLED_H
#include <wiringPi.h>
#include <wiringPiI2C.h>

#define u8 unsigned char
#define u32 unsigned int
#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据

#define         SSD1306_I2C_ADDR  0x78
#define         MAX_COLUMN	  128
#define         MAX_ROW		  64

void OLED_Init(int *fd);
void OLED_ColorTurn(int fd,u8 i);
void OLED_DisplayTurn(int fd,u8 i);
void OLED_DisPlay_On(int fd);
void OLED_DisPlay_Off(int fd);
void OLED_Refresh(int fd);
void OLED_Clear(int fd);
void OLED_DrawPoint(u8 x,u8 y);
void OLED_ClearPoint(u8 x,u8 y);
void OLED_DrawLine(u8 x1,u8 y1,u8 x2,u8 y2);
void OLED_DrawCircle(u8 x,u8 y,u8 r);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size1);
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 size1);
u32 OLED_Pow(u8 m,u8 n);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size1);
void OLED_WR_BP(int fd,u8 x,u8 y);
void OLED_ShowPicture(int fd,u8 x0,u8 y0,u8 x1,u8 y1,u8 BMP[]);










#endif
