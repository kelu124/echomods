/**
  ******************************************************************************
  * @file    micokit_ext_def.h
  * @author  Eshen Wang
  * @version V1.0.0
  * @date    20-May-2015
  * @brief   micokit extension board peripherals pin defines.
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

#ifndef __MICOKIT_EXT_DEF_H_
#define __MICOKIT_EXT_DEF_H_

#include "MICOPlatform.h"

//-------------------------- MicoKit-EXT board pin define ----------------------
#define MICO_EXT_OLED_SPI_PORT       (Arduino_SPI)
#define MICO_EXT_OLED_SPI_SCK        (Arduino_SCK)       
#define MICO_EXT_OLED_SPI_DIN        (Arduino_SI)  
#define MICO_EXT_OLED_SPI_DC         (Arduino_SO)  
#define MICO_EXT_OLED_SPI_CS         (Arduino_CS)

#define MICO_EXT_RGB_LED_P9813_CIN   (Arduino_SCL)
#define MICO_EXT_RGB_LED_P9813_DIN   (Arduino_SDA)

#define MICO_EXT_DC_MOTOR            (Arduino_D9)

#define MICO_EXT_KEY1                (Arduino_D4)
#define MICO_EXT_KEY2                (Arduino_D5)

#define MICO_EXT_I2C_BME280          (Arduino_I2C)
#define MICO_EXT_DHT11               (Arduino_D8)

#define MICO_EXT_ADC_LIGHT           (Arduino_A2)
#define MICO_EXT_ADC_INFRARED        (Arduino_A3)


#endif  // __MICOKIT_EXT_DEF_H_
