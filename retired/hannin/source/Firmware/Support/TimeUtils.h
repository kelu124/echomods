/**
  ******************************************************************************
  * @file    TimeUtils.h 
  * @author  William Xu
  * @version V1.0.0
  * @date    05-May-2014
  * @brief   This header contains function prototypes which aid in time calculations.
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


#ifndef __TimeUtils_h__
#define __TimeUtils_h__

#include "Common.h"

// ==== SECOND CONVERSION CONSTANTS ====
#define NANOSECONDS  1000000000ULL
#define MICROSECONDS 1000000UL
#define MILLISECONDS 1000

#define kNanosecondsPerSecond   1000000000


// ==== TIME DIFF UTILS ====
uint32_t TimeDifference(uint32_t inStart, uint32_t inEnd);


// ==== ELAPSED TIME UTILS ====
long long ElapsedTimeInMilliseconds(uint32_t inDiff);

long long ElapsedTimeInMicroseconds(uint32_t inDiff);

long long ElapsedTimeInNanoseconds(uint32_t inDiff);

// ==== TICK UTILS ====
uint64_t UpTicks( void );

uint64_t UpTicksPerSecond( void );

void SleepForUpTicks( uint64_t inTicks );

#endif


