/**
******************************************************************************
* @file    keys.h 
* @author  Eshen Wang
* @version V1.0.0
* @date    1-May-2015
* @brief   user key operation. 
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

#ifndef __KEYS_H_
#define __KEYS_H_


#include "MICOPlatform.h"

//--------------------------------  pin defines --------------------------------

//       USER KEY PIN  <------------->   EXT-BOARD PIN
#ifdef USE_MiCOKit_EXT
  #include "micokit_ext_def.h"
  #define USER_KEY1                       MICO_EXT_KEY1
  #define USER_KEY2                       MICO_EXT_KEY2
#else
  #define USER_KEY1                       MICO_GPIO_NONE
  #define USER_KEY2                       MICO_GPIO_NONE
#endif
   
#define user_key1_long_press_timeout    5000  /**< user key1 button long pressed for 5 seconds. */
#define user_key2_long_press_timeout    5000  /**< user key2 button long pressed for 5 seconds. */

//------------------------------ user interfaces -------------------------------

void user_key1_init(void);
void user_key2_init(void);


#endif  // __KEYS_H_
