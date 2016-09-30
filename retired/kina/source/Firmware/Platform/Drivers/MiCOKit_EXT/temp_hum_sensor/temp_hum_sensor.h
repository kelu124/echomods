/**
******************************************************************************
* @file    temp_hum_sensor.h 
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

#ifndef __TEMP_HUM_SENSOR_H_
#define __TEMP_HUM_SENSOR_H_

#include "Common.h"

typedef enum {
  MICOKIT_TEMP_HUM_SENSOR_BME280 = 0,
  MICOKIT_TEMP_HUM_SENSOR_DHT11
}temp_hum_sensor_type_t;

OSStatus temp_hum_sensor_init(void);
OSStatus temp_hum_sensor_read(int32_t *temperature,  uint32_t *humidity);

#endif  // __TEMP_HUM_SENSOR_H_
