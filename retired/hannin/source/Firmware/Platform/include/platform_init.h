/**
******************************************************************************
* @file    Platform_init.h 
* @author  William Xu
* @version V1.0.0
* @date    05-May-2014
* @brief   This file provides function headers need by MICO internal usage.
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
#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Main
 *
 * @param[in] : void
 * @return    : int
 *
 * @usage
 * \li Defined by RTOS or application and called by CRT0
 */
int main( void );

/**
 * Initialise system clock(s)
 * This function includes initialisation of PLL and switching to fast clock
 *
 * @param[in] : void
 * @return    : void
 *
 * @usage
 * \li Defined internally in platforms/MCU/<MCU>/platform_init.c and called by CRT0
 * \li Weakly defined in platforms/MCU/<MCU>/platform_init.c. Users may override it as desired
 */
extern void platform_init_system_clocks( void );
extern void init_clocks( void );

/**
 * Initialise memory subsystem
 * This function initialises memory subsystem such as external RAM
 *
 * @param[in] : void
 * @return    : void
 *
 * @usage
 * \li Defined internally in platforms/MCU/<MCU>/platform_init.c and called by CRT0
 * \li Weakly defined in platforms/MCU/<MCU>/platform_init.c. Users may override it as desired
 */
extern void platform_init_memory( void );

/**
 * Initialise default MCU infrastructure
 * This function initialises default MCU infrastructure such as watchdog
 *
 * @param[in] : void
 * @return    : void
 *
 * @usage
 * \li Defined and used internally in platforms/MCU/<MCU>/platform_init.c
 */
extern void platform_init_mcu_infrastructure( void );

/**
 * Initialise connectivity module(s)
 * This function initialises and puts connectivity modules (Wi-Fi, Bluetooth, etc) into their reset state
 *
 * @param[in] : void
 * @return    : void
 *
 * @usage
 * \li Defined and used internally in platforms/MCU/<MCU>/platform_init.c
 */
extern void platform_init_connectivity_module( void );

/**
 * Initialise external devices
 * This function initialises and puts external peripheral devices on the board such as LEDs, buttons, sensors, etc into their reset state
 *
 * @param[in] : void
 * @return    : void
 *
 * @usage     :
 * \li MUST be defined in platforms/<Platform>/platform.c
 * \li Called by @ref platform_init_mcu_infrastructure()
 */
extern void platform_init_external_devices( void );

/**
 * Initialise priorities of interrupts used by the platform peripherals
 *
 * @param[in] : void
 * @return    : void
 *
 * @usage
 * \li MUST be defined in platforms/<Platform>/platform.c
 * \li Called by @ref platform_init_mcu_infrastructure()
 */
extern void platform_init_peripheral_irq_priorities( void );

/**
 * Initialise priorities of interrupts used by the RTOS
 *
 * @param[in] : void
 * @return    : void

 * @usage
 * \li MUST be defined by the RTOS
 * \li Called by @ref platform_init_mcu_infrastructure()
 */
extern void platform_init_rtos_irq_priorities( void );

#ifdef __cplusplus
} /*extern "C" */
#endif
