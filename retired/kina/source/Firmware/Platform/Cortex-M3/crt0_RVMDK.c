/**
******************************************************************************
* @file    crt0_IAR.h 
* @author  William Xu
* @version V1.0.0
* @date    16-Sep-2014
* @brief   __low_level_init called by IAR before main.
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

#include "platform.h"
#include "crt0.h"

extern void* app_hdr_start_addr_loc;
#define SCB_VTOR_ADDRESS         ( ( volatile unsigned long* ) 0xE000ED08 )
#define APP_HDR_START_ADDR   ((unsigned char*)&app_hdr_start_addr_loc)
  
extern unsigned long Image$$ER_IROM1$$Base;

int __low_level_init( void );

/* This is the code that gets called on processor reset. To initialize the */
/* device. */
int __low_level_init( void )
{
     extern void init_clocks(void);
     extern void init_memory(void);
     /* IAR allows init functions in __low_level_init(), but it is run before global
      * variables have been initialised, so the following init still needs to be done
      * When using GCC, this is done in crt0_GCC.c
      */
     
     /* Setup the interrupt vectors address */
     *SCB_VTOR_ADDRESS = (unsigned long)&Image$$ER_IROM1$$Base;
     init_clocks();
     init_memory();

     return 1; /* return 1 to force memory init */
}
