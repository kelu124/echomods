/**
******************************************************************************
* @file    micokit_ext.c
* @author  Eshen Wang
* @version V1.0.0
* @date    8-May-2015
* @brief   micokit extension board peripherals operations..
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

#include "MicoPlatform.h"
#include "MICONotificationCenter.h"
#include "micokit_ext.h"

#define micokit_ext_log(M, ...) custom_log("MICOKIT_EXT", M, ##__VA_ARGS__)
#define micokit_ext_log_trace() custom_log_trace("MICOKIT_EXT")

//------------------------------------- API ------------------------------------
OSStatus user_modules_init(void)
{
  OSStatus err = kUnknownErr;
  char oled_show_line[16] = {'\0'};   // max char each line
  
  // init DC Motor(GPIO)
  dc_motor_init();
  dc_motor_set(0);   // off
  
  // init RGB LED(P9813)
  rgb_led_init();
  rgb_led_open(0, 0, 0);  // off
  
  // init OLED
  OLED_Init();
  OLED_Clear();
  snprintf(oled_show_line, 16, "%s", "MXCHIP Inc.");
  OLED_ShowString(0,0,(uint8_t*)oled_show_line);
  memset(oled_show_line, '\0', 16);
  snprintf(oled_show_line, 16, "%s", (uint8_t*)MODEL);
  OLED_ShowString(0,3,(uint8_t*)oled_show_line);
  OLED_ShowString(0,6,"Starting...     ");
  
  // init Light sensor(ADC)
  light_sensor_init();
  
  // init infrared sensor(ADC)
  infrared_reflective_init();
  
  // init user key1 && key2
  user_key1_init();
  user_key2_init();
  
  err = temp_hum_sensor_init();
  
//  int32_t temperature;
//  uint32_t humidity;
//  
//  while(1){
//  err = temp_hum_sensor_read( &temperature,  &humidity );
//  if( err == kNoErr ){
//    platform_log( "temperature: %d, humidity = %d ", temperature, humidity);
//  }
//  sleep(1);
//  }
  
  return err;
}

OSStatus micokit_ext_init(void)
{
  OSStatus err = kUnknownErr;
  err = user_modules_init();
  
  return err;
}
