/**
******************************************************************************
* @file    hsb2rgb_led.h 
* @author  Eshen Wang
* @version V1.0.0
* @date    17-Mar-2015
* @brief   converts HSB color values to RGB colors to control RGB LED. 
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

#ifndef __HSB2RGB_LED_H_
#define __HSB2RGB_LED_H_


void hsb2rgb_led_init(void);
void hsb2rgb_led_open(float hues, float saturation, float brightness);
void hsb2rgb_led_close(void);


#endif   // __HSB2RGB_LED_H_