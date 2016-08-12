/**
  ******************************************************************************
  * @file    TLVUtils.c 
  * @author  William Xu
  * @version V1.0.0
  * @date    05-May-2014
  * @brief   This file contains function that assist in TLV parsing and creation.
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

#include "TLVUtils.h"

#include "Debug.h"


OSStatus TLVGetNext( const uint8_t *    inSrc, 
                     const uint8_t *    inEnd, 
                     uint8_t *          outID, 
                     const uint8_t **   outData, 
                     size_t *           outLen, 
                     const uint8_t **   outNext )
{
    const uint8_t *     ptr;
    size_t              len;
    const uint8_t *     next;

    //check( inSrc <= inEnd );
    len = (size_t)( inEnd - inSrc );
    if( len < 2 )
        return( kNotFoundErr );

    len  = inSrc[ 1 ];
    ptr  = inSrc + 2;
    next = ptr + len;
    if( ( next < inSrc ) || ( next > inEnd ) )
        return( kUnderrunErr );
    
    *outID   = inSrc[ 0 ];
    *outData = ptr;
    *outLen  = len;
    if( outNext )
        *outNext = next;

    return( kNoErr );
}

