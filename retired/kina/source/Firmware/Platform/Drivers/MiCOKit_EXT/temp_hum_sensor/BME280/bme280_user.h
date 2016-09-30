/**
******************************************************************************
* @file    bme280_user.h 
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

#ifndef __BME280_USER_H_
#define __BME280_USER_H_

#include "MICOPlatform.h"

#define s32 int32_t
#define u32 uint32_t

#ifdef USE_MiCOKit_EXT
  #include "micokit_ext_def.h"
  #define BME280_I2C_DEVICE      MICO_EXT_I2C_BME280
#else
  #define BME280_I2C_DEVICE      MICO_I2C_NONE
#endif

OSStatus bme280_sensor_init(void);
OSStatus bme280_data_readout(s32 *v_actual_temp_s32, u32 *v_actual_press_u32, u32 *v_actual_humity_u32);
OSStatus bme280_read_temperature(s32 *v_actual_temp_s32);
OSStatus bme280_read_humidity(u32 *v_actual_humity_u32);
OSStatus bme280_data_pressure(u32 *v_actual_press_u32);
OSStatus bme280_sensor_deinit(void);

#endif  // __BME280_USER_H_
