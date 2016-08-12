/*
 * Copyright 2013, Broadcom Corporation
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Broadcom Corporation;
 * the contents of this file may not be disclosed to third parties, copied
 * or duplicated in any form, in whole or in part, without the prior
 * written permission of Broadcom Corporation.
 */

#include "MicoRtos.h"
#include "misc.h"
#include "string.h" /* For memcpy */
#include "platform_config.h"
#include "platform_peripheral.h"
#include "PlatformLogging.h"
#include "wlan_platform_common.h"

/******************************************************
 *             Constants
 ******************************************************/

#define DMA_TIMEOUT_LOOPS      (10000000)

/**
 * Transfer direction for the mico platform bus interface
 */
typedef enum
{
    /* If updating this enum, the bus_direction_mapping variable will also need to be updated */
    BUS_READ,
    BUS_WRITE
} bus_transfer_direction_t;

/******************************************************
 *             Structures
 ******************************************************/

/******************************************************
 *             Variables
 ******************************************************/

static mico_semaphore_t spi_transfer_finished_semaphore;

/******************************************************
 *             Function declarations
 ******************************************************/

/* Powersave functionality */
extern void MCU_CLOCKS_NEEDED( void );
extern void MCU_CLOCKS_NOT_NEEDED( void );

extern void wiced_platform_notify_irq( void );

/******************************************************
 *             Function definitions
 ******************************************************/
static void clear_dma_interrupts( DMA_Stream_TypeDef* stream, uint32_t flags )
{
    if ( stream <= DMA1_Stream3 )
    {
        DMA1->LIFCR |= flags;
    }
    else if ( stream <= DMA1_Stream7 )
    {
        DMA1->HIFCR |= flags;
    }
    else if ( stream <= DMA2_Stream3 )
    {
        DMA2->LIFCR |= flags;
    }
    else
    {
        DMA2->HIFCR |= flags;
    }
}


static void spi_irq_handler( void* arg )
{
    UNUSED_PARAMETER(arg);
#ifndef MICO_DISABLE_MCU_POWERSAVE
    platform_mcu_powersave_exit_notify( );
#endif /* ifndef MICO_DISABLE_MCU_POWERSAVE */
    wiced_platform_notify_irq( );
}

void platform_wifi_spi_rx_dma_irq( void )
{
    /* Clear interrupt */
    clear_dma_interrupts( wifi_spi.rx_dma.stream, wifi_spi.rx_dma.complete_flags );
    mico_rtos_set_semaphore( &spi_transfer_finished_semaphore );
}

OSStatus host_platform_bus_init( void )
{
    SPI_InitTypeDef  spi_init;
    DMA_InitTypeDef  dma_init_structure;
    uint32_t         a;

    platform_mcu_powersave_disable();

    mico_rtos_init_semaphore(&spi_transfer_finished_semaphore, 1);

    /* Enable SPI_SLAVE DMA clock */
    if ( wifi_spi.tx_dma.controller == DMA1 )
    {
        RCC->AHB1ENR |= RCC_AHB1Periph_DMA1;
    }
    else
    {
        RCC->AHB1ENR |= RCC_AHB1Periph_DMA2;
    }


    if ( wifi_spi.rx_dma.controller == DMA1 )
    {
        RCC->AHB1ENR |= RCC_AHB1Periph_DMA1;
    }
    else
    {
        RCC->AHB1ENR |= RCC_AHB1Periph_DMA2;
    }


    /* Enable SPI_SLAVE Periph clock */
    (wifi_spi.peripheral_clock_func)( wifi_spi.peripheral_clock_reg, ENABLE );

    /* Enable SYSCFG. Needed for selecting EXTI interrupt line */
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_SYSCFG, ENABLE );


    /* Setup the interrupt input for WLAN_IRQ */
    platform_gpio_init( &wifi_spi_pins[WIFI_PIN_SPI_IRQ], INPUT_HIGH_IMPEDANCE );
    platform_gpio_irq_enable( &wifi_spi_pins[WIFI_PIN_SPI_IRQ], IRQ_TRIGGER_RISING_EDGE, spi_irq_handler, 0 );

    /* Setup SPI slave select GPIOs */
    platform_gpio_init( &wifi_spi_pins[WIFI_PIN_SPI_CS], OUTPUT_PUSH_PULL );
    platform_gpio_output_high( &wifi_spi_pins[WIFI_PIN_SPI_CS] );

    /* Setup the SPI lines */
    for ( a = WIFI_PIN_SPI_CLK; a < WIFI_PIN_SPI_MAX; a++ )
    {
        platform_gpio_set_alternate_function( wifi_spi_pins[ a ].port, wifi_spi_pins[ a ].pin_number, GPIO_OType_PP, GPIO_PuPd_NOPULL, wifi_spi.gpio_af );
    }

#if defined ( MICO_WIFI_USE_GPIO_FOR_BOOTSTRAP )
    /* Set GPIO_B[1:0] to 01 to put WLAN module into gSPI mode */
    platform_gpio_init( &wifi_control_pins[WIFI_PIN_BOOTSTRAP_0], OUTPUT_PUSH_PULL );
    platform_gpio_output_high( &wifi_control_pins[WIFI_PIN_BOOTSTRAP_0] );
    platform_gpio_init( &wifi_control_pins[WIFI_PIN_BOOTSTRAP_1], OUTPUT_PUSH_PULL );
    platform_gpio_output_low( &wifi_control_pins[WIFI_PIN_BOOTSTRAP_1] );
#endif

    /* Setup DMA for SPIX RX */
    DMA_DeInit( wifi_spi.rx_dma.stream );
    dma_init_structure.DMA_Channel = wifi_spi.rx_dma.channel;
    dma_init_structure.DMA_PeripheralBaseAddr = (uint32_t) &(wifi_spi.port->DR);
    dma_init_structure.DMA_Memory0BaseAddr = 0;
    dma_init_structure.DMA_DIR = DMA_DIR_PeripheralToMemory;
    dma_init_structure.DMA_BufferSize = 0;
    dma_init_structure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    dma_init_structure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    dma_init_structure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    dma_init_structure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    dma_init_structure.DMA_Mode = DMA_Mode_Normal;
    dma_init_structure.DMA_Priority = DMA_Priority_VeryHigh;
    dma_init_structure.DMA_FIFOMode = DMA_FIFOMode_Disable;
    dma_init_structure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
    dma_init_structure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
    dma_init_structure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
    DMA_Init( wifi_spi.rx_dma.stream, &dma_init_structure );

    /* Setup DMA for SPIX TX */
    DMA_DeInit( wifi_spi.tx_dma.stream );
    dma_init_structure.DMA_Channel =  wifi_spi.tx_dma.channel;
    dma_init_structure.DMA_PeripheralBaseAddr = (uint32_t) &(wifi_spi.port->DR);
    dma_init_structure.DMA_Memory0BaseAddr = 0;
    dma_init_structure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
    dma_init_structure.DMA_BufferSize = 0;
    dma_init_structure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    dma_init_structure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    dma_init_structure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    dma_init_structure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    dma_init_structure.DMA_Mode = DMA_Mode_Normal;
    dma_init_structure.DMA_Priority = DMA_Priority_VeryHigh;
    dma_init_structure.DMA_FIFOMode = DMA_FIFOMode_Disable;
    dma_init_structure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
    dma_init_structure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
    dma_init_structure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
    DMA_Init( wifi_spi.tx_dma.stream, &dma_init_structure );

    /* Must be lower priority than the value of configMAX_SYSCALL_INTERRUPT_PRIORITY */
    /* otherwise FreeRTOS will not be able to mask the interrupt */
    /* keep in mind that ARMCM3 interrupt priority logic is inverted, the highest value */
    /* is the lowest priority */
    NVIC_EnableIRQ( wifi_spi.rx_dma.irq_vector );

    /* Enable DMA for TX */
    SPI_I2S_DMACmd( wifi_spi.port, SPI_I2S_DMAReq_Tx | SPI_I2S_DMAReq_Rx, ENABLE );

    /* Setup SPI */
    spi_init.SPI_Direction         = SPI_Direction_2Lines_FullDuplex;
    spi_init.SPI_Mode              = SPI_Mode_Master;
    spi_init.SPI_DataSize          = SPI_DataSize_8b;
    spi_init.SPI_CPOL              = SPI_CPOL_High;
    spi_init.SPI_CPHA              = SPI_CPHA_2Edge;
    spi_init.SPI_NSS               = SPI_NSS_Soft;
    spi_init.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
    spi_init.SPI_FirstBit          = SPI_FirstBit_MSB;
    spi_init.SPI_CRCPolynomial     = (uint16_t) 7;

    /* Init SPI and enable it */
    SPI_Init( wifi_spi.port, &spi_init );
    SPI_Cmd( wifi_spi.port, ENABLE );

    platform_mcu_powersave_enable();

    return kNoErr;
}

OSStatus host_platform_bus_deinit( void )
{
    uint32_t         a;

    platform_mcu_powersave_disable();

    /* Disable SPI and SPI DMA */
    SPI_Cmd( wifi_spi.port, DISABLE );
    SPI_I2S_DeInit( wifi_spi.port );
    SPI_I2S_DMACmd( wifi_spi.port, SPI_I2S_DMAReq_Tx | SPI_I2S_DMAReq_Rx, DISABLE );
    DMA_DeInit( wifi_spi.tx_dma.stream );
    DMA_DeInit( wifi_spi.rx_dma.stream );

#if defined ( MICO_WIFI_USE_GPIO_FOR_BOOTSTRAP )
    /* Clear GPIO_B[1:0] */
    platform_gpio_init( &wifi_control_pins[WIFI_PIN_BOOTSTRAP_0], INPUT_HIGH_IMPEDANCE );
    platform_gpio_init( &wifi_control_pins[WIFI_PIN_BOOTSTRAP_1], INPUT_HIGH_IMPEDANCE );
#endif

    /* Clear SPI slave select GPIOs */
    platform_gpio_init( &wifi_spi_pins[WIFI_PIN_SPI_CS], INPUT_HIGH_IMPEDANCE );

    /* Clear the SPI lines */
    for ( a = WIFI_PIN_SPI_CLK; a < WIFI_PIN_SPI_MAX; a++ )
    {
        platform_gpio_init( &wifi_spi_pins[ a ], INPUT_HIGH_IMPEDANCE );
    }

    platform_gpio_irq_disable( &wifi_spi_pins[WIFI_PIN_SPI_IRQ] );
    platform_gpio_init( &wifi_spi_pins[WIFI_PIN_SPI_IRQ], INPUT_HIGH_IMPEDANCE );

    /* Disable SPI_SLAVE Periph clock and DMA1 clock */
    (wifi_spi.peripheral_clock_func)( wifi_spi.peripheral_clock_reg, DISABLE );
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_SYSCFG, DISABLE );

    platform_mcu_powersave_enable();

    return kNoErr;
}



OSStatus host_platform_spi_transfer( bus_transfer_direction_t dir, uint8_t* buffer, uint16_t buffer_length )
{
    OSStatus result;
    uint32_t junk;

    platform_mcu_powersave_disable();

    wifi_spi.tx_dma.stream->NDTR = buffer_length;
    wifi_spi.tx_dma.stream->M0AR = (uint32_t) buffer;
    if ( dir == BUS_READ )
    {
        wifi_spi.rx_dma.stream->NDTR = buffer_length;
        wifi_spi.rx_dma.stream->M0AR = (uint32_t) buffer;
        wifi_spi.rx_dma.stream->CR  |= DMA_MemoryInc_Enable  | ( 1 << 4);
    }
    else
    {
        wifi_spi.rx_dma.stream->NDTR = buffer_length;
        wifi_spi.rx_dma.stream->M0AR = (uint32_t) &junk;
        wifi_spi.rx_dma.stream->CR &= ( ~DMA_MemoryInc_Enable ) | ( 1 << 4);
    }

    platform_gpio_output_low( &wifi_spi_pins[WIFI_PIN_SPI_CS] );
    DMA_Cmd( wifi_spi.rx_dma.stream, ENABLE );
    DMA_Cmd( wifi_spi.tx_dma.stream, ENABLE );

    /* Wait for DMA TX to complete */
    result = mico_rtos_get_semaphore( &spi_transfer_finished_semaphore, 100 );
//    loop_count = 0;
//    while ( ( DMA_GetFlagStatus( SPIX_DMA_RX_STREAM, DMA_FLAG_TCIF3 ) == RESET ) && ( loop_count < (uint32_t) DMA_TIMEOUT_LOOPS ) )
//    {
//        loop_count++;
//    }

    DMA_Cmd( wifi_spi.rx_dma.stream, DISABLE );
    DMA_Cmd( wifi_spi.tx_dma.stream, DISABLE );

    /* Clear the CS pin and the DMA status flag */
    platform_gpio_output_high( &wifi_spi_pins[WIFI_PIN_SPI_CS] ); /* CS high (to deselect) */
    clear_dma_interrupts( wifi_spi.rx_dma.stream, wifi_spi.rx_dma.complete_flags );
    clear_dma_interrupts( wifi_spi.tx_dma.stream, wifi_spi.tx_dma.complete_flags );

    platform_mcu_powersave_enable();

    return result;
}
