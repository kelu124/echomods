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

#ifndef __INFRARED_REFLECTIVE_H_
#define __INFRARED_REFLECTIVE_H_


#include "MICOPlatform.h"

//--------------------------------  pin defines --------------------------------
#ifdef USE_MiCOKit_EXT
  #include "micokit_ext_def.h"
  #define INFARAED_REFLECTIVE_ADC                 MICO_EXT_ADC_INFRARED  // ADC1_1 (PA1)
#else
  #define INFARAED_REFLECTIVE_ADC                 MICO_ADC_NONE  // ADC1_1 (PA1)
#endif

#define INFARAED_REFLECTIVE_ADC_SAMPLE_CYCLE    3

//------------------------------ user interfaces -------------------------------
int infrared_reflective_init(void);
int infrared_reflective_read(uint16_t *data);


#endif  // __INFRARED_REFLECTIVE_H_
