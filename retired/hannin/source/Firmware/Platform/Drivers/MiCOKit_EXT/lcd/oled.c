/**
******************************************************************************
* @file    oled.c
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

#include "oled.h"
#include "stdlib.h"
#include "oledfont.h"  	 
//#include "delay.h"
#include "MICO.h"
#include "platform.h"


extern const platform_spi_t        platform_spi_peripherals[];
extern platform_spi_driver_t       platform_spi_drivers[];
extern const platform_gpio_t       platform_gpio_pins[];

/* SPI5 for OLED */
const mico_spi_device_t micokit_spi_oled =
{
    .port        = OLED_SPI_PORT,
    .chip_select = OLED_SPI_CS,
    .speed       = 20000000,
    .mode        = (SPI_CLOCK_RISING_EDGE | SPI_CLOCK_IDLE_HIGH | SPI_USE_DMA | SPI_MSB_FIRST),
    .bits        = 8
};

  
uint8_t spi_tx_buffer = 0;
//mico_spi_message_segment_t oled_spi_msg = {
//  &spi_tx_buffer, NULL, 0
//};

//OLED的显存
//存放格式如下.
//[0]0 1 2 3 ... 127	
//[1]0 1 2 3 ... 127	
//[2]0 1 2 3 ... 127	
//[3]0 1 2 3 ... 127	
//[4]0 1 2 3 ... 127	
//[5]0 1 2 3 ... 127	
//[6]0 1 2 3 ... 127	
//[7]0 1 2 3 ... 127 			   

#if OLED_MODE==1
//向SSD1106写入一个字节。
//dat:要写入的数据/命令
//cmd:数据/命令标志 0,表示命令;1,表示数据;
void OLED_WR_Byte(u8 dat,u8 cmd)
{
  DATAOUT(dat);	    
  if(cmd)
    OLED_DC_Set();
  else 
    OLED_DC_Clr();		   
  OLED_CS_Clr();
  OLED_WR_Clr();	 
  OLED_WR_Set();
  OLED_CS_Set();	  
  OLED_DC_Set();	 
} 	    	    
#else
//向SSD1106写入一个字节。
//dat:要写入的数据/命令
//cmd:数据/命令标志 0,表示命令;1,表示数据;
void OLED_WR_Byte(u8 dat,u8 cmd)
{  
  platform_spi_config_t config;
  platform_spi_message_segment_t oled_spi_msg =
            { &dat,            NULL,       (unsigned long) 1 };

  config.chip_select = &platform_gpio_pins[micokit_spi_oled.chip_select];
  config.speed       = micokit_spi_oled.speed;
  config.mode        = micokit_spi_oled.mode;
  config.bits        = micokit_spi_oled.bits;
  
  if( platform_spi_drivers[micokit_spi_oled.port].spi_mutex == NULL)
    mico_rtos_init_mutex( &platform_spi_drivers[micokit_spi_oled.port].spi_mutex );

  mico_rtos_lock_mutex( &platform_spi_drivers[micokit_spi_oled.port].spi_mutex );

  platform_spi_init( &platform_spi_drivers[micokit_spi_oled.port], &platform_spi_peripherals[micokit_spi_oled.port], &config );
  OLED_DC_INIT();   

  if(cmd)
    OLED_DC_Set();
  else 
    OLED_DC_Clr();		  

  platform_spi_transfer( &platform_spi_drivers[micokit_spi_oled.port], &config, &oled_spi_msg, 1 );
  
  OLED_DC_Set();   

  mico_rtos_unlock_mutex( &platform_spi_drivers[micokit_spi_oled.port].spi_mutex );
} 
#endif

void OLED_Set_Pos(unsigned char x, unsigned char y) 
{
  OLED_WR_Byte(0xb0+y,OLED_CMD);
  OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
  OLED_WR_Byte((x&0x0f)|0x01,OLED_CMD); 
}   	  
//开启OLED显示    
void OLED_Display_On(void)
{
  OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
  OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
  OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}
//关闭OLED显示     
void OLED_Display_Off(void)
{
  OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
  OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
  OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}		   			 
//清屏函数,清完屏,整个屏幕是黑色的!和没点亮一样!!!	  
void OLED_Clear(void)  
{  
  u8 i,n;		    
  for(i=0;i<8;i++)  
  {  
    OLED_WR_Byte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
    OLED_WR_Byte (0x00,OLED_CMD);      //设置显示位置—列低地址
    OLED_WR_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址   
    for(n=0;n<128;n++)OLED_WR_Byte(0,OLED_DATA); 
  } //更新显示
}


//在指定位置显示一个字符,包括部分字符
//x:0~127
//y:0~63
//mode:0,反白显示;1,正常显示				 
//size:选择字体 16/12 
void OLED_ShowChar(u8 x,u8 y,u8 chr)
{      	
  unsigned char c=0,i=0;	
  c=chr-' ';//得到偏移后的值			
  if(x>Max_Column-1){x=0;y=y+2;}
  if(SIZE ==16)
  {
    OLED_Set_Pos(x,y);	
    for(i=0;i<8;i++)
      OLED_WR_Byte(F8X16[c*16+i],OLED_DATA);
    OLED_Set_Pos(x,y+1);
    for(i=0;i<8;i++)
      OLED_WR_Byte(F8X16[c*16+i+8],OLED_DATA);
  }
  else {	
    OLED_Set_Pos(x,y+1);
    for(i=0;i<6;i++)
      OLED_WR_Byte(F6x8[c][i],OLED_DATA);
    
  }
}
//m^n函数
u32 oled_pow(u8 m,u8 n)
{
  u32 result=1;	 
  while(n--)result*=m;    
  return result;
}				  
//显示2个数字
//x,y :起点坐标	 
//len :数字的位数
//size:字体大小
//mode:模式	0,填充模式;1,叠加模式
//num:数值(0~4294967295);	 		  
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size)
{         	
  u8 t,temp;
  u8 enshow=0;						   
  for(t=0;t<len;t++)
  {
    temp=(num/oled_pow(10,len-t-1))%10;
    if(enshow==0&&t<(len-1))
    {
      if(temp==0)
      {
        OLED_ShowChar(x+(size/2)*t,y,' ');
        continue;
      }else enshow=1; 
      
    }
    OLED_ShowChar(x+(size/2)*t,y,temp+'0'); 
  }
} 
//显示一个字符号串
void OLED_ShowString(u8 x,u8 y,u8 *chr)
{
  unsigned char j=0;
  u8 x_t = x,y_t = y;
  
  while (chr[j]!='\0')
  {	
    // add for CR/LF
    if( ('\r' == chr[j]) && ('\n' == chr[j+1]) ){  // CR LF
      while(x_t <= 120){  // fill rest chars in current line
        OLED_ShowChar(x_t,y_t,' ');
        x_t += 8;
      }
      j += 2;
    }
    else if( ('\r' == chr[j]) || ('\n' == chr[j]) ){   // CR or LF
      while(x_t <= 120){  // fill rest chars in current line
        OLED_ShowChar(x_t,y_t,' ');
        x_t += 8;
      }
      j += 1;
    }
    else{
      if(x_t>120){  // line end, goto next line
        x_t = 0;
        y_t += 2;
        if(y_t >= 8){  // can only display 4 line
          break;
        }
      }
      OLED_ShowChar(x_t,y_t,chr[j]);
      x_t += 8;
      j++;
    }
  }
}

//显示汉字
void OLED_ShowCHinese(u8 x,u8 y,u8 no)
{      			    
  u8 t,adder=0;
  OLED_Set_Pos(x,y);	
  for(t=0;t<16;t++)
  {
    OLED_WR_Byte(Hzk[2*no][t],OLED_DATA);
    adder+=1;
  }	
  OLED_Set_Pos(x,y+1);	
  for(t=0;t<16;t++)
  {	
    OLED_WR_Byte(Hzk[2*no+1][t],OLED_DATA);
    adder+=1;
  }					
}
/***********功能描述：显示显示BMP图片128×64起始点坐标(x,y),x的范围0～127，y为页的范围0～7*****************/
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[])
{ 	
  unsigned int j=0;
  unsigned char x,y;
  
  if(y1%8==0) y=y1/8;      
  else y=y1/8+1;
  for(y=y0;y<y1;y++)
  {
    OLED_Set_Pos(x0,y);
    for(x=x0;x<x1;x++)
    {      
      OLED_WR_Byte(BMP[j++],OLED_DATA);	    	
    }
  }
} 


//初始化SSD1306					    
void OLED_Init(void)
{ 	 
  platform_spi_config_t config;
  config.chip_select = &platform_gpio_pins[micokit_spi_oled.chip_select];
  config.speed       = micokit_spi_oled.speed;
  config.mode        = micokit_spi_oled.mode;
  config.bits        = micokit_spi_oled.bits;

  if( platform_spi_drivers[micokit_spi_oled.port].spi_mutex == NULL)
    mico_rtos_init_mutex( &platform_spi_drivers[micokit_spi_oled.port].spi_mutex );

  mico_rtos_lock_mutex( &platform_spi_drivers[micokit_spi_oled.port].spi_mutex );

  platform_spi_init( &platform_spi_drivers[micokit_spi_oled.port], &platform_spi_peripherals[micokit_spi_oled.port], &config );
  OLED_DC_INIT();  
    
  OLED_DC_Clr();
  OLED_RST_Clr();
  
  OLED_RST_Set();
  delay_ms(100);
  OLED_RST_Clr();
  delay_ms(100);
  OLED_RST_Set(); 

  mico_rtos_unlock_mutex( &platform_spi_drivers[micokit_spi_oled.port].spi_mutex );
  
  OLED_WR_Byte(0xAE,OLED_CMD);//--turn off oled panel
  OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
  OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
  OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
  OLED_WR_Byte(0x81,OLED_CMD);//--set contrast control register
  OLED_WR_Byte(0xCF,OLED_CMD); // Set SEG Output Current Brightness
  OLED_WR_Byte(0xA1,OLED_CMD);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
  OLED_WR_Byte(0xC8,OLED_CMD);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
  OLED_WR_Byte(0xA6,OLED_CMD);//--set normal display
  OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
  OLED_WR_Byte(0x3f,OLED_CMD);//--1/64 duty
  OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
  OLED_WR_Byte(0x00,OLED_CMD);//-not offset
  OLED_WR_Byte(0xd5,OLED_CMD);//--set display clock divide ratio/oscillator frequency
  OLED_WR_Byte(0x80,OLED_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
  OLED_WR_Byte(0xD9,OLED_CMD);//--set pre-charge period
  OLED_WR_Byte(0xF1,OLED_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
  OLED_WR_Byte(0xDA,OLED_CMD);//--set com pins hardware configuration
  OLED_WR_Byte(0x12,OLED_CMD);
  OLED_WR_Byte(0xDB,OLED_CMD);//--set vcomh
  OLED_WR_Byte(0x40,OLED_CMD);//Set VCOM Deselect Level
  OLED_WR_Byte(0x20,OLED_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
  OLED_WR_Byte(0x02,OLED_CMD);//
  OLED_WR_Byte(0x8D,OLED_CMD);//--set Charge Pump enable/disable
  OLED_WR_Byte(0x14,OLED_CMD);//--set(0x10) disable
  OLED_WR_Byte(0xA4,OLED_CMD);// Disable Entire Display On (0xa4/0xa5)
  OLED_WR_Byte(0xA6,OLED_CMD);// Disable Inverse Display On (0xa6/a7) 
  OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
  
  OLED_WR_Byte(0xAF,OLED_CMD); /*display ON*/ 
  OLED_Clear();
  OLED_Set_Pos(0,0); 	
}  



////////////////////////////////////////////////////////////////////////////////
void delay_init()	 
{
}

void delay_ms(u16 nms)
{
  mico_thread_msleep(nms);
}



























