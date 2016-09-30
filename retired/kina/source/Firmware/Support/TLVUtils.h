/**
  ******************************************************************************
  * @file    TLVUtils.h 
  * @author  William Xu
  * @version V1.0.0
  * @date    05-May-2014
  * @brief   This header contains function prototypes that assist in TLV parsing
     and creation.
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



#ifndef __TLVUtils_h__
#define __TLVUtils_h__
#include "Common.h"


OSStatus TLVGetNext( 
        const uint8_t *     inSrc, 
        const uint8_t *     inEnd, 
        uint8_t *           outID, 
        const uint8_t **    outData, 
        size_t *            outLen, 
        const uint8_t **    outNext );

#endif // __TLVUtils_h__

