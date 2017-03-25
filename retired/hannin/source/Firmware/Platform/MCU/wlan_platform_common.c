/**
******************************************************************************
* @file    wlan_platform_common.c 
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

#include <stdint.h>
#include "platform.h"
#include "platform_config.h"
#include "wlan_platform_common.h"

/******************************************************
 *                      Macros
 ******************************************************/
 
/******************************************************
 *                    Constants
 ******************************************************/

/******************************************************
 *                   Enumerations
 ******************************************************/

/******************************************************
 *                 Type Definitions
 ******************************************************/

/******************************************************
 *                    Structures
 ******************************************************/

/******************************************************
 *               Function Declarations
 ******************************************************/
OSStatus host_platform_deinit_wlan_powersave_clock( void );

/******************************************************
 *               Variables Definitions
 ******************************************************/

/******************************************************
 *               Function Definitions
 ******************************************************/

void host_platform_reset_wifi( bool reset_asserted )
{
#if defined (MICO_USE_WIFI_RESET_PIN )
    ( reset_asserted == true ) ? platform_gpio_output_low( &wifi_control_pins[ WIFI_PIN_RESET ] ) : platform_gpio_output_high( &wifi_control_pins[ WIFI_PIN_RESET ] );
#else
    UNUSED_PARAMETER( reset_asserted );
#endif
}

void host_platform_power_wifi( bool power_enabled )
{
#if   defined ( MICO_USE_WIFI_POWER_PIN ) && defined ( MICO_USE_WIFI_POWER_PIN_ACTIVE_HIGH )
    ( power_enabled == true ) ? platform_gpio_output_high( &wifi_control_pins[WIFI_PIN_POWER] ) : platform_gpio_output_low ( &wifi_control_pins[WIFI_PIN_POWER] );
#elif defined ( MICO_USE_WIFI_POWER_PIN )
    ( power_enabled == true ) ? platform_gpio_output_low ( &wifi_control_pins[WIFI_PIN_POWER] ) : platform_gpio_output_high( &wifi_control_pins[WIFI_PIN_POWER] );
#else
    UNUSED_PARAMETER( power_enabled );
#endif
}

OSStatus host_platform_init( void )
{
    host_platform_deinit_wlan_powersave_clock( );

#if defined ( MICO_USE_WIFI_RESET_PIN )
    platform_gpio_init( &wifi_control_pins[WIFI_PIN_RESET], OUTPUT_PUSH_PULL );
    host_platform_reset_wifi( true );  /* Start wifi chip in reset */
#endif
    
#if defined ( MICO_USE_WIFI_POWER_PIN )
    platform_gpio_init( &wifi_control_pins[WIFI_PIN_POWER], OUTPUT_PUSH_PULL );
    host_platform_power_wifi( false ); /* Start wifi chip with regulators off */
#endif

    return kNoErr;
}

OSStatus host_platform_deinit( void )
{
#if defined ( MICO_USE_WIFI_RESET_PIN )
    platform_gpio_init( &wifi_control_pins[WIFI_PIN_RESET], OUTPUT_PUSH_PULL );
    host_platform_reset_wifi( true );  /* Start wifi chip in reset */
#endif
    
#if defined ( MICO_USE_WIFI_POWER_PIN )
    platform_gpio_init( &wifi_control_pins[WIFI_PIN_POWER], OUTPUT_PUSH_PULL );
    host_platform_power_wifi( false ); /* Start wifi chip with regulators off */
#endif

    host_platform_deinit_wlan_powersave_clock( );

    return kNoErr;
}

bool host_platform_is_in_interrupt_context( void )
{
    /* From the ARM Cortex-M3 Techinical Reference Manual
     * 0xE000ED04   ICSR    RW [a]  Privileged  0x00000000  Interrupt Control and State Register */
    uint32_t active_interrupt_vector = (uint32_t)( SCB ->ICSR & 0x3fU );

    if ( active_interrupt_vector != 0 )
    {
        return true;
    }
    else
    {
        return false;
    }
}

OSStatus host_platform_deinit_wlan_powersave_clock( void )
{
#ifndef MICO_USE_WIFI_32K_PIN
    return kNoErr;
#else
    /* Tie the pin to ground */
    platform_gpio_init( &wifi_control_pins[WIFI_PIN_32K_CLK], OUTPUT_PUSH_PULL );
    platform_gpio_output_low( &wifi_control_pins[WIFI_PIN_32K_CLK] );
    return kNoErr;
#endif
}
