/**
******************************************************************************
* @file    spi_flash.h 
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
#ifndef INCLUDED_SPI_FLASH_API_H
#define INCLUDED_SPI_FLASH_API_H

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>

typedef enum
{
    SFLASH_WRITE_NOT_ALLOWED = 0,
    SFLASH_WRITE_ALLOWED     = 1,

} sflash_write_allowed_t;

typedef struct
{
    uint32_t device_id;
    void * platform_peripheral;
    sflash_write_allowed_t write_allowed;
} sflash_handle_t;

int init_sflash         ( /*@out@*/ sflash_handle_t* const handle, /*@shared@*/ void* peripheral_id, sflash_write_allowed_t write_allowed_in );
int sflash_read         ( const sflash_handle_t* const handle, unsigned long device_address, /*@out@*/  /*@dependent@*/ void* const data_addr, unsigned int size );
int sflash_write        ( const sflash_handle_t* const handle, unsigned long device_address,  /*@observer@*/ const void* const data_addr, unsigned int size );
int sflash_chip_erase   ( const sflash_handle_t* const handle );
int sflash_sector_erase ( const sflash_handle_t* const handle, unsigned long device_address );
int sflash_get_size     ( const sflash_handle_t* const handle, /*@out@*/ unsigned long* size );



#ifdef __cplusplus
}
#endif

#endif /* INCLUDED_SPI_FLASH_API_H */
