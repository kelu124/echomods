/**
******************************************************************************
* @file    rgb_led.h 
* @author  Eshen Wang
* @version V1.0.0
* @date    17-Mar-2015
* @brief    rgb led controller. 
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

#ifndef __RGB_LED_H_
#define __RGB_LED_H_

#include "MICOPlatform.h"

//-------------------- P9813 pin defines ---------------------------
#define P9813_CIN              MICO_GPIO_10    // CLK
#define P9813_DIN              MICO_GPIO_11    // DIN

#define RGB_LED_P9813_CIN          P9813_CIN    // CLK
#define RGB_LED_P9813_DIN          P9813_DIN    // DIN

//#define P9813_CIN_Clr()        MicoGpioOutputLow(P9813_CIN)  
//#define P9813_CIN_Set()        MicoGpioOutputHigh(P9813_CIN)
//
//#define P9813_DIN_Clr()        MicoGpioOutputLow(P9813_DIN) 
//#define P9813_DIN_Set()        MicoGpioOutputHigh(P9813_DIN)

//-------------------- user interfaces ---------------------------
void rgb_led_init(void);
void rgb_led_open(uint8_t red, uint8_t green, uint8_t blue);
void rgb_led_deinit(void);


#endif  // __RGB_LED_H_
