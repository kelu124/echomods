/**
******************************************************************************
* @file    MICOSystemMonitor.h 
* @author  William Xu
* @version V1.0.0
* @date    05-May-2014
* @brief   System monitor function, create a system monitor thread, and user 
*          can add own monitor events.
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

#ifndef __MICOSYSTEMMONITOR_H__
#define __MICOSYSTEMMONITOR_H__

#include "Common.h"
#include "MICODefine.h"

/** Structure to hold information about a system monitor item */
typedef struct
{
    uint32_t last_update;              /**< Time of the last system monitor update */
    uint32_t longest_permitted_delay;  /**< Longest permitted delay between checkins with the system monitor */
} mico_system_monitor_t;


OSStatus MICOStartSystemMonitor (mico_Context_t * const inContext);

OSStatus MICOUpdateSystemMonitor( mico_system_monitor_t* system_monitor, uint32_t permitted_delay );

OSStatus MICORegisterSystemMonitor( mico_system_monitor_t* system_monitor, uint32_t initial_permitted_delay );


#endif //__MICO_SYSTEM_MONITOR_H__



