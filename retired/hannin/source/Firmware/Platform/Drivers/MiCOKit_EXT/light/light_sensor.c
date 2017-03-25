/**
******************************************************************************
* @file    LIGHT_SENSOR.c
* @author  Eshen Wang
* @version V1.0.0
* @date    1-May-2015
* @brief   LIGHT_SENSOR operation. 
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

#include "MICOPlatform.h"
#include "light_sensor.h"

#define light_sensor_log(M, ...) custom_log("LIGHT_SENSOR", M, ##__VA_ARGS__)
#define light_sensor_log_trace() custom_log_trace("LIGHT_SENSOR")

 
/*------------------------------ USER INTERFACES -----------------------------*/

int light_sensor_init(void)
{
  OSStatus err = kUnknownErr;
  
  err = MicoAdcInitialize(LIGHT_SENSOR_ADC, LIGHT_SENSOR_ADC_SAMPLE_CYCLE);
  if(kNoErr != err){
    return -1;
  }
  
  return 0;
}

int light_sensor_read(uint16_t *data)
{
  int ret = 0;
  OSStatus err = kUnknownErr;
  
  // init ADC
  err = MicoAdcInitialize(LIGHT_SENSOR_ADC, LIGHT_SENSOR_ADC_SAMPLE_CYCLE);
  if(kNoErr != err){
    return -1;
  }
  // get ADC data
  err = MicoAdcTakeSample(LIGHT_SENSOR_ADC, data);
  if(kNoErr == err){
    ret = 0;   // get data succeed
  }
  else{
    ret = -1;  // get data error
  }
  
  return ret;
}
