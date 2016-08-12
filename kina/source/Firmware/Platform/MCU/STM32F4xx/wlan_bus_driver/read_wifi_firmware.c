/**
******************************************************************************
* @file    read_wifi_firmware.h
* @author  William Xu
* @version V1.0.0
* @date    05-May-2014
* @brief   This file provides function called by MICO when reading RF chip's
*          firmware.
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

#include "Common.h"
#include "MicoPlatform.h"
#include "platform_config.h"


#ifndef MICO_FLASH_FOR_DRIVER
extern uint32_t wifi_firmware_image_size;
extern unsigned char wifi_firmware_image[];

uint32_t platform_get_wifi_image_size(void)
{
    return wifi_firmware_image_size;
}

uint32_t platform_get_wifi_image(unsigned char* buffer, uint32_t size, uint32_t offset)
{
    uint32_t buffer_size;
    buffer_size = MIN(size, (wifi_firmware_image_size - offset));
    memcpy(buffer, &wifi_firmware_image[offset], buffer_size);

    return buffer_size;
}

#else

static uint32_t image_size = DRIVER_FLASH_SIZE;

uint32_t platform_get_wifi_image_size(void)
{
#define READ_LEN 2048
    uint32_t FlashAddress = DRIVER_START_ADDRESS + DRIVER_FLASH_SIZE;
    uint32_t imageTail;
    uint32_t *p;
    uint32_t *buf = (uint32_t *)malloc(READ_LEN);

    image_size = DRIVER_FLASH_SIZE;
    do {
        FlashAddress -= READ_LEN; // Next block
        MicoFlashRead(MICO_FLASH_FOR_DRIVER, &FlashAddress, (uint8_t *)buf, READ_LEN);
        FlashAddress -= READ_LEN; // MicoFlashRead will increase FlashAddress READ_LEN, move back.
        p = buf + (READ_LEN - 4)/sizeof(uint32_t);
        while(p >= buf) {
            if (*p != 0xFFFFFFFF) {
                goto EXIT;
            }
            p--;
            image_size -= 4;
        }
    } while (FlashAddress > DRIVER_START_ADDRESS);

EXIT:
    free(buf);
    return image_size;
}

uint32_t platform_get_wifi_image(unsigned char* buffer, uint32_t size, uint32_t offset)
{
    uint32_t buffer_size;
    uint32_t FlashAddress = DRIVER_START_ADDRESS;
    
    buffer_size = MIN(size, (image_size - offset));
    FlashAddress += offset;

    MicoFlashRead(MICO_FLASH_FOR_DRIVER, &FlashAddress, buffer, buffer_size);
    return buffer_size;
}
#endif
