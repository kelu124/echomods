/**
******************************************************************************
* @file    wlan_platform.c 
* @author  William Xu
* @version V1.0.0
* @date    05-May-2014
* @brief   This file provide functions called by MICO to wlan RF module
******************************************************************************
*
*  The MIT License
*  Copyright (c) 2014 MXCHIP Inc.
*
*  Permission is hereby granted, free of charge, to any person obtaining a copy 
*  of this software and associated documentation files (the "Software"), to deal
*  in the Software without restriction, including without limitation the rights 
*  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*  copies of the Software, and to permit persons to whom the Software is furnished
*  to do so, subject to the following conditions:
*
*  The above copyright notice and this permission notice shall be included in
*  all copies or substantial portions of the Software.
*
*  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
*  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
*  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
*  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
*  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR 
*  IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
******************************************************************************
*/ 

#include "platform_config.h"
#include "platform_peripheral.h"
#include "PlatformLogging.h"

/* Used to give a 32k clock to EMW1062 wifi rf module */
OSStatus host_platform_init_wlan_powersave_clock( void )
{
#if defined ( MICO_USE_WIFI_32K_CLOCK_MCO ) && defined ( MICO_USE_WIFI_32K_PIN )
    platform_gpio_set_alternate_function( wifi_control_pins[WIFI_PIN_32K_CLK].port, wifi_control_pins[WIFI_PIN_32K_CLK].pin_number, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_AF_MCO );

    /* enable LSE output on MCO1 */
    RCC_MCO1Config( RCC_MCO1Source_LSE, RCC_MCO1Div_1 );
    return kNoErr;
#elif defined ( MICO_USE_WIFI_32K_PIN )
    return host_platform_deinit_wlan_powersave_clock( );
#else
    return kNoErr;
#endif
}



