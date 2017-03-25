/**
******************************************************************************
* @file    rgb_led_platform.c
* @author  Eshen Wang
* @version V1.0.0
* @date    17-Mar-2015
* @brief  rgb led controller.
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

#include "rgb_led.h"
#include "MicoPlatform.h"
#include "platform.h"
#include "rgb_led_platform_interface.h"

#define rgb_led_log(M, ...)
#define rgb_led_log_trace()

#ifdef USE_RGB_LED_DRIVER_P9813

#define P9813_CIN_Clr()        MicoGpioOutputLow(RGB_LED_P9813_CIN)  
#define P9813_CIN_Set()        MicoGpioOutputHigh(RGB_LED_P9813_CIN)

#define P9813_DIN_Clr()        MicoGpioOutputLow(RGB_LED_P9813_DIN) 
#define P9813_DIN_Set()        MicoGpioOutputHigh(RGB_LED_P9813_DIN)

#else

#define P9813_CIN_Clr()        
#define P9813_CIN_Set()       

#define P9813_DIN_Clr()        
#define P9813_DIN_Set()        

#endif

/* use gpio */
static void P9813_write_frame(uint32_t data)
{ 
  uint8_t i;        
  uint32_t f_data = data;
  rgb_led_log("P9813_write_frame = %X", f_data);
    
  //P9813_CIN_Clr();
  //P9813_DIN_Clr();
  
  for(i=0; i<32; i++){
    P9813_CIN_Clr();
    if(f_data & 0x80000000){
      P9813_DIN_Set();
    }
    else{
      P9813_DIN_Clr();
    }
    P9813_CIN_Set();  // raise edge to set data
    f_data = f_data << 1;
    //rgb_led_log("frame_data<<1 =%x", f_data);
  } 
  
  //P9813_CIN_Clr();
  //P9813_DIN_Clr();
}

static void P9813_write_start_frame(void)
{ 
  uint32_t start_frame = 0x00000000;
  P9813_write_frame(start_frame);     
}

static void P9813_write_data(uint8_t blue, uint8_t green, uint8_t red)
{
  uint8_t check_byte = 0xC0;  // starting flag "11"
  uint32_t send_data = 0;
  
  // calc check data
  check_byte |= (((~blue) >> 2) & 0x30);  // B7, B6
  check_byte |= (((~green) >> 4) & 0x0C);  // G7,G6
  check_byte |= (((~red) >> 6) & 0x03);   // R7,R6
  
  // create send data 32bit
  send_data |= (check_byte << 24) | (blue << 16) | (green << 8) | (red);
  
  //send_data = 0xFC0000FF;
  //rgb_led_log("P9813_write_data: %X", send_data);
  P9813_write_frame(send_data);
}
 
/*-------------------------------------------------- USER INTERFACES ------------------------------------------------*/

void rgb_led_pwm_init(void)
{
  rgb_led_log("Unimplemented");
}

void rgb_led_pwm_open(uint8_t red, uint8_t green, uint8_t blue)
{
  rgb_led_log("Unimplemented");
}

void rgb_led_pwm_deinit(void)
{
  rgb_led_log("Unimplemented");
}


void rgb_led_init(void)
{
#ifdef USE_RGB_LED_DRIVER_P9813
  MicoGpioInitialize( (mico_gpio_t)P9813_CIN, OUTPUT_OPEN_DRAIN_NO_PULL );
  MicoGpioInitialize( (mico_gpio_t)P9813_DIN, OUTPUT_OPEN_DRAIN_NO_PULL );
#elif USE_RGB_LED_DRIVER_PWM
  rgb_led_log("Unimplemented");
#else
#error LED driver function is not defined in platform.h
#endif
  
}

void rgb_led_open(uint8_t red, uint8_t green, uint8_t blue)
{
#ifdef USE_RGB_LED_DRIVER_P9813
  P9813_write_start_frame();
  P9813_write_data(blue, green, red);
  P9813_write_start_frame(); 
#elif USE_RGB_LED_DRIVER_PWM
  rgb_led_log("Unimplemented");
#else
#error LED driver function is not defined in platform.h
#endif
}

void rgb_led_P9813_deinit(void)
{
#ifdef USE_RGB_LED_DRIVER_P9813
  rgb_led_init();
  rgb_led_open(0, 0, 0);
#elif USE_RGB_LED_DRIVER_PWM
  rgb_led_log("Unimplemented");
#else
#error LED driver function is not defined in platform.h
#endif

}
