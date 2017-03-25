/**
******************************************************************************
* @file    DHT11.h 
* @author  Eshen Wang
* @version V1.0.0
* @date    1-May-2015
* @brief   DHT11 operation. 
  operation
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

#ifndef __DHT11_H_
#define __DHT11_H_

#include "MICOPlatform.h"

//---------------------------------- PIN DEFINES -------------------------------

// data pin
//      DHT11 PIN   <------->  EXT-BOARD PIN
#ifdef USE_MiCOKit_EXT
  #include "micokit_ext_def.h"
  #define DHT11_DATA             MICO_EXT_DHT11  // PA11
#else
  #define DHT11_DATA             MICO_GPIO_NONE  // PA11
#endif

// Set GPIO Direction
#define DHT11_IO_IN()          MicoGpioInitialize( (mico_gpio_t)DHT11_DATA, INPUT_PULL_UP );										 
#define DHT11_IO_OUT()         MicoGpioInitialize( (mico_gpio_t)DHT11_DATA, OUTPUT_PUSH_PULL );
	
// Set Data output state
#define DHT11_DATA_Clr()       MicoGpioOutputLow(DHT11_DATA) 
#define DHT11_DATA_Set()       MicoGpioOutputHigh(DHT11_DATA)

// get DATA input state
#define	DHT11_DQ_IN            MicoGpioInputGet(DHT11_DATA)

//-------------------------------- USER INTERFACES -----------------------------

uint8_t DHT11_Init(void); //Init DHT11
uint8_t DHT11_Read_Data(uint8_t *temperature,uint8_t *humidity); //Read DHT11 Value
uint8_t DHT11_Read_Byte(void);//Read One Byte
uint8_t DHT11_Read_Bit(void);//Read One Bit
uint8_t DHT11_Check(void);//Chack DHT11
void DHT11_Rst(void);//Reset DHT11  

// delay func
//void Delay_Init(uint8_t SYSCLK);
void Delay_ms(uint16_t nms);
void Delay_us(uint32_t nus);

#endif  // __DHT11_H_
