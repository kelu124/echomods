/**
******************************************************************************
* @file    platform_init.c 
* @author  William Xu
* @version V1.0.0
* @date    05-May-2014
* @brief   This file provide functions called by MICO to drive stm32f2xx 
*          platform: - e.g. power save, reboot, platform initialize
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


#include "platform_peripheral.h"
#include "platform.h"
#include "platform_config.h"
#include "MicoPlatform.h"
#include "PlatformLogging.h"
#include <string.h> // For memcmp
#include "crt0.h"
#include "MICODefaults.h"
#include "MicoRTOS.h"
#include "platform_init.h"

#ifdef __GNUC__
#include "../../GCC/stdio_newlib.h"
#endif /* ifdef __GNUC__ */


/******************************************************
*                      Macros
******************************************************/

/******************************************************
*                    Constants
******************************************************/

#ifndef STDIO_BUFFER_SIZE
#define STDIO_BUFFER_SIZE   64
#endif

/******************************************************
*                   Enumerations
******************************************************/

/******************************************************
*                 Type Definitions
******************************************************/

/******************************************************
*                    Structures
******************************************************/

/******************************************************
*               Function Declarations
******************************************************/

extern OSStatus host_platform_init( void );

/******************************************************
*               Variables Definitions
******************************************************/
extern platform_uart_t platform_uart_peripherals[];
extern platform_uart_driver_t platform_uart_drivers[];
  
/* mico_cpu_clock_hz is used by MICO RTOS */
const uint32_t  mico_cpu_clock_hz = 120000000;

#ifndef MICO_DISABLE_STDIO
static const mico_uart_config_t stdio_uart_config =
{
  .baud_rate    = STDIO_UART_BAUDRATE,
  .data_width   = DATA_WIDTH_8BIT,
  .parity       = NO_PARITY,
  .stop_bits    = STOP_BITS_1,
  .flow_control = FLOW_CONTROL_DISABLED,
  .flags        = 0,
};

static volatile ring_buffer_t stdio_rx_buffer;
static volatile uint8_t             stdio_rx_data[STDIO_BUFFER_SIZE];
mico_mutex_t        stdio_rx_mutex;
mico_mutex_t        stdio_tx_mutex;
#endif /* #ifndef MICO_DISABLE_STDIO */

/******************************************************
*               Function Definitions
******************************************************/
#if defined ( __ICCARM__ )
static inline void __jump_to( uint32_t addr )
{
  __asm( "MOV R1, #0x00000001" );
  __asm( "ORR R0, R0, R1" );  /* Last bit of jump address indicates whether destination is Thumb or ARM code */
  __asm( "BLX R0" );
}


#elif defined ( __GNUC__ )
__attribute__( ( always_inline ) ) static __INLINE void __jump_to( uint32_t addr )
{
  addr |= 0x00000001;  /* Last bit of jump address indicates whether destination is Thumb or ARM code */
  __ASM volatile ("BX %0" : : "r" (addr) );
}


#elif defined ( __CC_ARM )
static void __asm __jump_to( uint32_t addr )
{
  MOV R1, #0x00000001
  ORR R0, R0, R1  /* Last bit of jump address indicates whether destination is Thumb or ARM code */
  BLX R0
}
#endif

/*Boot to mico application form APPLICATION_START_ADDRESS defined in platform_common_config.h */
void startApplication(void)
{
  uint32_t text_addr = APPLICATION_START_ADDRESS;
  uint32_t* stack_ptr;
  uint32_t* start_ptr;
  SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
  
  /* Clear all interrupt enabled by bootloader */
  for (int i = 0; i < 8; i++ )
    NVIC->ICER[i] = 0x00;
  
  if (((*(volatile uint32_t*)text_addr) & 0x2FFE0000 ) != 0x20000000)
  text_addr += 0x200;
  /* Test if user code is programmed starting from address "ApplicationAddress" */
  if (((*(volatile uint32_t*)text_addr) & 0x2FFE0000 ) == 0x20000000)
  { 
    stack_ptr = (uint32_t*) text_addr;  /* Initial stack pointer is first 4 bytes of vector table */
    start_ptr = ( stack_ptr + 1 );  /* Reset vector is second 4 bytes of vector table */

    #if defined ( __ICCARM__)
    __ASM( "MOV LR,        #0xFFFFFFFF" );
    __ASM( "MOV R1,        #0x01000000" );
    __ASM( "MSR APSR_nzcvq,     R1" );
    __ASM( "MOV R1,        #0x00000000" );
    __ASM( "MSR PRIMASK,   R1" );
    __ASM( "MSR FAULTMASK, R1" );
    __ASM( "MSR BASEPRI,   R1" );
    __ASM( "MSR CONTROL,   R1" );
    #endif
    
    __set_MSP( *stack_ptr );
    __jump_to( *start_ptr );
  }  
}

void platform_mcu_reset( void )
{
    NVIC_SystemReset();
}

/* STM32F2 common clock initialisation function
* This brings up enough clocks to allow the processor to run quickly while initialising memory.
* Other platform specific clock init can be done in init_platform() or init_architecture()
*/
void init_clocks( void )
{
  //RCC_DeInit( ); /* if not commented then the LSE PA8 output will be disabled and never comes up again */
  
  /* Configure Clocks */
  RCC_HSEConfig( HSE_SOURCE );
  RCC_WaitForHSEStartUp( );
  
  RCC_HCLKConfig( AHB_CLOCK_DIVIDER );
  RCC_PCLK2Config( APB2_CLOCK_DIVIDER );
  RCC_PCLK1Config( APB1_CLOCK_DIVIDER );
  
  /* Enable the PLL */
  FLASH_SetLatency( INT_FLASH_WAIT_STATE );
  FLASH_PrefetchBufferCmd( ENABLE );
  
  /* Use the clock configuration utility from ST to calculate these values
  * http://www.st.com/st-web-ui/static/active/en/st_prod_software_internet/resource/technical/software/utility/stsw-stm32090.zip
  */
  RCC_PLLConfig( PLL_SOURCE, PLL_M_CONSTANT, PLL_N_CONSTANT, PLL_P_CONSTANT, PPL_Q_CONSTANT ); /* NOTE: The CPU Clock Frequency is independently defined in <WICED-SDK>/Wiced/Platform/<platform>/<platform>.mk */
  RCC_PLLCmd( ENABLE );
  
  while ( RCC_GetFlagStatus( RCC_FLAG_PLLRDY ) == RESET )
  {
  }
  RCC_SYSCLKConfig( SYSTEM_CLOCK_SOURCE );
  
  while ( RCC_GetSYSCLKSource( ) != 0x08 )
  {
  }
  
  /* Configure HCLK clock as SysTick clock source. */
  SysTick_CLKSourceConfig( SYSTICK_CLOCK_SOURCE );
#ifdef NO_MICO_RTOS  
  SysTick_Config( SystemCoreClock / 1000 );
#endif
}

WEAK void init_memory( void )
{
  
}

void init_architecture( void )
{
  uint8_t i;
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
  
   /*STM32 wakeup by watchdog in standby mode, re-enter standby mode in this situation*/
  if ( (PWR_GetFlagStatus(PWR_FLAG_SB) != RESET) && RCC_GetFlagStatus(RCC_FLAG_IWDGRST) != RESET){
     RCC_ClearFlag();
     PWR_EnterSTANDBYMode();
   }
  PWR_ClearFlag(PWR_FLAG_SB);
  
  /* Initialise the interrupt priorities to a priority lower than 0 so that the BASEPRI register can mask them */
  for ( i = 0; i < 81; i++ )
  {
    NVIC ->IP[i] = 0xff;
  }
  
  NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 );

  platform_init_peripheral_irq_priorities();

  /* Initialise GPIO IRQ manager */
  platform_gpio_irq_manager_init();
  
#ifndef MICO_DISABLE_STDIO
#ifndef NO_MICO_RTOS
  mico_rtos_init_mutex( &stdio_tx_mutex );
  mico_rtos_unlock_mutex ( &stdio_tx_mutex );
  mico_rtos_init_mutex( &stdio_rx_mutex );
  mico_rtos_unlock_mutex ( &stdio_rx_mutex );
#endif

  ring_buffer_init  ( (ring_buffer_t*)&stdio_rx_buffer, (uint8_t*)stdio_rx_data, STDIO_BUFFER_SIZE );
  platform_uart_init( &platform_uart_drivers[STDIO_UART], &platform_uart_peripherals[STDIO_UART], &stdio_uart_config, (ring_buffer_t*)&stdio_rx_buffer );
#endif

  /* Ensure 802.11 device is in reset. */
  host_platform_init( );

#ifdef BOOTLOADER
  return;
#endif
  
  /* Initialise RTC */
  platform_rtc_init( );
  
#ifndef MICO_DISABLE_MCU_POWERSAVE
  /* Initialise MCU powersave */
  platform_mcu_powersave_init( );
#endif /* ifndef MICO_DISABLE_MCU_POWERSAVE */

  platform_mcu_powersave_disable( );
}

OSStatus stdio_hardfault( char* data, uint32_t size )
{
  extern const platform_uart_t       platform_uart_peripherals[];
#ifndef MICO_DISABLE_STDIO
  uint32_t idx;
  for(idx = 0; idx < size; idx++){
    while ( ( platform_uart_peripherals[ STDIO_UART ].port->SR & USART_SR_TXE ) == 0 );
    platform_uart_peripherals[ STDIO_UART ].port->DR = (data[idx] & (uint16_t)0x01FF);
    
  }
#endif
  return kNoErr;
}

/******************************************************
*            NO-OS Functions
******************************************************/


#ifdef NO_MICO_RTOS
static volatile uint32_t no_os_tick = 0;

void SysTick_Handler(void)
{
  no_os_tick ++;
  platform_watchdog_kick( );
}

uint32_t mico_get_time_no_os(void)
{
  return no_os_tick;
}

void mico_thread_msleep_no_os(uint32_t milliseconds)
{
  int tick_delay_start = mico_get_time_no_os();
  while(mico_get_time_no_os() < tick_delay_start+milliseconds);  
}
#endif


