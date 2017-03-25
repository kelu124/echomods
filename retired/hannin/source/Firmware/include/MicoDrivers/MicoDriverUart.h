/**
******************************************************************************
* @file    MicoDriverUart.h 
* @author  William Xu
* @version V1.0.0
* @date    16-Sep-2014
* @brief   This file provides all the headers of UART operation functions.
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


#ifndef __MICODRIVERUART_H__
#define __MICODRIVERUART_H__

#pragma once
#include "Common.h"
#include "RingBufferUtils.h"
#include "platform.h"
#include "platform_peripheral.h"

/** @addtogroup MICO_PLATFORM
* @{
*/

/******************************************************
 *                   Enumerations
 ******************************************************/

// typedef enum
// {
//     DATA_WIDTH_5BIT,
//     DATA_WIDTH_6BIT,
//     DATA_WIDTH_7BIT,
//     DATA_WIDTH_8BIT,
//     DATA_WIDTH_9BIT
// } mico_uart_data_width_t;

// typedef enum
// {
//     STOP_BITS_1,
//     STOP_BITS_2,
// } mico_uart_stop_bits_t;

// typedef enum
// {
//     FLOW_CONTROL_DISABLED,
//     FLOW_CONTROL_CTS,
//     FLOW_CONTROL_RTS,
//     FLOW_CONTROL_CTS_RTS
// } mico_uart_flow_control_t;

// typedef enum
// {
//     NO_PARITY,
//     ODD_PARITY,
//     EVEN_PARITY,
// } mico_uart_parity_t;

#define UART_WAKEUP_MASK_POSN   0
#define UART_WAKEUP_DISABLE    (0 << UART_WAKEUP_MASK_POSN) /**< UART can not wakeup MCU from stop mode */
#define UART_WAKEUP_ENABLE     (1 << UART_WAKEUP_MASK_POSN) /**< UART can wake up MCU from stop mode */


/******************************************************
 *                    Structures
 ******************************************************/

//  typedef struct
// {
//     uint32_t                  baud_rate;
//     mico_uart_data_width_t    data_width;
//     mico_uart_parity_t        parity;
//     mico_uart_stop_bits_t     stop_bits;
//     mico_uart_flow_control_t  flow_control;
//     uint8_t                   flags;          /**< if set, UART can wake up MCU from stop mode, reference: @ref UART_WAKEUP_DISABLE and @ref UART_WAKEUP_ENABLE*/
// } mico_uart_config_t;

/******************************************************
 *                 Type Definitions
 ******************************************************/
 typedef platform_uart_config_t                  mico_uart_config_t;

/******************************************************
 *                 Function Declarations
 ******************************************************/

/** @defgroup MICO_UART MICO UART Driver
* @brief  Universal Asynchronous Receiver Transmitter (UART) Functions
* @{
*/


/** Initialises a UART interface
 *
 * Prepares an UART hardware interface for communications
 *
 * @param  uart     : the interface which should be initialised
 * @param  config   : UART configuration structure
 * @param  optional_rx_buffer : Pointer to an optional RX ring buffer
 *
 * @return    kNoErr        : on success.
 * @return    kGeneralErr   : if an error occurred with any step
 */
OSStatus MicoUartInitialize( mico_uart_t uart, const mico_uart_config_t* config, ring_buffer_t* optional_rx_buffer );


/** Initialises a STDIO UART interface, internal use only
 *
 * Prepares an UART hardware interface for stdio communications
 *
 * @param  config   : UART configuration structure
 * @param  optional_rx_buffer : Pointer to an optional RX ring buffer
 *
 * @return    kNoErr        : on success.
 * @return    kGeneralErr   : if an error occurred with any step
 */
OSStatus MicoStdioUartInitialize( const mico_uart_config_t* config, ring_buffer_t* optional_rx_buffer );


/** Deinitialises a UART interface
 *
 * @param  uart : the interface which should be deinitialised
 *
 * @return    kNoErr        : on success.
 * @return    kGeneralErr   : if an error occurred with any step
 */
OSStatus MicoUartFinalize( mico_uart_t uart );


/** Transmit data on a UART interface
 *
 * @param  uart     : the UART interface
 * @param  data     : pointer to the start of data
 * @param  size     : number of bytes to transmit
 *
 * @return    kNoErr        : on success.
 * @return    kGeneralErr   : if an error occurred with any step
 */
OSStatus MicoUartSend( mico_uart_t uart, const void* data, uint32_t size );


/** Receive data on a UART interface
 *
 * @param  uart     : the UART interface
 * @param  data     : pointer to the buffer which will store incoming data
 * @param  size     : number of bytes to receive
 * @param  timeout  : timeout in milisecond
 *
 * @return    kNoErr        : on success.
 * @return    kGeneralErr   : if an error occurred with any step
 */
OSStatus MicoUartRecv( mico_uart_t uart, void* data, uint32_t size, uint32_t timeout );

/** Read the length of the data that is already recived by uart driver and stored in buffer
 *
 * @param  uart     : the UART interface
 *
 * @return    Data length
 */
uint32_t MicoUartGetLengthInBuffer( mico_uart_t uart ); 

/** @} */
/** @} */

#endif