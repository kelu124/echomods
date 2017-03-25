/**
******************************************************************************
* @file    infrared_reflective.h 
* @author  Eshen Wang
* @version V1.0.0
* @date    1-May-2015
* @brief   infrared reflective sensor operation. 
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
#include "infrared_reflective.h"

#define infrared_reflective_log(M, ...) custom_log("INFRARED_REFLECTIVE", M, ##__VA_ARGS__)
#define infrared_reflective_log_trace() custom_log_trace("INFRARED_REFLECTIVE")

 
/*------------------------------ USER INTERFACES -----------------------------*/

int infrared_reflective_init(void)
{
  OSStatus err = kUnknownErr;
  
  err = MicoAdcInitialize(INFARAED_REFLECTIVE_ADC, INFARAED_REFLECTIVE_ADC_SAMPLE_CYCLE);
  if(kNoErr != err){
    return -1;
  }
  
  return 0;
}

int infrared_reflective_read(uint16_t *data)
{
  int ret = 0;
  OSStatus err = kUnknownErr;
  
  // init ADC
  err = MicoAdcInitialize(INFARAED_REFLECTIVE_ADC, INFARAED_REFLECTIVE_ADC_SAMPLE_CYCLE);
  if(kNoErr != err){
    return -1;
  }
  // get ADC data
  err = MicoAdcTakeSample(INFARAED_REFLECTIVE_ADC, data);
  if(kNoErr == err){
    ret = 0;   // get data succeed
  }
  else{
    ret = -1;  // get data error
  }
  
  return ret;
}
