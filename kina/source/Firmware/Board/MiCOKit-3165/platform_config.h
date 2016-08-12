/**
******************************************************************************
* @file    platform_config.h
* @author  William Xu
* @version V1.0.0
* @date    05-May-2014
* @brief   This file provides common configuration for current platform.
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

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif


/******************************************************
*                      Macros
******************************************************/

/******************************************************
*                    Constants
******************************************************/
//doit
#define BOOTLOADER_FOR_MICO_KIT

#ifdef BOOTLOADER_FOR_MICO_KIT
  #define Bootloader_REVISION "V1.1"
  #define MODEL               "\"MicoKit of EMW3165\""
#else
  #define MODEL               "\"WiFiMCU Board\""
  #define Bootloader_REVISION "V1.1"
#endif

/* MICO RTOS tick rate in Hz */
#define MICO_DEFAULT_TICK_RATE_HZ                   (1000) 

/************************************************************************
 * Uncomment to disable watchdog. For debugging only */
//#define MICO_DISABLE_WATCHDOG

/************************************************************************
 * Uncomment to disable standard IO, i.e. printf(), etc. */
//#define MICO_DISABLE_STDIO

/************************************************************************
 * Uncomment to disable MCU powersave API functions */
//#define MICO_DISABLE_MCU_POWERSAVE

/************************************************************************
 * Uncomment to enable MCU real time clock */
//#define MICO_ENABLE_MCU_RTC

/************************************************************************
 * Restore default and start easylink after press down EasyLink button for 3 seconds. */
#define RestoreDefault_TimeOut                      (3000)


#define MCU_CLOCK_HZ            100000000

#define HSE_SOURCE              RCC_HSE_ON               /* Use external crystal                 */
#define AHB_CLOCK_DIVIDER       RCC_SYSCLK_Div1          /* AHB clock = System clock             */
#define APB1_CLOCK_DIVIDER      RCC_HCLK_Div2            /* APB1 clock = AHB clock / 2           */
#define APB2_CLOCK_DIVIDER      RCC_HCLK_Div1            /* APB2 clock = AHB clock / 1           */
#define PLL_SOURCE              RCC_PLLSource_HSE        /* PLL source = external crystal        */
#define PLL_M_CONSTANT          26                       /* PLLM = 16                            */
#define PLL_N_CONSTANT          400                      /* PLLN = 400                           */
#define PLL_P_CONSTANT          4                        /* PLLP = 4                             */
#define PPL_Q_CONSTANT          7                        /* PLLQ = 7                             */
#define SYSTEM_CLOCK_SOURCE     RCC_SYSCLKSource_PLLCLK  /* System clock source = PLL clock      */
#define SYSTICK_CLOCK_SOURCE    SysTick_CLKSource_HCLK   /* SysTick clock source = AHB clock     */
#define INT_FLASH_WAIT_STATE    FLASH_Latency_3          /* Internal flash wait state = 3 cycles */


/******************************************************
 *  EMW1062 Options
 ******************************************************/
/*  Wi-Fi chip module */
#define EMW1062
  
/*  GPIO pins are used to bootstrap Wi-Fi to SDIO or gSPI mode */
//#define MICO_WIFI_USE_GPIO_FOR_BOOTSTRAP

/*  Wi-Fi GPIO0 pin is used for out-of-band interrupt */
#define MICO_WIFI_OOB_IRQ_GPIO_PIN  ( 0 )

/*  Wi-Fi power pin is present */
//#define MICO_USE_WIFI_POWER_PIN

/*  Wi-Fi reset pin is present */
#define MICO_USE_WIFI_RESET_PIN

/*  Wi-Fi 32K pin is present */
//#define MICO_USE_WIFI_32K_PIN

/*  USE SDIO 1bit mode */
//#define SDIO_1_BIT

/* Wi-Fi power pin is active high */
//#define MICO_USE_WIFI_POWER_PIN_ACTIVE_HIGH

/*  WLAN Powersave Clock Source
 *  The WLAN sleep clock can be driven from one of two sources:
 *  1. MCO (MCU Clock Output) - default
 *  2. WLAN 32K internal oscillator (30% inaccuracy)
 */
#define MICO_USE_WIFI_32K_CLOCK_MCO

/* Memory map */

#define MICO_FLASH_FOR_BOOT         MICO_INTERNAL_FLASH
#define BOOT_START_ADDRESS          (uint32_t)0x08000000
#define BOOT_END_ADDRESS            (uint32_t)0x08007FFF
#define BOOT_FLASH_SIZE             (BOOT_END_ADDRESS - BOOT_START_ADDRESS + 1) /* 32k bytes*/

#define MICO_FLASH_FOR_PARA         MICO_SPI_FLASH
#define PARA_START_ADDRESS          (uint32_t)0x00000000
#define PARA_END_ADDRESS            (uint32_t)0x00000FFF
#define PARA_FLASH_SIZE             (PARA_END_ADDRESS - PARA_START_ADDRESS + 1)   /* 4k bytes*/

#define MICO_FLASH_FOR_EX_PARA      MICO_SPI_FLASH
#define EX_PARA_START_ADDRESS       (uint32_t)0x00001000
#define EX_PARA_END_ADDRESS         (uint32_t)0x00001FFF
#define EX_PARA_FLASH_SIZE          (EX_PARA_END_ADDRESS - EX_PARA_START_ADDRESS + 1)   /* 4k bytes*/

#define MICO_FLASH_FOR_APPLICATION  MICO_INTERNAL_FLASH
#define APPLICATION_START_ADDRESS   (uint32_t)0x0800C000
#define APPLICATION_END_ADDRESS     (uint32_t)0x0807FFFF
#define APPLICATION_FLASH_SIZE      (APPLICATION_END_ADDRESS - APPLICATION_START_ADDRESS + 1) /* 464 bytes*/

#define MICO_FLASH_FOR_UPDATE       MICO_SPI_FLASH  /* Optional */
#define UPDATE_START_ADDRESS        (uint32_t)0x00040000 /* Optional */
#define UPDATE_END_ADDRESS          (uint32_t)0x000BFFFF /* Optional */
#define UPDATE_FLASH_SIZE           (UPDATE_END_ADDRESS - UPDATE_START_ADDRESS + 1) /* 512k bytes, optional*/

#define MICO_FLASH_FOR_DRIVER       MICO_SPI_FLASH
#define DRIVER_START_ADDRESS        (uint32_t)0x00002000
#define DRIVER_END_ADDRESS          (uint32_t)0x0003FFFF
#define DRIVER_FLASH_SIZE           (DRIVER_END_ADDRESS - DRIVER_START_ADDRESS + 1) /* 248k bytes*/

#ifdef __cplusplus
} /*extern "C" */
#endif

 
