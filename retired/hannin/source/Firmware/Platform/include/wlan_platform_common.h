/**
******************************************************************************
* @file    wlan_platform_common.h
* @author  William Xu
* @version V1.0.0
* @date    20-March-2015
* @brief   This file provide wlan IO pin define.
******************************************************************************
*
*  The MIT License
*  Copyright (c) 2015 MXCHIP Inc.
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


#pragma once

#include "platform_peripheral.h"
#include "platform_config.h"

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************
 *                      Macros
 ******************************************************/

/******************************************************
 *                    Constants
 ******************************************************/

/******************************************************
 *                   Enumerations
 ******************************************************/

/******************************************************
 *                 Type Definitions
 ******************************************************/

/**
 * WLAN control pins
 */
typedef enum
{
    WIFI_PIN_POWER,
    WIFI_PIN_RESET,
    WIFI_PIN_32K_CLK,
    WIFI_PIN_BOOTSTRAP_0,
    WIFI_PIN_BOOTSTRAP_1,
    WIFI_PIN_CONTROL_MAX,
} wifi_control_pin_t;

/**
 * WLAN SDIO pins
 */

typedef enum
{
#ifdef SDIO_1_BIT
    WIFI_PIN_SDIO_IRQ,
#else
    WIFI_PIN_SDIO_OOB_IRQ,
#endif
    WIFI_PIN_SDIO_CLK,
    WIFI_PIN_SDIO_CMD,
    WIFI_PIN_SDIO_D0,
#ifndef SDIO_1_BIT
    WIFI_PIN_SDIO_D1,
    WIFI_PIN_SDIO_D2,
    WIFI_PIN_SDIO_D3,
#endif
    WIFI_PIN_SDIO_MAX,
} wifi_sdio_pin_t;

/**
 * WLAN SPI pins
 */
typedef enum
{
    WIFI_PIN_SPI_IRQ,
    WIFI_PIN_SPI_CS,
    WIFI_PIN_SPI_CLK,
    WIFI_PIN_SPI_MOSI,
    WIFI_PIN_SPI_MISO,
    WIFI_PIN_SPI_MAX,
} emw1062_spi_pin_t;

/******************************************************
 *                    Structures
 ******************************************************/

/******************************************************
 *                 Global Variables
 ******************************************************/

/* Externed from <WICED-SDK>/platforms/<Platform>/platform.c */
extern const platform_gpio_t wifi_control_pins[];
extern const platform_gpio_t wifi_sdio_pins   [];
extern const platform_gpio_t wifi_spi_pins    [];
extern const platform_spi_t  wifi_spi;

/******************************************************
 *               Function Declarations
 ******************************************************/

extern void platform_wifi_spi_rx_dma_irq( void );


#ifdef __cplusplus
} /*extern "C" */
#endif
