/**
******************************************************************************
* @file    light_sensor.h 
* @author  Eshen Wang
* @version V1.0.0
* @date    1-May-2015
* @brief   light sensor operation. 
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

#ifndef __LIGHT_SENSOR_H_
#define __LIGHT_SENSOR_H_


#include "MICOPlatform.h"

//--------------------------------  pin defines --------------------------------
#ifdef USE_MiCOKit_EXT
  #include "micokit_ext_def.h"
  #define LIGHT_SENSOR_ADC                 MICO_EXT_ADC_LIGHT  // ADC1_4 (PA4)
#else
  #define LIGHT_SENSOR_ADC                 MICO_ADC_NONE  // ADC1_4 (PA4)
#endif

#define LIGHT_SENSOR_ADC_SAMPLE_CYCLE    3

//------------------------------ user interfaces -------------------------------
int light_sensor_init(void);
int light_sensor_read(uint16_t *data);


#endif  // __LIGHT_SENSOR_H_
