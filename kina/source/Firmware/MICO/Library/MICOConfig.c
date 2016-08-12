/**
******************************************************************************
* @file    MicoConfig.C 
* @author  William Xu
* @version V1.0.0
* @date    05-May-2014
* @brief   This file provide the MICO running constants.
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

#include "Common.h"
#include "MicoDefaults.h"
#include "platform_config.h"

#ifdef MICO_DEFAULT_APPLICATION_STACK_SIZE
uint32_t  app_stack_size = MICO_DEFAULT_APPLICATION_STACK_SIZE; 
#else
uint32_t  app_stack_size = 1500;
#endif


#ifdef  MICO_DEFAULT_TICK_RATE_HZ
const uint32_t  mico_tick_rate_hz = MICO_DEFAULT_TICK_RATE_HZ;
#else 
const uint32_t  mico_tick_rate_hz = 1000; // Drfault OS tick is 1000Hz
#endif

const uint32_t  mico_timer_queue_len = 5;


const uint32_t mico_nmode_enable = true;

#ifdef DEBUG
//int mico_debug_enabled = 1;
int mico_debug_enabled = 0;//doit
#endif

#ifdef SDIO_1_BIT
int sdio_1_bit_mode = 1;
#else
int sdio_1_bit_mode = 0;
#endif

