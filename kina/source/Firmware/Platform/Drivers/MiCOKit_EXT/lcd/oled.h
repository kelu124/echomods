/**
******************************************************************************
* @file    oled.h 
* @author  Eshen Wang
* @version V1.0.0
* @date    17-Mar-2015
* @brief     OLED controller. 
  operation
******************************************************************************
* @attention
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
* TIME. AS A RESULT, MXCHIP Inc. SHALL NOT BE HELD LIABLE FOR ANY
* DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
* CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
* <h2><center>&copy; COPYRIGHT 2014 MXCHIP Inc.</center></h2>
******************************************************************************
*/ 

#ifndef __OLED_H_
#define __OLED_H_


#include "stdlib.h"
#include "MICOPlatform.h"

#define OLED_MODE 0
#define SIZE 16
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	

// typedef
#define u8     uint8_t
#define u16    uint16_t
#define u32    uint32_t

// SPI pin
//         OLED PIN  <---------->  EXT-BOARD PIN
#ifdef USE_MiCOKit_EXT
  #include "micokit_ext_def.h"
  #define OLED_SPI_PORT             MICO_EXT_OLED_SPI_PORT
  #define OLED_SPI_SCK              MICO_EXT_OLED_SPI_SCK
  #define OLED_SPI_DIN              MICO_EXT_OLED_SPI_DIN
  #define OLED_SPI_DC               MICO_EXT_OLED_SPI_DC
  #define OLED_SPI_CS               MICO_EXT_OLED_SPI_CS
#else
  #define OLED_SPI_PORT             MICO_SPI_NONE
  #define OLED_SPI_SCK              MICO_GPIO_NONE
  #define OLED_SPI_DIN              MICO_GPIO_NONE
  #define OLED_SPI_DC               MICO_GPIO_NONE
  #define OLED_SPI_CS               MICO_GPIO_NONE
#endif

//----------------- OLED PIN ----------------  	
#define OLED_DC_INIT()     MicoGpioInitialize( (mico_gpio_t)OLED_SPI_DC, OUTPUT_PUSH_PULL );  // in case spi flash is wrote

#define OLED_CS_Clr()      MicoGpioOutputLow(OLED_SPI_CS)  //CS
#define OLED_CS_Set()      MicoGpioOutputHigh(OLED_SPI_CS)

#define OLED_DC_Clr()      MicoGpioOutputLow(OLED_SPI_DC)  //DC
#define OLED_DC_Set()      MicoGpioOutputHigh(OLED_SPI_DC)

#define OLED_RST_Clr()
#define OLED_RST_Set()

//PC0~7,作为数据线
#define DATAOUT(x)           GPIO_Write(GPIOC,x);//输出  
//使用4线串行接口时使用 

#define OLED_SCLK_Clr() MicoGpioOutputLow(OLED_SPI_SCK)  //CLK
#define OLED_SCLK_Set() MicoGpioOutputHigh(OLED_SPI_SCK)

#define OLED_SDIN_Clr() MicoGpioOutputLow(OLED_SPI_DIN)  //DIN
#define OLED_SDIN_Set() MicoGpioOutputHigh(OLED_SPI_DIN)
	     
#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据

//-------------------------------- display define ------------------------------
// for 8*16 char can only display 4 rows, 16 chars each row.
#define OLED_DISPLAY_ROW_1    0    // yellow
#define OLED_DISPLAY_ROW_2    2    // blue
#define OLED_DISPLAY_ROW_3    4    // blue
#define OLED_DISPLAY_ROW_4    6    // blue

#define OLED_DISPLAY_COLUMN_START    0    // colloum from left pos 0

#define OLED_DISPLAY_MAX_CHAR_PER_ROW    16   // max 16 chars each row


//OLED控制用函数
void OLED_WR_Byte(u8 dat,u8 cmd);	    
void OLED_Display_On(void);
void OLED_Display_Off(void);	  

void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void OLED_ShowChar(u8 x,u8 y,u8 chr);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);

void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_ShowCHinese(u8 x,u8 y,u8 no);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);

void delay_init(void);
void delay_ms(u16 nms);
void delay_us(u32 nus);


/*-------------------------------------------------------- USER INTERFACES -----------------------------------------*/
void OLED_Init(void);
void OLED_Clear(void);
void OLED_ShowString(u8 x,u8 y, u8 *p);


#endif  
	 



