/**
  ******************************************************************************
  * @file    TimeUtils.c 
  * @author  William Xu
  * @version V1.0.0
  * @date    05-May-2014
  * @brief   This file contains function which aid in time calculations.
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


#include "TimeUtils.h"
#include "Debug.h"
#include "MICO.h"
#include <errno.h>

uint32_t TimeDifference(uint32_t inStart, uint32_t inEnd)
{
    return inStart-inEnd;
}

long long ElapsedTimeInMilliseconds(uint32_t inDiff)
{
    return (long long)inDiff;
}

long long ElapsedTimeInMicroseconds(uint32_t inDiff)
{
    return (long long)(inDiff*MILLISECONDS) ;
}

long long ElapsedTimeInNanoseconds(uint32_t inDiff)
{
    return (long long)(inDiff*MICROSECONDS) ;
}

uint64_t UpTicks( void )
{
    return mico_get_time();;
}

uint64_t UpTicksPerSecond( void )
{
    return MILLISECONDS;
}

void SleepForUpTicks( uint64_t inTicks )
{
    uint64_t  ticks, deadline;
    
    ticks = UpTicks();
    deadline = ticks + inTicks;
    for( ; ticks < deadline; ticks = UpTicks() )
    {
        ticks = deadline - ticks;
        msleep(ticks);
    }
}

