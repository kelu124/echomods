/**
******************************************************************************
* @file    spi_flash_platform.c 
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
#include "spi_flash_platform_interface.h"
#include "MicoPlatform.h"

#if defined ( USE_MICO_SPI_FLASH )

int sflash_platform_init ( /*@shared@*/ void* peripheral_id, /*@out@*/ void** platform_peripheral_out )
{
    UNUSED_PARAMETER( peripheral_id );  /* Unused due to single SPI Flash */

    if ( kNoErr != MicoSpiInitialize( &mico_spi_flash ) )
    {
        /*@-mustdefine@*/ /* Lint: failed - do not define platform peripheral */
        return -1;
        /*@+mustdefine@*/
    }

    if( platform_peripheral_out != NULL)
      *platform_peripheral_out = NULL;
    
    return 0;
}


extern int sflash_platform_send_recv ( const void* platform_peripheral, /*@in@*/ /*@out@*/ sflash_platform_message_segment_t* segments, unsigned int num_segments  )
{
    UNUSED_PARAMETER( platform_peripheral );

    if ( kNoErr != MicoSpiTransfer( &mico_spi_flash, (mico_spi_message_segment_t*) segments, (uint16_t) num_segments ) )
    {
        return -1;
    }

    return 0;
}
#else
int sflash_platform_init( /*@shared@*/ void* peripheral_id, /*@out@*/ void** platform_peripheral_out )
{
    UNUSED_PARAMETER( peripheral_id );
    UNUSED_PARAMETER( platform_peripheral_out );
    return -1;
}

extern int sflash_platform_send_recv( const void* platform_peripheral, /*@in@*//*@out@*/sflash_platform_message_segment_t* segments, unsigned int num_segments )
{
    UNUSED_PARAMETER( platform_peripheral );
    UNUSED_PARAMETER( segments );
    UNUSED_PARAMETER( num_segments );
    return -1;
}
#endif
