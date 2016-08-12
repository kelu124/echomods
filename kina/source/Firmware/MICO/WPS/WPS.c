/**
******************************************************************************
* @file    wps.c 
* @author  William Xu
* @version V1.0.0
* @date    05-May-2014
* @brief   This file provide functions for start a WPS (Wi-Fi protected set-up) 
*          function thread.
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

#include "MICO.h"
#include "MICONotificationCenter.h"

#include "MicoPlatform.h"
#include "StringUtils.h"
#include "HTTPUtils.h"

#include "WPS.h"
#include "SoftAp/EasyLinkSoftAP.h"

#define wps_log(M, ...) custom_log("WPS", M, ##__VA_ARGS__)
#define wps_log_trace() custom_log_trace("WPS")

static mico_semaphore_t  wps_sem = NULL;

static void wps_thread(void *inContext);

extern void       ConfigWillStart           ( mico_Context_t * const inContext );
extern void       ConfigWillStop            ( mico_Context_t * const inContext );
extern void       ConfigSoftApWillStart     ( mico_Context_t * const inContext );
extern OSStatus   MICOStartBonjourService   ( WiFi_Interface interface, mico_Context_t * const inContext );


void WPSNotify_WPSCompleteHandler(network_InitTypeDef_st *nwkpara, mico_Context_t * const inContext)
{
  OSStatus err;
  wps_log_trace();
  require_action(inContext, exit, err = kParamErr);
  require_action(nwkpara, exit, err = kTimeoutErr);
  
  mico_rtos_lock_mutex(&inContext->flashContentInRam_mutex);
  memcpy(inContext->flashContentInRam.micoSystemConfig.ssid, nwkpara->wifi_ssid, maxSsidLen);
  inContext->flashContentInRam.micoSystemConfig.channel = 0;
  inContext->flashContentInRam.micoSystemConfig.security = SECURITY_TYPE_AUTO;
  memcpy(inContext->flashContentInRam.micoSystemConfig.user_key, nwkpara->wifi_key, maxKeyLen);
  inContext->flashContentInRam.micoSystemConfig.user_keyLength = strlen(nwkpara->wifi_key);
  memcpy(inContext->flashContentInRam.micoSystemConfig.key, nwkpara->wifi_key, maxKeyLen);
  inContext->flashContentInRam.micoSystemConfig.keyLength = strlen(nwkpara->wifi_key);
  inContext->flashContentInRam.micoSystemConfig.configured = allConfigured;
  MICOUpdateConfiguration(inContext);
  mico_rtos_unlock_mutex(&inContext->flashContentInRam_mutex);
  wps_log("Get SSID: %s, Key: %s", inContext->flashContentInRam.micoSystemConfig.ssid, inContext->flashContentInRam.micoSystemConfig.user_key);
  ConfigWillStop(inContext);
  MicoSystemReboot();
  return;

/*WPS timeout*/    
exit:
  wps_log("ERROR, err: %d", err);
#if ( MICO_CONFIG_MODE == CONFIG_MODE_WPS_WITH_SOFTAP)
  mico_rtos_set_semaphore(&wps_sem);
#else
  ConfigWillStop(inContext);
  /*so roll back to previous settings  (if it has) and reboot*/
  mico_rtos_lock_mutex(&inContext->flashContentInRam_mutex);
  if(inContext->flashContentInRam.micoSystemConfig.configured != unConfigured){
    inContext->flashContentInRam.micoSystemConfig.configured = allConfigured;
    MICOUpdateConfiguration(inContext);
    MicoSystemReboot();
  }
  mico_rtos_unlock_mutex(&inContext->flashContentInRam_mutex);
  /*module should powd down in default setting*/ 
  micoWlanPowerOff();
#endif
  return;
}

void WPSNotify_SYSWillPowerOffHandler(mico_Context_t * const inContext)
{
  stopWPS(inContext);
}

OSStatus startWPS( mico_Context_t * const inContext)
{
  wps_log_trace();
  OSStatus err = kUnknownErr;

  err = MICOAddNotification( mico_notify_EASYLINK_WPS_COMPLETED, (void *)WPSNotify_WPSCompleteHandler );
  require_noerr(err, exit);
  err = MICOAddNotification( mico_notify_SYS_WILL_POWER_OFF, (void *)WPSNotify_SYSWillPowerOffHandler );
  require_noerr( err, exit ); 

  // Start the WPS thread
  ConfigWillStart(inContext);
  mico_rtos_init_semaphore(&wps_sem, 1);
  err = mico_rtos_create_thread(NULL, MICO_APPLICATION_PRIORITY, "WPS", wps_thread, 0x1000, (void*)inContext );
  require_noerr_string( err, exit, "ERROR: Unable to start the WPS thread." );

exit:
  return err;
}


void _wpsStartSoftAp( mico_Context_t * const inContext)
{
  startEasyLinkSoftAP( inContext);
}


OSStatus stopWPS( mico_Context_t * const inContext)
{
  (void)inContext;

  MICORemoveNotification( mico_notify_EASYLINK_WPS_COMPLETED, (void *)WPSNotify_WPSCompleteHandler );
  MICORemoveNotification( mico_notify_SYS_WILL_POWER_OFF, (void *)WPSNotify_SYSWillPowerOffHandler );

  if(wps_sem){
    mico_rtos_deinit_semaphore(&wps_sem);
    wps_sem = NULL;
  }

  micoWlanStopWPS();
  return kNoErr;
}

void wps_thread(void *inContext)
{
  
  wps_log_trace();
  OSStatus err = kNoErr;
  mico_Context_t *Context = inContext;

  require_action(wps_sem, exit, err = kNotPreparedErr);

  micoWlanStartWPS(WPS_TimeOut/1000); 
  wps_log("Start WPS configuration");
  mico_rtos_get_semaphore(&wps_sem, MICO_WAIT_FOREVER);

  /* If WPS is failed and needs to start soft ap mode */
  msleep(20);
  _wpsStartSoftAp(Context);

exit:
  if(err) wps_log("WPS thread exit, err = %d", err);
  stopWPS(Context);
  mico_rtos_delete_thread(NULL);
    
  return;

}



