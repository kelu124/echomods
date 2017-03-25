/**
******************************************************************************
* @file    MicoDriverWdg.h 
* @author  William Xu
* @version V1.0.0
* @date    16-Sep-2014
* @brief   This file provides all the headers of WDG operation functions.
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


#ifndef __MICODRIVERWDG_H__
#define __MICODRIVERWDG_H__

#pragma once
#include "Common.h"
#include "platform.h"

/** @addtogroup MICO_PLATFORM
* @{
*/

/******************************************************
 *                   Macros
 ******************************************************/  

#define PlatformWDGInitialize   MicoWdgInitialize /**< For API compatiable with older version */
#define PlatformWDGReload       MicoWdgReload     /**< For API compatiable with older version */
#define PlatformWDGFinalize     MicoWdgFinalize   /**< For API compatiable with older version */

/******************************************************
 *@cond              Enumerations
 ******************************************************/

/******************************************************
 *@endcond         Type Definitions
 ******************************************************/

 /******************************************************
 *                    Structures
 ******************************************************/


/******************************************************
 *                     Variables
 ******************************************************/

/******************************************************
 * @endcond           Function Declarations
 ******************************************************/

/** @defgroup MICO_WDG MICO WDG Driver
* @brief  Hardware watch dog Functions (WDG) Functions
* @note   These Functions are used by MICO's system monitor service, If any defined system monitor 
*          cannot be reloaded for some reason, system monitor service use this hardware watch dog 
*          to perform a system reset. So the watch dog reload time should be greater than system 
*          monitor's refresh time.
* @{
*/

/**
 * This function will initialize the on board CPU hardware watch dog
 *
 * @param timeout        : Watchdag timeout, application should call MicoWdgReload befor timeout.
 *
 * @return    kNoErr        : on success.
 * @return    kGeneralErr   : if an error occurred with any step
 */
OSStatus MicoWdgInitialize( uint32_t timeout );

/**
 * Reload watchdog counter.
 *
 * @param     none
 * @return    none
 */
void MicoWdgReload( void );

/**
 * This function performs any platform-specific cleanup needed for hardware watch dog.
 *
 * @param     none
 *
 * @return    kNoErr        : on success.
 * @return    kGeneralErr   : if an error occurred with any step
 */
OSStatus MicoWdgFinalize( void );

/** @} */
/** @} */

#endif


