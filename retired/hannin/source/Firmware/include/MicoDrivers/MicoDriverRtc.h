/**
******************************************************************************
* @file    MicoDriverRtc.h 
* @author  William Xu
* @version V1.0.0
* @date    16-Sep-2014
* @brief   This file provides all the headers of RTC operation functions.
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

#ifndef __MICODRIVERRTC_H__
#define __MICODRIVERRTC_H__

#pragma once
#include "Common.h"
#include "platform.h"
#include "platform_peripheral.h"

/** @addtogroup MICO_PLATFORM
* @{
*/

/******************************************************
 *                   Macros
 ******************************************************/  

/******************************************************
 *                   Enumerations
 ******************************************************/

/******************************************************
 *                 Type Definitions
 ******************************************************/

typedef platform_rtc_time_t           mico_rtc_time_t;

 /******************************************************
 *                    Structures
 ******************************************************/

/******************************************************
 *                     Variables
 ******************************************************/

/******************************************************
                Function Declarations
 ******************************************************/

/** @defgroup MICO_RTC MICO RTC Driver
* @brief  Real-time clock (RTC) Functions
* @{
*/

/**
 * This function will initialize the on board CPU real time clock
 *
 * @note  This function should be called by MICO system when initializing clocks, so
 *        It is not needed to be called by application
 *
 * @return    kNoErr        : on success.
 * @return    kGeneralErr   : if an error occurred with any step
 */
void MicoRtcInitialize(void);

/**
 * This function will return the value of time read from the on board CPU real time clock. Time value must be given in the format of
 * the structure wiced_rtc_time_t
 *
 * @param time        : pointer to a time structure
 *
 * @return    kNoErr        : on success.
 * @return    kGeneralErr   : if an error occurred with any step
 */
OSStatus MicoRtcGetTime(mico_rtc_time_t* time);

/**
 * This function will set MCU RTC time to a new value. Time value must be given in the format of
 * the structure wiced_rtc_time_t
 *
 * @param time        : pointer to a time structure
 *
 * @return    kNoErr        : on success.
 * @return    kGeneralErr   : if an error occurred with any step
 */
OSStatus MicoRtcSetTime(mico_rtc_time_t* time);

/** @} */
/** @} */

#endif


