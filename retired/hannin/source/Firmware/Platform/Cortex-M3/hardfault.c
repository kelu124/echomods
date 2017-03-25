/**
******************************************************************************
* @file    hardfault.c 
* @author  William Xu
* @version V1.0.0
* @date    05-May-2014
* @brief   This file provide debug information in hardfault.
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

#include "stdio.h"
#include "MicoRTOS.h"
#include "MicoPlatform.h"
#include "platform.h"

extern OSStatus stdio_hardfault( char* data, uint32_t size );

#if   defined ( __CC_ARM )

//static __inline uint32_t __get_IPSR(void)
//{
//  register uint32_t __regIPSR          __asm("ipsr");
//  return(__regIPSR);
//}

#elif defined ( __ICCARM__ ) /*------------------ ICC Compiler -------------------*/
/* IAR iccarm specific functions */
#define __ASM           __asm                                       /*!< asm keyword for IAR Compiler          */
#define __INLINE        inline                                      /*!< inline keyword for IAR Compiler. Only available in High optimization mode! */
#include <cmsis_iar.h>

#elif defined ( __GNUC__ ) 

__attribute__( ( always_inline ) ) static inline uint32_t __get_IPSR(void)
{
  uint32_t result;
  
  __asm volatile ("MRS %0, ipsr" : "=r" (result) );
  return(result);
}

#endif
void hard_fault_handler_c (unsigned int * hardfault_args)
{
  unsigned int stacked_r0;
  unsigned int stacked_r1;
  unsigned int stacked_r2;
  unsigned int stacked_r3;
  unsigned int stacked_r12;
  unsigned int stacked_lr;
  unsigned int stacked_pc;
  unsigned int stacked_psr;
  char logString[50];
  
  stacked_r0 = ((unsigned long) hardfault_args[0]);
  stacked_r1 = ((unsigned long) hardfault_args[1]);
  stacked_r2 = ((unsigned long) hardfault_args[2]);
  stacked_r3 = ((unsigned long) hardfault_args[3]);
  
  stacked_r12 = ((unsigned long) hardfault_args[4]);
  stacked_lr = ((unsigned long) hardfault_args[5]);
  stacked_pc = ((unsigned long) hardfault_args[6]);
  stacked_psr = ((unsigned long) hardfault_args[7]);
  
  sprintf (logString,"\n>>>>>>>>>>>>>>[");
  stdio_hardfault( logString, strlen(logString)+1 );
  switch(__get_IPSR())
  {
    case	3:
      sprintf (logString, "Hard Fault");
      stdio_hardfault( logString, strlen(logString)+1 );
      break;
      
    case	4:
      sprintf (logString, "Memory Manage");
      stdio_hardfault( logString, strlen(logString)+1 );
      break;
        
    case	5:
      sprintf (logString, "Bus Fault");
      stdio_hardfault( logString, strlen(logString)+1 );
      break;
          
    case	6:
      sprintf (logString, "Usage Fault");
      stdio_hardfault( logString, strlen(logString)+1 );
      break;
            
  default:
    sprintf (logString, "Unknown Fault %d", __get_IPSR());
    stdio_hardfault( logString, strlen(logString)+1 );
    break;
  }
  sprintf (logString, ",corrupt,dump registers]>>>>>>>>>>>>>>>>>>\n\r");
  stdio_hardfault( logString, strlen(logString)+1 );
  
  sprintf (logString, "R0 = 0x08%x\r\n", stacked_r0);
  stdio_hardfault( logString, strlen(logString)+1 );
  sprintf (logString, "R1 = 0x%08x\r\n", stacked_r1);
  stdio_hardfault( logString, strlen(logString)+1 );
  sprintf (logString, "R2 = 0x%08x\r\n", stacked_r2);
  stdio_hardfault( logString, strlen(logString)+1 );
  sprintf (logString, "R3 = 0x%08x\r\n", stacked_r3);
  stdio_hardfault( logString, strlen(logString)+1 );
  sprintf (logString, "R12 = 0x%08x\r\n", stacked_r12);
  stdio_hardfault( logString, strlen(logString)+1 );
  sprintf (logString, "LR [R14] = 0x08%x  subroutine call return address\r\n", stacked_lr);
  stdio_hardfault( logString, strlen(logString)+1 );
  sprintf (logString, "PC [R15] = 0x08%x  program counter\r\n", stacked_pc);
  stdio_hardfault( logString, strlen(logString)+1 );
  sprintf (logString, "PSR = 0x08%x\r\n", stacked_psr);
  stdio_hardfault( logString, strlen(logString)+1 );
  sprintf (logString, "BFAR = 0x08%x\r\n", (*((volatile unsigned long *)(0xE000ED38))));
  stdio_hardfault( logString, strlen(logString)+1 );
  sprintf (logString, "CFSR = 0x%08x\r\n", (*((volatile unsigned long *)(0xE000ED28))));
  stdio_hardfault( logString, strlen(logString)+1 );
  sprintf (logString, "HFSR = 0x08%x\r\n", (*((volatile unsigned long *)(0xE000ED2C))));
  stdio_hardfault( logString, strlen(logString)+1 );
  sprintf (logString, "DFSR = 0x08%x\r\n", (*((volatile unsigned long *)(0xE000ED30))));
  stdio_hardfault( logString, strlen(logString)+1 );
  sprintf (logString, "AFSR = 0x08%x\r\n", (*((volatile unsigned long *)(0xE000ED3C))));
  stdio_hardfault( logString, strlen(logString)+1 );
  
  while (1);
}