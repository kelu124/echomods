/**
******************************************************************************
* @file    update_for_OTA.c 
* @author  William Xu
* @version V2.0.0
* @date    05-Oct-2014
* @brief   This file provides functions to overwrite the target flash contents 
*          using according the storeed in OTA temporary storage
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

#include "MicoPlatform.h"
#include "platform_config.h"
#include "debug.h"

typedef int Log_Status;					
#define Log_NotExist				1
#define Log_NeedUpdate				2
#define Log_UpdateTagNotExist		3
#define Log_contentTypeNotExist		4
#define Log_dataLengthOverFlow		5
#define Log_StartAddressERROR		6
#define Log_UnkonwnERROR			7

#define SizePerRW 4096   /* Bootloader need 2xSizePerRW RAM heap size to operate, 
                            but it can boost the setup. */

#ifdef MICO_FLASH_FOR_UPDATE
static uint8_t data[SizePerRW];
static uint8_t newData[SizePerRW];
static uint8_t paraSaveInRam[PARA_FLASH_SIZE];

static uint32_t destStartAddress, destEndAddress;
static mico_flash_t destFlashType;
#endif

/* Upgrade iamge should save this table to flash */
typedef struct  _boot_table_t {
  uint32_t start_address; // the address of the bin saved on flash.
  uint32_t length; // file real length
  uint8_t version[8];
  uint8_t type; // B:bootloader, P:boot_table, A:application, D: 8782 driver
  uint8_t upgrade_type; //u:upgrade, 
  uint8_t reserved[6];
}boot_table_t;

#define update_log(M, ...) custom_log("UPDATE", M, ##__VA_ARGS__)
#define update_log_trace() custom_log_trace("UPDATE")

#ifndef MICO_FLASH_FOR_UPDATE
OSStatus update(void)
{
  return kUnsupportedErr;
}
#else
Log_Status updateLogCheck(boot_table_t *updateLog)
{
  uint32_t i;
  
  for(i=0; i<sizeof(boot_table_t); i++){
    if(*((uint8_t *)updateLog + i) != 0xff)
      break;
  }
  if(i == sizeof(boot_table_t))
    return Log_NotExist;
  
  if(updateLog->upgrade_type == 'U'){
    if(updateLog->start_address != UPDATE_START_ADDRESS)
      return Log_StartAddressERROR;
    if(updateLog->type == 'B'){
      destStartAddress = BOOT_START_ADDRESS;
      destEndAddress = BOOT_END_ADDRESS;
      destFlashType = MICO_FLASH_FOR_BOOT;
      if(updateLog->length > BOOT_FLASH_SIZE)
        return Log_dataLengthOverFlow;
    }
    else if(updateLog->type == 'A'){
      destStartAddress = APPLICATION_START_ADDRESS;
      destEndAddress = APPLICATION_END_ADDRESS;
      destFlashType = MICO_FLASH_FOR_APPLICATION;
      if(updateLog->length > APPLICATION_FLASH_SIZE)
        return Log_dataLengthOverFlow;
    }
#ifdef MICO_FLASH_FOR_DRIVER
    else if(updateLog->type == 'D'){
      destStartAddress = DRIVER_START_ADDRESS;
      destEndAddress = DRIVER_END_ADDRESS;
      destFlashType = MICO_FLASH_FOR_DRIVER;
      if(updateLog->length > DRIVER_FLASH_SIZE)
        return Log_dataLengthOverFlow;
    }
#endif
    else 
      return Log_contentTypeNotExist;
    
    return Log_NeedUpdate;
  }
  else
    return Log_UpdateTagNotExist;
}


OSStatus update(void)
{
  boot_table_t updateLog;
  uint32_t i, j, size;
  uint32_t updateStartAddress;
  uint32_t destStartAddress_tmp;
  uint32_t paraStartAddress;
  uint32_t copyLength;
  OSStatus err = kNoErr;
 
  MicoFlashInitialize( (mico_flash_t)MICO_FLASH_FOR_UPDATE );
  memset(data, 0xFF, SizePerRW);
  memset(newData, 0xFF, SizePerRW);
  memset(paraSaveInRam, 0xFF, PARA_FLASH_SIZE);
  
  updateStartAddress = UPDATE_START_ADDRESS;
  
  paraStartAddress = PARA_START_ADDRESS;  
  err = MicoFlashRead(MICO_FLASH_FOR_PARA, &paraStartAddress, (uint8_t *)&updateLog, sizeof(boot_table_t));
  require_noerr(err, exit);

  /*Not a correct record*/
  if(updateLogCheck(&updateLog) != Log_NeedUpdate){
    size = UPDATE_FLASH_SIZE/SizePerRW;
    for(i = 0; i <= size; i++){
      if( i==size ){
        err = MicoFlashRead(MICO_FLASH_FOR_UPDATE, &updateStartAddress, data , UPDATE_FLASH_SIZE%SizePerRW);
        require_noerr(err, exit);
      }
      else{
        err = MicoFlashRead(MICO_FLASH_FOR_UPDATE, &updateStartAddress, data , SizePerRW);
        require_noerr(err, exit);
      }
      
      for(j=0; j<SizePerRW; j++){
        if(data[j] != 0xFF){
          update_log("Update data need to be erased");
          err = MicoFlashInitialize( MICO_FLASH_FOR_UPDATE );
          require_noerr(err, exit);
          err = MicoFlashErase( MICO_FLASH_FOR_UPDATE, UPDATE_START_ADDRESS, UPDATE_END_ADDRESS );
          require_noerr(err, exit);
          err = MicoFlashFinalize( MICO_FLASH_FOR_UPDATE );
          require_noerr(err, exit);
          goto exit;
        }
      }
    }
    goto exit;
  }
  
  update_log("Write OTA data to destination, type:%d, from 0x%08x to 0x%08x, length 0x%x", destFlashType, destStartAddress, destEndAddress, updateLog.length);
  
  destStartAddress_tmp = destStartAddress;
  updateStartAddress = UPDATE_START_ADDRESS;
  
  err = MicoFlashInitialize( destFlashType );
  require_noerr(err, exit);
  err = MicoFlashErase( destFlashType, destStartAddress, destEndAddress );
  require_noerr(err, exit);
  size = (updateLog.length)/SizePerRW;
  
  for(i = 0; i <= size; i++){
    if( i == size ){
      if( (updateLog.length)%SizePerRW )
        copyLength = (updateLog.length)%SizePerRW;
      else
        break;
    }else{
      copyLength = SizePerRW;
    }
    err = MicoFlashRead(MICO_FLASH_FOR_UPDATE, &updateStartAddress, data , copyLength);
    require_noerr(err, exit);
    err = MicoFlashInitialize( destFlashType );
    require_noerr(err, exit);
    err = MicoFlashWrite(destFlashType, &destStartAddress_tmp, data, copyLength);
    require_noerr(err, exit);
    destStartAddress_tmp -= copyLength;
    err = MicoFlashRead(destFlashType, &destStartAddress_tmp, newData , copyLength);
    require_noerr(err, exit);
    err = memcmp(data, newData, copyLength);
    require_noerr_action(err, exit, err = kWriteErr); 
 }  

  update_log("Update start to clear data...");
    
  paraStartAddress = PARA_START_ADDRESS;
  err = MicoFlashRead(MICO_FLASH_FOR_PARA, &paraStartAddress, paraSaveInRam, PARA_FLASH_SIZE);
  require_noerr(err, exit);
  memset(paraSaveInRam, 0xff, sizeof(boot_table_t));
  
  err = MicoFlashErase(MICO_FLASH_FOR_PARA, PARA_START_ADDRESS, PARA_END_ADDRESS);
  require_noerr(err, exit);

  paraStartAddress = PARA_START_ADDRESS;
  err = MicoFlashWrite(MICO_FLASH_FOR_PARA, &paraStartAddress, paraSaveInRam, PARA_FLASH_SIZE);
  require_noerr(err, exit);
  
  err = MicoFlashErase(MICO_FLASH_FOR_UPDATE, UPDATE_START_ADDRESS, UPDATE_END_ADDRESS);
  require_noerr(err, exit);
  update_log("Update success");
  
exit:
  if(err != kNoErr) update_log("Update exit with err = %d", err);
  MicoFlashFinalize(MICO_FLASH_FOR_UPDATE);
  MicoFlashFinalize(destFlashType);
  return err;
}
#endif



