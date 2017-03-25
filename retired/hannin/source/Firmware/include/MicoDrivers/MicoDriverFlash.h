/**
******************************************************************************
* @file    MicoDriverFlash.h 
* @author  William Xu
* @version V1.0.0
* @date    16-Sep-2014
* @brief   This file provides all the headers of flash operation functions.
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

#ifndef __MICODRIVERFLASH_H__
#define __MICODRIVERFLASH_H__

#pragma once
#include "Common.h"
#include "platform.h"

/** @addtogroup MICO_PLATFORM
* @{
*/

/******************************************************
 *                   Macros
 ******************************************************/  

/******************************************************
 *                   Enumerations
 ******************************************************/

/******************************************************
 *                 Type Definitions
 ******************************************************/

/******************************************************
 *                 Global Variables
 ******************************************************/

extern const char*  flash_name[];  /**< A name string of a Flash drive */

 /******************************************************
 *                 Function Declarations
 ******************************************************/

/** @defgroup MICO_FLASH MICO Flash Driver
* @brief  Flash operation Functions
* @{
*/

/** Initialises a Flash driver
 *
 * Prepares an Flash for read and write
 *
 * @param  inFlash     : the interface which should be initialised
 *
 * @return    kNoErr        : On success.
 * @return    kGeneralErr   : If an error occurred with any step
 */
OSStatus MicoFlashInitialize( mico_flash_t inFlash );

/** Erase an area on a Flash
 *
 * @note Erase on an address will erase all data on a sector that the 
 *       address is belonged to, this function does not save data that
 *       beyond the address area but in the affected sector, the data
 *       will be lost.
 *
 * @param  inFlash     		: The target flash which should be erased
 * @param  inStartAddress 	: Start address of the erased flash area
 * @param  inEndAddress   	: End address of the erased flash area
 *
 * @return    kNoErr        : On success.
 * @return    kGeneralErr   : If an error occurred with any step
 */
OSStatus MicoFlashErase(mico_flash_t inFlash, uint32_t inStartAddress, uint32_t inEndAddress);

/** Write data to an area on a Flash
 *
 * @param  inFlash     	  : The target flash which should be written
 * @param  inFlashAddress : Poing to the start address that the data is written to, and
 *                          point to the last unwritten address after this function is 
 *                          returned, so you can call this function serval times without
 *                          update this start address.
 * @param  inBuffer       : point to the data buffer that will be written to flash
 * @param  inBufferLength : The length of the buffer
 *
 * @return    kNoErr        : On success.
 * @return    kGeneralErr   : If an error occurred with any step
 */
OSStatus MicoFlashWrite(mico_flash_t inFlash, volatile uint32_t* inFlashAddress, uint8_t* inBuffer ,uint32_t inBufferLength);

/** Read data from an area on a Flash to data buffer in RAM
 *
 * @param  inFlash     	  : The target flash which should be  read
 * @param  inFlashAddress : Poing to the start address that the data is read, and
 *                          point to the last unread address after this function is 
 *                          returned, so you can call this function serval times without
 *                          update this start address.
 * @param  outBuffer      : point to the data buffer that stores the data read from flash
 * @param  inBufferLength : The length of the buffer
 *
 * @return    kNoErr        : On success.
 * @return    kGeneralErr   : If an error occurred with any step
 */
OSStatus MicoFlashRead(mico_flash_t inFlash, volatile uint32_t* inFlashAddress, uint8_t* outBuffer ,uint32_t inBufferLength);

/** Deinitialises a Flash driver
 *
 * Prepares an Flash for read and write
 *
 * @param  inFlash     : The target flash which should be deinitialised
 *
 * @return    kNoErr        : On success.
 * @return    kGeneralErr   : If an error occurred with any step
 */
OSStatus MicoFlashFinalize( mico_flash_t inFlash );



/** @} */
/** @} */

#endif


