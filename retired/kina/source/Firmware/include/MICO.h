/**
******************************************************************************
* @file    MICO.h 
* @author  William Xu
* @version V1.0.0
* @date    16-Sep-2014
* @brief   This file provides other MICO API header file and some basic APIs.
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


/** \mainpage MICO 

  This documentation describes the MICO APIs.
  It consists of:
     - MICO Hardware Abstract Layer   
     - MICO RTOS and Timer APIs       
     - MICO Wi-Fi Connectivith APIs   
     - MICO BSD Socket APIs           
 */

#ifndef __MICO_H_
#define __MICO_H_

#include "Debug.h"
#include "Common.h" 
#include "MicoRTOS.h"
#include "MicoWlan.h"
#include "MicoSocket.h"
#include "MicoAlgorithm.h"
#include "MicoPlatform.h"

#define MicoGetRfVer                wlan_driver_version
#define MicoGetVer                  system_lib_version
#define MicoInit                    mxchipInit
#define MicoGetMemoryInfo           mico_memory_info

/** \defgroup MICO_Core_APIs MICO Core APIs
  This file defines all structures and symbols for MICO core:
   - MICO Core exported symbols
   - MICO Core exported functions
 */

/** @addtogroup MICO_Core_APIs
  * @{
  */

/** \defgroup MICO_Init_Info Initialization and Tools
  @{
 */

typedef struct  {
  int num_of_chunks;  /**< number of free chunks*/
  int total_memory;  /**< maximum total allocated space*/
  int allocted_memory; /**< total allocated space*/
  int free_memory; /**< total free space*/
} micoMemInfo_t;

/**
  * @brief  Get RF driver's version.
  *
  * @note   Create a memery buffer to store the version characters.
  *         THe input buffer length should be 40 bytes at least.
  * @note   This must be executed after micoInit().
  * @param  inVersion: Buffer address to store the RF driver. 
  * @param  inLength: Buffer size. 
  *
  * @return int
  */
int MicoGetRfVer( char* outVersion, uint8_t inLength );

/**
  * @brief  Get MICO's version.
  *
  * @param  None 
  *
  * @return Point to the MICO's version string.
  */
char* MicoGetVer( void );

/**
  * @brief  Initialize the TCPIP stack thread, RF driver thread, and other
            supporting threads needed for wlan connection. Do some necessary
            initialization
  *
  * @param  None
  *
  * @return None
  */
void MicoInit( void );

/**
  * @brief  Get memory usage information
  *
  * @param  None 
  *
  * @return Point to structure of memory usage information in heap
  */
micoMemInfo_t* MicoGetMemoryInfo( void );

#endif /* __MICO_H_ */

/**
  * @}
  */

/**
  * @}
  */

