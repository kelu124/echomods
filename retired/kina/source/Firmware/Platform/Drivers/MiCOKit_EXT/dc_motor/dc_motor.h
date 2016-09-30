/**
******************************************************************************
* @file    dc_motor.h 
* @author  Eshen Wang
* @version V1.0.0
* @date    1-May-2015
* @brief   dc motor operation. 
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

#ifndef __DC_MOTOR_H_
#define __DC_MOTOR_H_


#include "MICOPlatform.h"

//--------------------------------  pin defines --------------------------------
//      DC MOTOR PIN <------->  EXT-BOARD PIN
#ifdef USE_MiCOKit_EXT
  #include "micokit_ext_def.h"
  #define DC_MOTOR            MICO_EXT_DC_MOTOR  // PB4
#else
  #define DC_MOTOR            MICO_GPIO_NONE
#endif

//------------------------------ user interfaces -------------------------------
int dc_motor_init(void);
int dc_motor_set(int value);    // 0: off, others: on


#endif  // __DC_MOTOR_H_
