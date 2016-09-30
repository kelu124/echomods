/**
******************************************************************************
* @file    dc_motor.c
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

#include "MICOPlatform.h"
#include "dc_motor.h"

#define dc_motor_log(M, ...) custom_log("DC_MOTOR", M, ##__VA_ARGS__)
#define dc_motor_log_trace() custom_log_trace("DC_MOTOR")

 
/*------------------------------ USER INTERFACES -----------------------------*/

int dc_motor_init(void)
{
  MicoGpioInitialize( DC_MOTOR, OUTPUT_PUSH_PULL );
  return 0;
}

int dc_motor_set(int value)
{
  if (0 == value) {
    MicoGpioOutputLow( DC_MOTOR );
  } 
  else {
    MicoGpioOutputHigh( DC_MOTOR );
  }
  
  return 0;
}
