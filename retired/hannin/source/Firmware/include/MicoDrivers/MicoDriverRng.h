/**
******************************************************************************
* @file    MicoDriverRng.h 
* @author  William Xu
* @version V1.0.0
* @date    16-Sep-2014
* @brief   This file provides all the headers of RNG operation functions.
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

#ifndef __MICODRIVERRNG_H__
#define __MICODRIVERRNG_H__

#pragma once
#include "Common.h"
#include "platform.h"



/** @addtogroup MICO_PLATFORM
* @{
*/

/******************************************************
 *@cond             Macros
 ******************************************************/  

#define PlatformRandomBytes MicoRandomNumberRead   /**< For API compatiable with older version */

/******************************************************
 *@endcond           Enumerations
 ******************************************************/


/******************************************************
 *                 Type Definitions
 ******************************************************/

 /******************************************************
 *                 Function Declarations
 ******************************************************/
 
/** @defgroup MICO_RNG MICO RNG Driver
 * @brief  Random Number Generater(RNG) Functions
 * @{
 */

/** Fill in a memory buffer with random data
 *
 * @param inBuffer        : Point to a valid memory buffer, this function will fill 
                            in this memory with random numbers after excuted
 * @param inByteCount     : Length of the memory buffer (bytes)
 *
 * @return    kNoErr        : on success.
 * @return    kGeneralErr   : if an error occurred with any step
 */
OSStatus MicoRandomNumberRead( void *inBuffer, int inByteCount );

/** @} */
/** @} */

#endif


