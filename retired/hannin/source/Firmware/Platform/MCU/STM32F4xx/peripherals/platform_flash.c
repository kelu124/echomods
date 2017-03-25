/**
******************************************************************************
* @file    platform_flash.c 
* @author  William Xu
* @version V1.0.0
* @date    05-May-2014
* @brief   This file provides flash operation functions.
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

/* Includes ------------------------------------------------------------------*/
#include "PlatformLogging.h"
#include "MicoPlatform.h"
#include "platform.h"
//#include "platform_config.h"
#include "stdio.h"
#ifdef USE_MICO_SPI_FLASH
#include "spi_flash.h"
#endif

/* Private constants --------------------------------------------------------*/
#define ADDR_FLASH_SECTOR_0     ((uint32_t)0x08000000) /* Base @ of Sector 0, 16 Kbyte */
#define ADDR_FLASH_SECTOR_1     ((uint32_t)0x08004000) /* Base @ of Sector 1, 16 Kbyte */
#define ADDR_FLASH_SECTOR_2     ((uint32_t)0x08008000) /* Base @ of Sector 2, 16 Kbyte */
#define ADDR_FLASH_SECTOR_3     ((uint32_t)0x0800C000) /* Base @ of Sector 3, 16 Kbyte */
#define ADDR_FLASH_SECTOR_4     ((uint32_t)0x08010000) /* Base @ of Sector 4, 64 Kbyte */
#define ADDR_FLASH_SECTOR_5     ((uint32_t)0x08020000) /* Base @ of Sector 5, 128 Kbyte */
#define ADDR_FLASH_SECTOR_6     ((uint32_t)0x08040000) /* Base @ of Sector 6, 128 Kbyte */
#define ADDR_FLASH_SECTOR_7     ((uint32_t)0x08060000) /* Base @ of Sector 7, 128 Kbyte */
#define ADDR_FLASH_SECTOR_8     ((uint32_t)0x08080000) /* Base @ of Sector 8, 128 Kbyte */
#define ADDR_FLASH_SECTOR_9     ((uint32_t)0x080A0000) /* Base @ of Sector 9, 128 Kbyte */
#define ADDR_FLASH_SECTOR_10    ((uint32_t)0x080C0000) /* Base @ of Sector 10, 128 Kbyte */
#define ADDR_FLASH_SECTOR_11    ((uint32_t)0x080E0000) /* Base @ of Sector 11, 128 Kbyte */

/* End of the Flash address */
#define FLASH_START_ADDRESS     (uint32_t)0x08000000  
#define FLASH_END_ADDRESS       (uint32_t)0x080FFFFF
#define FLASH_SIZE              (FLASH_END_ADDRESS -  FLASH_START_ADDRESS + 1)
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
#ifdef USE_MICO_SPI_FLASH
sflash_handle_t sflash_handle = {0x0, 0x0, SFLASH_WRITE_NOT_ALLOWED};
#endif
/* Private function prototypes -----------------------------------------------*/
static uint32_t _GetSector( uint32_t Address );
static OSStatus _GetAddress(uint32_t sector, uint32_t *startAddress, uint32_t *endAddress);
static OSStatus internalFlashInitialize( void );
static OSStatus internalFlashErase(uint32_t StartAddress, uint32_t EndAddress);
static OSStatus internalFlashWrite(volatile uint32_t* FlashAddress, uint32_t* Data ,uint32_t DataLength);
static OSStatus internalFlashByteWrite( volatile uint32_t* FlashAddress, uint8_t* Data ,uint32_t DataLength );
static OSStatus internalFlashFinalize( void );
#ifdef USE_MICO_SPI_FLASH
OSStatus spiFlashErase(uint32_t StartAddress, uint32_t EndAddress);
#endif

// OSStatus MicoFlashInitialize( mico_flash_t flash )
// { 
//   platform_log_trace();
//   if(flash == MICO_INTERNAL_FLASH){
//     return internalFlashInitialize();    
//   }
// #ifdef USE_MICO_SPI_FLASH
//   else if(flash == MICO_SPI_FLASH){
//     if(sflash_handle.device_id)
//       return kNoErr;
//     else
//       return init_sflash( &sflash_handle, 0, SFLASH_WRITE_ALLOWED );
//   }
// #endif
//   else
//     return kUnsupportedErr;
// }

OSStatus platform_flash_init( platform_flash_driver_t *driver, const platform_flash_t *peripheral )
{
  OSStatus err = kNoErr;

  require_action_quiet( driver != NULL && peripheral != NULL, exit, err = kParamErr);
  require_action_quiet( driver->initialized == false, exit, err = kNoErr);

  driver->peripheral = (platform_flash_t *)peripheral;

  if( driver->peripheral->flash_type == FLASH_TYPE_INTERNAL ){
    err = internalFlashInitialize();
    require_noerr(err, exit);
  }
#ifdef USE_MICO_SPI_FLASH
  else if( driver->peripheral->flash_type == FLASH_TYPE_SPI ){
    err = init_sflash( &sflash_handle, 0, SFLASH_WRITE_ALLOWED );
    require_noerr(err, exit);
  }
#endif
  else{
    err = kTypeErr;
    goto exit;
  }

  driver->initialized = true;

exit:
  return err;
}

// OSStatus MicoFlashErase( mico_flash_t flash, uint32_t StartAddress, uint32_t EndAddress )
// { 
//   platform_log_trace();
//   if(flash == MICO_INTERNAL_FLASH){
//     if(StartAddress<INTERNAL_FLASH_START_ADDRESS || EndAddress > INTERNAL_FLASH_END_ADDRESS)
//       return kParamErr;
//     return internalFlashErase(StartAddress, EndAddress);    
//   }
// #ifdef USE_MICO_SPI_FLASH
//   else if(flash == MICO_SPI_FLASH){
//     if(StartAddress>=EndAddress || EndAddress > SPI_FLASH_END_ADDRESS)
//       return kParamErr;
//     return spiFlashErase(StartAddress, EndAddress); 
//   }
// #endif
//   else
//     return kUnsupportedErr;
// }

OSStatus platform_flash_erase( platform_flash_driver_t *driver, uint32_t StartAddress, uint32_t EndAddress  )
{
  OSStatus err = kNoErr;

  require_action_quiet( driver != NULL, exit, err = kParamErr);
  require_action_quiet( driver->initialized != false, exit, err = kNotInitializedErr);
  
  require_action( StartAddress >= driver->peripheral->flash_start_addr 
               && EndAddress   <= driver->peripheral->flash_start_addr + driver->peripheral->flash_length - 1, exit, err = kParamErr);
 
  if( driver->peripheral->flash_type == FLASH_TYPE_INTERNAL ){
    err = internalFlashErase(StartAddress, EndAddress);    
    require_noerr(err, exit);
  }
#ifdef USE_MICO_SPI_FLASH
  else if( driver->peripheral->flash_type == FLASH_TYPE_SPI ){
    err = spiFlashErase(StartAddress, EndAddress);
    require_noerr(err, exit);
  }
#endif
  else{
    err = kTypeErr;
    goto exit;
  }

exit:
  return err;
}



// OSStatus MicoFlashWrite(mico_flash_t flash, volatile uint32_t* FlashAddress, uint8_t* Data ,uint32_t DataLength)
// {
//   if(flash == MICO_INTERNAL_FLASH){
//     if( *FlashAddress<INTERNAL_FLASH_START_ADDRESS || *FlashAddress + DataLength > INTERNAL_FLASH_END_ADDRESS + 1)
//       return kParamErr;
//     return internalFlashWrite(FlashAddress, (uint32_t *)Data, DataLength);    
//   }
// #ifdef USE_MICO_SPI_FLASH
//   else if(flash == MICO_SPI_FLASH){
//     if( *FlashAddress + DataLength > SPI_FLASH_END_ADDRESS + 1)
//       return kParamErr;
//     int returnVal = sflash_write( &sflash_handle, *FlashAddress, Data, DataLength );
//     *FlashAddress += DataLength;
//     return returnVal;
//   }
// #endif
//   else
//     return kUnsupportedErr;
// }


OSStatus platform_flash_write( platform_flash_driver_t *driver, volatile uint32_t* FlashAddress, uint8_t* Data ,uint32_t DataLength  )
{
  OSStatus err = kNoErr;

  require_action_quiet( driver != NULL, exit, err = kParamErr);
  require_action_quiet( driver->initialized != false, exit, err = kNotInitializedErr);
  require_action( *FlashAddress >= driver->peripheral->flash_start_addr 
               && *FlashAddress + DataLength <= driver->peripheral->flash_start_addr + driver->peripheral->flash_length, exit, err = kParamErr);
    
  if( driver->peripheral->flash_type == FLASH_TYPE_INTERNAL ){
    err = internalFlashWrite(FlashAddress, (uint32_t *)Data, DataLength); 
    require_noerr(err, exit);
  }
#ifdef USE_MICO_SPI_FLASH
  else if( driver->peripheral->flash_type == FLASH_TYPE_SPI ){
    err = sflash_write( &sflash_handle, *FlashAddress, Data, DataLength );
    require_noerr(err, exit);
    *FlashAddress += DataLength;
  }
#endif
  else{
    err = kTypeErr;
    goto exit;
  }

exit:
  return err;
}


// OSStatus MicoFlashRead(mico_flash_t flash, volatile uint32_t* FlashAddress, uint8_t* Data ,uint32_t DataLength)
// {
  
//   if(flash == MICO_INTERNAL_FLASH){
//     if( *FlashAddress<INTERNAL_FLASH_START_ADDRESS || *FlashAddress + DataLength > INTERNAL_FLASH_END_ADDRESS + 1)
//       return kParamErr;
//     memcpy(Data, (void *)(*FlashAddress), DataLength);
//     *FlashAddress += DataLength;
//     return kNoErr;
//   }
// #ifdef USE_MICO_SPI_FLASH
//   else if(flash == MICO_SPI_FLASH){
//     if( *FlashAddress + DataLength > SPI_FLASH_END_ADDRESS + 1)
//       return kParamErr;
//     int returnVal = sflash_read( &sflash_handle, *FlashAddress, Data, DataLength );
//     *FlashAddress += DataLength;
//     return returnVal;
//   }
// #endif
//   else
//     return kUnsupportedErr;
// }

OSStatus platform_flash_read( platform_flash_driver_t *driver, volatile uint32_t* FlashAddress, uint8_t* Data ,uint32_t DataLength  )
{
  OSStatus err = kNoErr;

  require_action_quiet( driver != NULL, exit, err = kParamErr);
  require_action_quiet( driver->initialized != false, exit, err = kNotInitializedErr);
  require_action( (*FlashAddress >= driver->peripheral->flash_start_addr) 
               && (*FlashAddress + DataLength) <= (driver->peripheral->flash_start_addr + driver->peripheral->flash_length), exit, err = kParamErr);

  if( driver->peripheral->flash_type == FLASH_TYPE_INTERNAL ){
    memcpy(Data, (void *)(*FlashAddress), DataLength);
    *FlashAddress += DataLength;
  }
#ifdef USE_MICO_SPI_FLASH
  else if( driver->peripheral->flash_type == FLASH_TYPE_SPI ){
    err = sflash_read( &sflash_handle, *FlashAddress, Data, DataLength );
    require_noerr(err, exit);
    *FlashAddress += DataLength;
  }
#endif
  else{
    err = kTypeErr;
    goto exit;
  }

exit:
  return err;
}

// OSStatus MicoFlashFinalize( mico_flash_t flash )
// {
//   if(flash == MICO_INTERNAL_FLASH){
//     return internalFlashFinalize();    
//   }
// #ifdef USE_MICO_SPI_FLASH
//   else if(flash == MICO_SPI_FLASH){
//     sflash_handle.device_id = 0x0;
//     return kNoErr;
//   }
// #endif
//   else
//     return kUnsupportedErr;
// }

OSStatus platform_flash_deinit( platform_flash_driver_t *driver)
{
  OSStatus err = kNoErr;

  require_action_quiet( driver != NULL, exit, err = kParamErr);

  driver->initialized = false;

  if( driver->peripheral->flash_type == FLASH_TYPE_INTERNAL){
    err = internalFlashFinalize();   
    require_noerr(err, exit); 
  }
#ifdef USE_MICO_SPI_FLASH
  else if( driver->peripheral->flash_type == FLASH_TYPE_SPI ){
    sflash_handle.device_id = 0x0;
  }
#endif
  else{
    err = kTypeErr;
    goto exit;
  }
  
exit:
  return err;
}

OSStatus internalFlashInitialize( void )
{ 
  platform_log_trace();
  FLASH_Unlock(); 
  /* Clear pending flags (if any) */
  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | 
                  FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR);
  return kNoErr;    
}

OSStatus internalFlashErase(uint32_t StartAddress, uint32_t EndAddress)
{
  platform_log_trace();
  OSStatus err = kNoErr;
  uint32_t StartSector, EndSector, i = 0, j = 0;
  
  /* Get the sector where start the user flash area */
  StartSector = _GetSector(StartAddress);
  EndSector = _GetSector(EndAddress);
  
  for(i = StartSector; i <= EndSector; i += 8)
  {
    /* Device voltage range supposed to be [2.7V to 3.6V], the operation will
    be done by word */
    _GetAddress(i, &StartAddress, &EndAddress);
    for(j=StartAddress; j<=EndAddress; j+=8){
      if( (*(uint32_t *)(j))!=0xFFFFFFFF )
        break;
    }
    if( j>EndAddress ) 
      continue;
    require_action(FLASH_EraseSector(i, VoltageRange_3) == FLASH_COMPLETE, exit, err = kWriteErr); 
  }
  
exit:
  return err;
}

#ifdef USE_MICO_SPI_FLASH
OSStatus spiFlashErase(uint32_t StartAddress, uint32_t EndAddress)
{
  platform_log_trace();
  OSStatus err = kNoErr;
  uint32_t StartSector, EndSector, i = 0;
  
  /* Get the sector where start the user flash area */
  StartSector = StartAddress>>12;
  EndSector = EndAddress>>12;
  
  for(i = StartSector; i <= EndSector; i += 1)
  {
    /* Device voltage range supposed to be [2.7V to 3.6V], the operation will
    be done by word */
    require_action(sflash_sector_erase(&sflash_handle, i<<12) == kNoErr, exit, err = kWriteErr); 
  }
  
exit:
  return err;
}
#endif


OSStatus internalFlashWrite(volatile uint32_t* FlashAddress, uint32_t* Data ,uint32_t DataLength)
{
  platform_log_trace();
  OSStatus err = kNoErr;
  uint32_t i = 0;
  uint32_t dataInRam;
  uint8_t startNumber;
  uint32_t DataLength32 = DataLength;
  
  /*First bytes that are not 32bit align*/
  if(*FlashAddress%4){
    startNumber = 4-(*FlashAddress)%4;
    err = internalFlashByteWrite(FlashAddress, (uint8_t *)Data, startNumber);
    require_noerr(err, exit);
    DataLength32 = DataLength - startNumber;
    Data = (uint32_t *)((uint32_t)Data + startNumber);
  }
  
  /*Program flash by words*/
  for (i = 0; (i < DataLength32/4) && (*FlashAddress <= (FLASH_END_ADDRESS-3)); i++)
  {
    /* Device voltage range supposed to be [2.7V to 3.6V], the operation will
    be done by word */ 
    dataInRam = *(Data+i);
    require_action(FLASH_ProgramWord(*FlashAddress, dataInRam) == FLASH_COMPLETE, exit, err = kWriteErr); 
    require_action(*(uint32_t*)*FlashAddress == dataInRam, exit, err = kChecksumErr); 
    /* Increment FLASH destination address */
    *FlashAddress += 4;
  }
  
  /*Last bytes that cannot be write by a 32 bit word*/
  err = internalFlashByteWrite(FlashAddress, (uint8_t *)Data + i*4, DataLength32-i*4);
  require_noerr(err, exit);
  
exit:
  return err;
}

OSStatus internalFlashFinalize( void )
{
  FLASH_Lock();
  return kNoErr;
}


OSStatus internalFlashByteWrite(__IO uint32_t* FlashAddress, uint8_t* Data ,uint32_t DataLength)
{
  uint32_t i = 0;
  uint32_t dataInRam;
  OSStatus err = kNoErr;
  
  for (i = 0; (i < DataLength) && (*FlashAddress <= (FLASH_END_ADDRESS)); i++)
  {
    /* Device voltage range supposed to be [2.7V to 3.6V], the operation will
    be done by word */ 
    dataInRam = *(uint8_t*)(Data+i);
    
    require_action(FLASH_ProgramByte(*FlashAddress, dataInRam) == FLASH_COMPLETE, exit, err = kWriteErr); 
    require_action(*(uint8_t*)*FlashAddress == dataInRam, exit, err = kChecksumErr); 
    *FlashAddress +=1;
  }
  
exit:
  return err;
}

/**
* @brief  Gets the sector of a given address
* @param  Address: Flash address
* @retval The sector of a given address
*/
static uint32_t _GetSector(uint32_t Address)
{
  uint32_t sector = 0;
  
  if((Address < ADDR_FLASH_SECTOR_1) && (Address >= ADDR_FLASH_SECTOR_0))
  {
    sector = FLASH_Sector_0;  
  }
  else if((Address < ADDR_FLASH_SECTOR_2) && (Address >= ADDR_FLASH_SECTOR_1))
  {
    sector = FLASH_Sector_1;  
  }
  else if((Address < ADDR_FLASH_SECTOR_3) && (Address >= ADDR_FLASH_SECTOR_2))
  {
    sector = FLASH_Sector_2;  
  }
  else if((Address < ADDR_FLASH_SECTOR_4) && (Address >= ADDR_FLASH_SECTOR_3))
  {
    sector = FLASH_Sector_3;  
  }
  else if((Address < ADDR_FLASH_SECTOR_5) && (Address >= ADDR_FLASH_SECTOR_4))
  {
    sector = FLASH_Sector_4;  
  }
  else if((Address < ADDR_FLASH_SECTOR_6) && (Address >= ADDR_FLASH_SECTOR_5))
  {
    sector = FLASH_Sector_5;  
  }
  else if((Address < ADDR_FLASH_SECTOR_7) && (Address >= ADDR_FLASH_SECTOR_6))
  {
    sector = FLASH_Sector_6;  
  }
  else if((Address < ADDR_FLASH_SECTOR_8) && (Address >= ADDR_FLASH_SECTOR_7))
  {
    sector = FLASH_Sector_7;  
  }
  else if((Address < ADDR_FLASH_SECTOR_9) && (Address >= ADDR_FLASH_SECTOR_8))
  {
    sector = FLASH_Sector_8;  
  }
  else if((Address < ADDR_FLASH_SECTOR_10) && (Address >= ADDR_FLASH_SECTOR_9))
  {
    sector = FLASH_Sector_9;  
  }
  else if((Address < ADDR_FLASH_SECTOR_11) && (Address >= ADDR_FLASH_SECTOR_10))
  {
    sector = FLASH_Sector_10;  
  }
  else/*(Address < FLASH_END_ADDR) && (Address >= ADDR_FLASH_SECTOR_11))*/
  {
    sector = FLASH_Sector_11;  
  }
  return sector;
}


/**
* @brief  Gets the address of a given sector
* @param  Sector: The sector of a given address
* @retval Flash address if the sector start
*/
static OSStatus _GetAddress(uint32_t sector, uint32_t *startAddress, uint32_t *endAddress)
{
  OSStatus err = kNoErr; 
  if(sector == FLASH_Sector_0)
  {
    *startAddress = ADDR_FLASH_SECTOR_0;
    *endAddress = ADDR_FLASH_SECTOR_1 - 1;
  }
  else if(sector == FLASH_Sector_1)
  {
    *startAddress = ADDR_FLASH_SECTOR_1;
    *endAddress = ADDR_FLASH_SECTOR_2 - 1;
  }
  else if(sector == FLASH_Sector_2)
  {
    *startAddress = ADDR_FLASH_SECTOR_2;
    *endAddress = ADDR_FLASH_SECTOR_3 - 1;
  }
  else if(sector == FLASH_Sector_3)
  {
    *startAddress = ADDR_FLASH_SECTOR_3;
    *endAddress = ADDR_FLASH_SECTOR_4 - 1;
  }
  else if(sector == FLASH_Sector_4)
  {
    *startAddress = ADDR_FLASH_SECTOR_4;
    *endAddress = ADDR_FLASH_SECTOR_5 - 1;
  }
  else if(sector == FLASH_Sector_5)
  {
    *startAddress = ADDR_FLASH_SECTOR_5;
    *endAddress = ADDR_FLASH_SECTOR_6 - 1;
  }
  else if(sector == FLASH_Sector_6)
  {
    *startAddress = ADDR_FLASH_SECTOR_6;
    *endAddress = ADDR_FLASH_SECTOR_7 - 1;
  }
  else if(sector == FLASH_Sector_7)
  {
    *startAddress = ADDR_FLASH_SECTOR_7;
    *endAddress = ADDR_FLASH_SECTOR_8 - 1;
  }
  else if(sector == FLASH_Sector_8)
  {
    *startAddress = ADDR_FLASH_SECTOR_8;
    *endAddress = ADDR_FLASH_SECTOR_9 - 1;
  }
  else if(sector == FLASH_Sector_9)
  {
    *startAddress = ADDR_FLASH_SECTOR_9;
    *endAddress = ADDR_FLASH_SECTOR_10 - 1;
  }
  else if(sector == FLASH_Sector_10)
  {
    *startAddress = ADDR_FLASH_SECTOR_10;
    *endAddress = ADDR_FLASH_SECTOR_11 - 1;
  }
  else if(sector == FLASH_Sector_11)
  {
    *startAddress = ADDR_FLASH_SECTOR_11;
    *endAddress = FLASH_END_ADDRESS - 1;
  }
  else
    err = kNotFoundErr;
  
  return err;
}

