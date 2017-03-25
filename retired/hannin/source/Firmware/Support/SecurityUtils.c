/**
******************************************************************************
* @file    SecurityUtils.C 
* @author  William Xu
* @version V1.0.0
* @date    05-May-2014
* @brief   This header contains function that aid in security on the platform.
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

#include "SecurityUtils.h"

//===========================================================================================================================
//  memcmp_constant_time
//
//  Compares memory so that the time it takes does not depend on the data being compared.
//  This is needed to avoid certain timing attacks in cryptographic software.
//===========================================================================================================================

int memcmp_constant_time( const void *inA, const void *inB, size_t inLen )
{
    const uint8_t * const       a = (const uint8_t *) inA; 
    const uint8_t * const       b = (const uint8_t *) inB; 
    int                         result = 0; 
    size_t                      i;   
    
    for( i = 0; i < inLen; ++i )
    {    
        result |= ( a[ i ] ^ b[ i ] ); 
    }    
    return( result );
}


