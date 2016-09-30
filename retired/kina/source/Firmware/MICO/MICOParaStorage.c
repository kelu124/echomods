/**
******************************************************************************
* @file    MICOParaStorage.c 
* @author  William Xu
* @version V1.0.0
* @date    05-May-2014
* @brief   This file provide functions to read and write MICO settings on 
*          nonvolatile memory.
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

#include "MICODefine.h"
#include "MICO.h"
#include "platform_config.h"
#include "MicoPlatform.h"

/* Update seed number every time*/
static int32_t seedNum = 0;

__weak void appRestoreDefault_callback(mico_Context_t *inContext)
{

}

OSStatus MICORestoreDefault(mico_Context_t *inContext)
{ 
  OSStatus err = kNoErr;
  uint32_t paraStartAddress, paraEndAddress;
 
  paraStartAddress = PARA_START_ADDRESS;
  paraEndAddress = PARA_END_ADDRESS;

  /*wlan configration is not need to change to a default state, use easylink to do that*/
  memset(&inContext->flashContentInRam, 0x0, sizeof(inContext->flashContentInRam));
  sprintf(inContext->flashContentInRam.micoSystemConfig.name, DEFAULT_NAME);
  inContext->flashContentInRam.micoSystemConfig.configured = unConfigured;
  inContext->flashContentInRam.micoSystemConfig.easyLinkByPass = EASYLINK_BYPASS_NO;
  inContext->flashContentInRam.micoSystemConfig.rfPowerSaveEnable = false;
  inContext->flashContentInRam.micoSystemConfig.mcuPowerSaveEnable = false;
  inContext->flashContentInRam.micoSystemConfig.bonjourEnable = true;
  inContext->flashContentInRam.micoSystemConfig.configServerEnable = true;
  inContext->flashContentInRam.micoSystemConfig.seed = seedNum;

  /*Application's default configuration*/
  appRestoreDefault_callback(inContext);

  err = MicoFlashInitialize(MICO_FLASH_FOR_PARA);
  require_noerr(err, exit);
  err = MicoFlashErase(MICO_FLASH_FOR_PARA, paraStartAddress, paraEndAddress);
  require_noerr(err, exit);
  err = MicoFlashWrite(MICO_FLASH_FOR_PARA, &paraStartAddress, (void *)inContext, sizeof(flash_content_t));
  require_noerr(err, exit);
  err = MicoFlashFinalize(MICO_FLASH_FOR_PARA);
  require_noerr(err, exit);

exit:
  return err;
}

#ifdef MFG_MODE_AUTO
OSStatus MICORestoreMFG(mico_Context_t *inContext)
{ 
  OSStatus err = kNoErr;
  uint32_t paraStartAddress, paraEndAddress;
 
  paraStartAddress = PARA_START_ADDRESS;
  paraEndAddress = PARA_END_ADDRESS;

  /*wlan configration is not need to change to a default state, use easylink to do that*/
  sprintf(inContext->flashContentInRam.micoSystemConfig.name, DEFAULT_NAME);
  inContext->flashContentInRam.micoSystemConfig.configured = mfgConfigured;

  /*Application's default configuration*/
  appRestoreDefault_callback(inContext);

  err = MicoFlashInitialize(MICO_FLASH_FOR_PARA);
  require_noerr(err, exit);
  err = MicoFlashErase(MICO_FLASH_FOR_PARA, paraStartAddress, paraEndAddress);
  require_noerr(err, exit);
  err = MicoFlashWrite(MICO_FLASH_FOR_PARA, &paraStartAddress, (void *)inContext, sizeof(flash_content_t));
  require_noerr(err, exit);
  err = MicoFlashFinalize(MICO_FLASH_FOR_PARA);
  require_noerr(err, exit);

exit:
  return err;
}
#endif



OSStatus MICOReadConfiguration(mico_Context_t *inContext)
{
  uint32_t configInFlash;
  OSStatus err = kNoErr;
  configInFlash = PARA_START_ADDRESS;
  err = MicoFlashInitialize(MICO_FLASH_FOR_PARA);
  require_noerr(err, exit);
  err = MicoFlashRead(MICO_FLASH_FOR_PARA, &configInFlash, (uint8_t *)&inContext->flashContentInRam, sizeof(flash_content_t));
  seedNum = inContext->flashContentInRam.micoSystemConfig.seed;
  if(seedNum == -1) seedNum = 0;

  if(inContext->flashContentInRam.appConfig.configDataVer != CONFIGURATION_VERSION){
#ifdef MFG_MODE_AUTO
    err = MICORestoreMFG(inContext);
#else
    err = MICORestoreDefault(inContext);
#endif
    
    require_noerr(err, exit);
  }

  if(inContext->flashContentInRam.micoSystemConfig.dhcpEnable == DHCP_Disable){
    strcpy((char *)inContext->micoStatus.localIp, inContext->flashContentInRam.micoSystemConfig.localIp);
    strcpy((char *)inContext->micoStatus.netMask, inContext->flashContentInRam.micoSystemConfig.netMask);
    strcpy((char *)inContext->micoStatus.gateWay, inContext->flashContentInRam.micoSystemConfig.gateWay);
    strcpy((char *)inContext->micoStatus.dnsServer, inContext->flashContentInRam.micoSystemConfig.dnsServer);
  }

exit: 
  return err;
}

OSStatus MICOUpdateConfiguration(mico_Context_t *inContext)
{
  OSStatus err = kNoErr;
  uint32_t paraStartAddress, paraEndAddress;
 
  paraStartAddress = PARA_START_ADDRESS;
  paraEndAddress = PARA_END_ADDRESS;

  inContext->flashContentInRam.micoSystemConfig.seed = ++seedNum;
  err = MicoFlashInitialize(MICO_FLASH_FOR_PARA);
  require_noerr(err, exit);
  err = MicoFlashErase(MICO_FLASH_FOR_PARA, paraStartAddress, paraEndAddress);
  require_noerr(err, exit);
  err = MicoFlashWrite(MICO_FLASH_FOR_PARA, &paraStartAddress, (uint8_t *)&inContext->flashContentInRam, sizeof(flash_content_t));
  require_noerr(err, exit);
  err = MicoFlashFinalize(MICO_FLASH_FOR_PARA);
  require_noerr(err, exit);

exit:
  return err;
}


