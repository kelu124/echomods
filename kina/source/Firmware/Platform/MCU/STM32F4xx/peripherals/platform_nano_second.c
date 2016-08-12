/**
******************************************************************************
* @file    platform_nano_second.c 
* @author  William Xu
* @version V1.0.0
* @date    05-May-2014
* @brief   This file provide time delay function using nano second.
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

#include "platform_peripheral.h"

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
 *                      Macros
 ******************************************************/
#define CYCLE_COUNTING_INIT() \
    do \
    { \
        /* enable DWT hardware and cycle counting */ \
        CoreDebug->DEMCR = CoreDebug->DEMCR | CoreDebug_DEMCR_TRCENA_Msk; \
        /* reset a counter */ \
        DWT->CYCCNT = 0;  \
        /* enable the counter */ \
        DWT->CTRL = (DWT->CTRL | DWT_CTRL_CYCCNTENA_Msk) ; \
    } \
    while(0)

#define absolute_value(a) ( (a) < 0 ) ? -(a) : (a)
          
/******************************************************
*               Variables Definitions
******************************************************/

uint32_t nsclock_nsec =0;
uint32_t nsclock_sec =0;
uint32_t prev_cycles = 0;

/******************************************************
*               Function Declarations
******************************************************/

/******************************************************
*               Function Definitions
******************************************************/

uint64_t platform_get_nanosecond_clock_value(void)
{
    uint64_t nanos;
    uint32_t cycles;
    uint32_t diff;
    cycles = DWT->CYCCNT;

    /* add values to the ns part of the time which can be divided by 3 */
    /* every time such value is added we will increment our clock by 25ns = 1/40 000000( cycle counter is running on the CPU frequency ),  */
    /* values will be 3, 6, 9, etc */
    diff = absolute_value((int)(cycles - prev_cycles));
    nsclock_nsec += ( diff / 3 ) * 25;

    /* when ns counter rolls over, add one second */
    if( nsclock_nsec >= 1000000000 )
    {
        nsclock_sec++;
        nsclock_nsec = nsclock_nsec - 1000000000;
    }
    prev_cycles = cycles - (diff % 3);

    nanos = nsclock_sec;
    nanos *= 1000000000;
    nanos += nsclock_nsec;
    return nanos;
}


void platform_deinit_nanosecond_clock(void)
{
    nsclock_nsec = 0;
    nsclock_sec = 0;
}

void platform_reset_nanosecond_clock(void)
{
    nsclock_nsec = 0;
    nsclock_sec = 0;
}

void platform_init_nanosecond_clock(void)
{
    CYCLE_COUNTING_INIT();
    nsclock_nsec = 0;
    nsclock_sec = 0;
}


void platform_nanosecond_delay( uint64_t delayns )
{
  uint64_t currentns = 0;
  
  platform_init_nanosecond_clock();
  
  do
  {
    currentns = platform_get_nanosecond_clock_value();
  }
  while(currentns < delayns);
  
}

