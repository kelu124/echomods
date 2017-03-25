/**
******************************************************************************
* @file    hsb2rgb_led.c
* @author  Eshen Wang
* @version V1.0.0
* @date    17-Mar-2015
* @brief   converts HSB color values to RGB colors to control RGB LED. 
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

#include "Common.h"
#include "debug.h"
#include "hsb2rgb_led.h"
#include "rgb_led.h"

#define hsb2rgb_led_log(M, ...) custom_log("HSB2RGB_LED", M, ##__VA_ARGS__)
#define hsb2rgb_led_log_trace() custom_log_trace("HSB2RGB_LED")

#define H2R_MAX_RGB_val 255.0

static float constrain(float value, float min, float max){
  if(value >= max)
    return max;
  if(value <=min )
    return min;
  return value;
}

//float Percent(float value){
//  return value = (((float)value / 255.0) * 100.0);
//}

static void H2R_HSBtoRGB(float hue, float sat, float bright, float *color) {
  // constrain all input variables to expected range
  hue = constrain(hue, 0, 360);
  sat = constrain(sat, 0, 100);
  bright = constrain(bright, 0, 100);
  // define maximum value for RGB array elements
  float max_rgb_val = H2R_MAX_RGB_val;
  // convert saturation and brightness value to decimals and init r, g, b variables
  float sat_f = (float)sat / 100.0;
  float bright_f = (float)bright / 100.0;
  float r, g, b;
  // If brightness is 0 then color is black (achromatic)
  // therefore, R, G and B values will all equal to 0
  if (bright <= 0) {
    color[0] = 0;
    color[1] = 0;
    color[2] = 0;
  }
  // If saturation is 0 then color is gray (achromatic)
  // therefore, R, G and B values will all equal the current brightness
  if (sat <= 0) {
    color[0] = bright_f * max_rgb_val;
    color[1] = bright_f * max_rgb_val;
    color[2] = bright_f * max_rgb_val;
  }
  // if saturation and brightness are greater than 0 then calculate
  // R, G and B values based on the current hue and brightness
  else {
    if (hue >= 0 && hue < 120) {
      float hue_primary = 1.0 - ((float)hue / 120.0);
      float hue_secondary = (float)hue / 120.0;
      float sat_primary = (1.0 - hue_primary) * (1.0 - sat_f);
      float sat_secondary = (1.0 - hue_secondary) * (1.0 - sat_f);
      float sat_tertiary = 1.0 - sat_f;
      r = (bright_f * max_rgb_val) * (hue_primary + sat_primary);
      g = (bright_f * max_rgb_val) * (hue_secondary + sat_secondary);
      b = (bright_f * max_rgb_val) * sat_tertiary;
    }
    else if (hue >= 120 && hue < 240) {
      float hue_primary = 1.0 - (((float)hue-120.0) / 120.0);
      float hue_secondary = ((float)hue-120.0) / 120.0;
      float sat_primary = (1.0 - hue_primary) * (1.0 - sat_f);
      float sat_secondary = (1.0 - hue_secondary) * (1.0 - sat_f);
      float sat_tertiary = 1.0 - sat_f;
      r = (bright_f * max_rgb_val) * sat_tertiary;
      g = (bright_f * max_rgb_val) * (hue_primary + sat_primary);
      b = (bright_f * max_rgb_val) * (hue_secondary + sat_secondary);
    }
    else if (hue >= 240 && hue <= 360) {
      float hue_primary = 1.0 - (((float)hue-240.0) / 120.0);
      float hue_secondary = ((float)hue-240.0) / 120.0;
      float sat_primary = (1.0 - hue_primary) * (1.0 - sat_f);
      float sat_secondary = (1.0 - hue_secondary) * (1.0 - sat_f);
      float sat_tertiary = 1.0 - sat_f;
      r = (bright_f * max_rgb_val) * (hue_secondary + sat_secondary);
      g = (bright_f * max_rgb_val) * sat_tertiary;
      b = (bright_f * max_rgb_val) * (hue_primary + sat_primary);
    }
    color[0] = r;
    color[1] = g;
    color[2] = b;
  }
  //  color[0] = Percent(color[0]);
  //  color[1] = Percent(color[1]);
  //  color[2] = Percent(color[2]);
}

/*----------------------------------------------------- INTERNAL FUNCTION  ---------------------------------------*/

// call RGB LED driver to control LED
static void OpenLED_RGB(float *color)
{
  uint8_t blue = (uint8_t)(color[2]);
  uint8_t green = (uint8_t)(color[1]);
  uint8_t red = (uint8_t)(color[0]);
  
  //hsb2rgb_led_log("OpenLED_RGB: red=%d, green=%d, blue=%d.", red, green, blue);
  
  rgb_led_init();
  rgb_led_open(red, green, blue);
}

static void CloseLED_RGB()
{
  rgb_led_init();
  rgb_led_close();
}


/*----------------------------------------------------- USER INTERFACES ---------------------------------------*/

void hsb2rgb_led_init(void)
{
  rgb_led_init();
}

void hsb2rgb_led_open(float hues, float saturation, float brightness)
{
  float color[3] = {0};
  H2R_HSBtoRGB(hues, saturation, brightness, color);
  OpenLED_RGB(color);
}

void hsb2rgb_led_close(void)
{
  CloseLED_RGB();
}
