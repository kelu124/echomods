/**
  ******************************************************************************
  * @file    URLUtils.h 
  * @author  William Xu
  * @version V1.0.0
  * @date    05-May-2014
  * @brief   This header contains function prototypes that aid in parsing URLs.
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

#ifndef __URLUtils_h__
#define __URLUtils_h__

#include "Common.h"

//---------------------------------------------------------------------------------------------------------------------------
/*! @function   URLParseComponents
    @abstract   Parses an absolute or relative URL into the general components supported by all URI's.
*/

typedef struct
{
    const char *    schemePtr;
    size_t          schemeLen;
    const char *    userPtr;
    size_t          userLen;
    const char *    passwordPtr;
    size_t          passwordLen;
    const char *    hostPtr;
    size_t          hostLen;
    const char *    pathPtr;
    size_t          pathLen;
    const char *    queryPtr;
    size_t          queryLen;
    const char *    fragmentPtr;
    size_t          fragmentLen;
    
    const char *    segmentPtr; // Ptr to the current resource path segment. Leading slash is removed, if present.
    const char *    segmentEnd; // End of the resource path segments. Trailing slash is removed, if present.
    
} URLComponents;


int URLParseComponents( const char *inSrc, const char *inEnd, URLComponents *outComponents, const char **outSrc );

void PrintURL( URLComponents *inURL );

#endif // __URLUtils_h__

