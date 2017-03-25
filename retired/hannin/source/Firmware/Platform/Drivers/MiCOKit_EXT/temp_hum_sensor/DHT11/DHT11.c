/**
******************************************************************************
* @file    DHT11.c
* @author  Eshen Wang
* @version V1.0.0
* @date    1-May-2015
* @brief   DHT11 temperature and humidity sensor driver. 
******************************************************************************
* @attention
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDATAG CUSTOMERS
* WITH CODATAG INFORMATION REGARDATAG THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
* TIME. AS A RESULT, MXCHIP Inc. SHALL NOT BE HELD LIABLE FOR ANY
* DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
* CODATAG INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
* <h2><center>&copy; COPYRIGHT 2014 MXCHIP Inc.</center></h2>
******************************************************************************
*/ 

#include "DHT11.h"

/*------------------------------ delay function ------------------------------*/

void Delay_us(uint32_t nus)
{ 
  MicoNanosendDelay( 1000*nus );
}

void Delay_ms(uint16_t nms)
{	  	  
  mico_thread_msleep(nms);	  	    
}

/*--------------------------------- DHT11 Operations -------------------------*/

//Reset DHT11
void DHT11_Rst(void)	   
{                 
  DHT11_IO_OUT(); 											//SET OUTPUT
  DHT11_DATA_Clr(); 											//GPIOA.0=0
  Delay_ms(20);    											//Pull down Least 18ms
  DHT11_DATA_Set(); 											//GPIOA.0=1 
  Delay_us(30);     										//Pull up 20~40us
}

uint8_t DHT11_Check(void) 	   
{   
  uint8_t retry=0;
  DHT11_IO_IN();												//SET INPUT	 
  while (DHT11_DQ_IN&&retry<100)				//DHT11 Pull down 40~80us
  {
    retry++;
    Delay_us(1);
  }	 
  
  if(retry>=100)
    return 1;
  else 
    retry=0;
  
  while (!DHT11_DQ_IN&&retry<100)				//DHT11 Pull up 40~80us
  {
    retry++;
    Delay_us(1);
  }
  
  if(retry>=100)
    return 1;														//chack error	    
  
  return 0;
}

uint8_t DHT11_Read_Bit(void) 			 
{
  uint8_t retry=0;
  while(DHT11_DQ_IN&&retry<100)					//wait become Low level
  {
    retry++;
    Delay_us(1);
  }
  
  retry=0;
  while(!DHT11_DQ_IN&&retry<100)				//wait become High level
  {
    retry++;
    Delay_us(1);
  }
  
  Delay_us(40);//wait 40us
  
  if(DHT11_DQ_IN)
    return 1;
  else 
    return 0;		   
}

uint8_t DHT11_Read_Byte(void)    
{
  uint8_t i,dat;
  dat=0;
  for (i=0;i<8;i++) 
  {
    dat<<=1; 
    dat|=DHT11_Read_Bit();
  }						    
  
  return dat;
}

uint8_t DHT11_Read_Data(uint8_t *temperature,uint8_t *humidity)    
{        
  uint8_t buf[5];
  uint8_t i;
  DHT11_Rst();
  if(DHT11_Check()==0)
  {
    for(i=0;i<5;i++)
    {
      buf[i]=DHT11_Read_Byte();
    }
    if((buf[0]+buf[1]+buf[2]+buf[3])==buf[4])
    {
      *humidity=buf[0];
      *temperature=buf[2];
    }
  }
  else {
    return 1;
  }
  
  return 0;	    
}

uint8_t DHT11_Init(void)
{	 
  DHT11_IO_OUT();
  
  DHT11_Rst();  
  return DHT11_Check();
} 
