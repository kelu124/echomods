/**
******************************************************************************
* @file    Airkiss.c 
* @author  William Xu
* @version V1.0.0
* @date    05-May-2014
* @brief   This file provide the airkiss function and FTC server for quick 
*          provisioning and first time configuration.
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
#include "MicoWlan.h"
#include "MICONotificationCenter.h"

#include "MicoPlatform.h"
#include "platform.h"
#include "StringUtils.h"
#include "HTTPUtils.h"
#include "SocketUtils.h"

#include "Airkiss.h"

#define airkiss_log(M, ...) custom_log("Airkiss", M, ##__VA_ARGS__)
#define airkiss_log_trace() custom_log_trace("Airkiss")

//#define Airkiss_TimeOut                20000 /**< EasyLink timeout 10 seconds. */
//
//#define Airkiss_ConnectWlan_Timeout    20000 /**< Connect to wlan after configured by easylink.
//                                                   Restart easylink after timeout: 20 seconds. */

static mico_semaphore_t      airkiss_sem;
static uint8_t airkiss_data;

static void airkiss_thread(void *inContext);

static bool AirkissFailed = false;

extern void         ConfigWillStart               ( mico_Context_t * const inContext );
extern void         ConfigWillStop                ( mico_Context_t * const inContext );
extern void         ConfigAirkissIsSuccess       ( mico_Context_t * const inContext );
extern void         ConfigSoftApWillStart         ( mico_Context_t * const inContext );
extern OSStatus     ConfigELRecvAuthData          ( char * userInfo, mico_Context_t * const inContext );
extern OSStatus     MICOStartBonjourService       ( WiFi_Interface interface, mico_Context_t * const inContext );
extern OSStatus     MICOstartConfigServer         ( mico_Context_t * const inContext );

void AirkissNotify_WifiStatusHandler(WiFiEvent event, mico_Context_t * const inContext)
{
  airkiss_log_trace();
  IPStatusTypedef para;

  require(inContext, exit);
  switch (event) {
  case NOTIFY_STATION_UP:
    airkiss_log("Access point connected");
    MicoRfLed(true);
    mico_rtos_set_semaphore(&airkiss_sem);
    micoWlanGetIPStatus(&para, Station);
    strncpy(inContext->flashContentInRam.micoSystemConfig.localIp, para.ip, maxIpLen);
    strncpy(inContext->flashContentInRam.micoSystemConfig.netMask, para.mask, maxIpLen);
    strncpy(inContext->flashContentInRam.micoSystemConfig.gateWay, para.gate, maxIpLen);
    strncpy(inContext->flashContentInRam.micoSystemConfig.dnsServer, para.dns, maxIpLen);
    break;
  case NOTIFY_STATION_DOWN:
    MicoRfLed(false);
    break;
  case NOTIFY_AP_UP:
    MicoRfLed(true);
    break;
  case NOTIFY_AP_DOWN:
    MicoRfLed(false);
    break;
  default:
    break;
  }
exit:
  return;
}

void AirkissNotify_AirkissButtonClickedHandler(mico_Context_t * const inContext)
{
  (void)inContext;
}


void AirkissNotify_WiFIParaChangedHandler(apinfo_adv_t *ap_info, char *key, int key_len, mico_Context_t * const inContext)
{
  airkiss_log_trace();
  require(inContext, exit);
  mico_rtos_lock_mutex(&inContext->flashContentInRam_mutex);
  memcpy(inContext->flashContentInRam.micoSystemConfig.ssid, ap_info->ssid, maxSsidLen);
  memcpy(inContext->flashContentInRam.micoSystemConfig.bssid, ap_info->bssid, 6);
  inContext->flashContentInRam.micoSystemConfig.channel = ap_info->channel;
  inContext->flashContentInRam.micoSystemConfig.security = ap_info->security;
  memcpy(inContext->flashContentInRam.micoSystemConfig.key, key, maxKeyLen);
  inContext->flashContentInRam.micoSystemConfig.keyLength = key_len;
  mico_rtos_unlock_mutex(&inContext->flashContentInRam_mutex);
exit:
  return;
}

void AirkissNotify_DHCPCompleteHandler(IPStatusTypedef *pnet, mico_Context_t * const inContext)
{
  airkiss_log_trace();
  require(inContext, exit);
  strcpy((char *)inContext->micoStatus.localIp, pnet->ip);
  strcpy((char *)inContext->micoStatus.netMask, pnet->mask);
  strcpy((char *)inContext->micoStatus.gateWay, pnet->gate);
  strcpy((char *)inContext->micoStatus.dnsServer, pnet->dns);
exit:
  return;
}

void AirkissNotify_AirkissCompleteHandler(network_InitTypeDef_st *nwkpara, mico_Context_t * const inContext)
{
  OSStatus err;
  airkiss_log_trace();
  airkiss_log("Airkiss return");
  require_action(inContext, exit, err = kParamErr);
  require_action(nwkpara, exit, err = kTimeoutErr);
  
  mico_rtos_lock_mutex(&inContext->flashContentInRam_mutex);
  memcpy(inContext->flashContentInRam.micoSystemConfig.ssid, nwkpara->wifi_ssid, maxSsidLen);
  memset(inContext->flashContentInRam.micoSystemConfig.bssid, 0x0, 6);
  memcpy(inContext->flashContentInRam.micoSystemConfig.user_key, nwkpara->wifi_key, maxKeyLen);
  inContext->flashContentInRam.micoSystemConfig.user_keyLength = strlen(nwkpara->wifi_key);
  inContext->flashContentInRam.micoSystemConfig.dhcpEnable = true;
  mico_rtos_unlock_mutex(&inContext->flashContentInRam_mutex);
  airkiss_log("Get SSID: %s, Key: %s", inContext->flashContentInRam.micoSystemConfig.ssid, inContext->flashContentInRam.micoSystemConfig.user_key);
  return;

/*Airkiss timeout or error*/    
exit:
  airkiss_log("ERROR, err: %d", err);

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

  return;
}

void AirkissNotify_AirkissGetExtraDataHandler(int datalen, char* data, mico_Context_t * const inContext)
{
  OSStatus err;
  airkiss_log_trace();
  require_action(inContext, exit, err = kParamErr);
  char *debugString;

  debugString = DataToHexStringWithSpaces( (const uint8_t *)data, datalen );
  airkiss_log("Get user info: %s", debugString);
  free(debugString);

  airkiss_data = data[0];
  mico_rtos_set_semaphore(&airkiss_sem);
  ConfigAirkissIsSuccess(inContext);

  return;
exit:
  airkiss_log("ERROR, err: %d", err);
  ConfigWillStop(inContext);
  MicoSystemReboot();  
  return;
}

void AirkissNotify_SYSWillPowerOffHandler(mico_Context_t * const inContext)
{
  stopAirkiss(inContext);
}

OSStatus startAirkiss( mico_Context_t * const inContext)
{
  airkiss_log_trace();
  OSStatus err = kUnknownErr;

  err = MICOAddNotification( mico_notify_WIFI_STATUS_CHANGED, (void *)AirkissNotify_WifiStatusHandler );
  require_noerr(err, exit);
  err = MICOAddNotification( mico_notify_WiFI_PARA_CHANGED, (void *)AirkissNotify_WiFIParaChangedHandler );
  require_noerr(err, exit);
  err = MICOAddNotification( mico_notify_EASYLINK_WPS_COMPLETED, (void *)AirkissNotify_AirkissCompleteHandler );
  require_noerr(err, exit);
  err = MICOAddNotification( mico_notify_EASYLINK_GET_EXTRA_DATA, (void *)AirkissNotify_AirkissGetExtraDataHandler );
  require_noerr(err, exit);
  err = MICOAddNotification( mico_notify_DHCP_COMPLETED, (void *)AirkissNotify_DHCPCompleteHandler );
  require_noerr( err, exit );    
  err = MICOAddNotification( mico_notify_SYS_WILL_POWER_OFF, (void *)AirkissNotify_SYSWillPowerOffHandler );
  require_noerr( err, exit ); 
  
  // Start the Airkiss thread
  ConfigWillStart(inContext);
  mico_rtos_init_semaphore(&airkiss_sem, 1);
  err = mico_rtos_create_thread(NULL, MICO_APPLICATION_PRIORITY, "Airkiss", airkiss_thread, 0x1000, (void*)inContext );
  require_noerr_action( err, exit, airkiss_log("ERROR: Unable to start the Airkiss thread.") );

exit:
  return err;
}

void _airkissConnectWiFi( mico_Context_t * const inContext)
{
  airkiss_log_trace();
  network_InitTypeDef_adv_st wNetConfig;
  memset(&wNetConfig, 0x0, sizeof(network_InitTypeDef_adv_st));
  
  mico_rtos_lock_mutex(&inContext->flashContentInRam_mutex);
  strncpy((char*)wNetConfig.ap_info.ssid, inContext->flashContentInRam.micoSystemConfig.ssid, maxSsidLen);
  wNetConfig.ap_info.security = SECURITY_TYPE_AUTO;
  memcpy(wNetConfig.key, inContext->flashContentInRam.micoSystemConfig.user_key, maxKeyLen);
  wNetConfig.key_len = inContext->flashContentInRam.micoSystemConfig.user_keyLength;
  wNetConfig.dhcpMode = inContext->flashContentInRam.micoSystemConfig.dhcpEnable;
  strncpy((char*)wNetConfig.local_ip_addr, inContext->flashContentInRam.micoSystemConfig.localIp, maxIpLen);
  strncpy((char*)wNetConfig.net_mask, inContext->flashContentInRam.micoSystemConfig.netMask, maxIpLen);
  strncpy((char*)wNetConfig.gateway_ip_addr, inContext->flashContentInRam.micoSystemConfig.gateWay, maxIpLen);
  strncpy((char*)wNetConfig.dnsServer_ip_addr, inContext->flashContentInRam.micoSystemConfig.dnsServer, maxIpLen);

  wNetConfig.wifi_retry_interval = 100;
  mico_rtos_unlock_mutex(&inContext->flashContentInRam_mutex);
  micoWlanStartAdv(&wNetConfig);
  airkiss_log("connect to %s.....", wNetConfig.ap_info.ssid);
}

void _airkissConnectWiFi_fast( mico_Context_t * const inContext)
{
  airkiss_log_trace();
  network_InitTypeDef_adv_st wNetConfig;
  memset(&wNetConfig, 0x0, sizeof(network_InitTypeDef_adv_st));

  mico_rtos_lock_mutex(&inContext->flashContentInRam_mutex);
  strncpy((char*)wNetConfig.ap_info.ssid, inContext->flashContentInRam.micoSystemConfig.ssid, maxSsidLen);
  memcpy(wNetConfig.ap_info.bssid, inContext->flashContentInRam.micoSystemConfig.bssid, 6);
  wNetConfig.ap_info.channel = inContext->flashContentInRam.micoSystemConfig.channel;
  wNetConfig.ap_info.security = inContext->flashContentInRam.micoSystemConfig.security;
  memcpy(wNetConfig.key, inContext->flashContentInRam.micoSystemConfig.key, maxKeyLen);
  wNetConfig.key_len = inContext->flashContentInRam.micoSystemConfig.keyLength;
  wNetConfig.dhcpMode = inContext->flashContentInRam.micoSystemConfig.dhcpEnable;
  strncpy((char*)wNetConfig.local_ip_addr, inContext->flashContentInRam.micoSystemConfig.localIp, maxIpLen);
  strncpy((char*)wNetConfig.net_mask, inContext->flashContentInRam.micoSystemConfig.netMask, maxIpLen);
  strncpy((char*)wNetConfig.gateway_ip_addr, inContext->flashContentInRam.micoSystemConfig.gateWay, maxIpLen);
  strncpy((char*)wNetConfig.dnsServer_ip_addr, inContext->flashContentInRam.micoSystemConfig.dnsServer, maxIpLen);

  wNetConfig.wifi_retry_interval = 100;
  mico_rtos_unlock_mutex(&inContext->flashContentInRam_mutex);
  micoWlanStartAdv(&wNetConfig);
  airkiss_log("Connect to %s.....\r\n", wNetConfig.ap_info.ssid);
}

void _cleanAirkissResource( mico_Context_t * const inContext )
{
  (void)inContext;
  /*module should power down under default setting*/ 
  MICORemoveNotification( mico_notify_WIFI_STATUS_CHANGED, (void *)AirkissNotify_WifiStatusHandler );
  MICORemoveNotification( mico_notify_WiFI_PARA_CHANGED, (void *)AirkissNotify_WiFIParaChangedHandler );
  MICORemoveNotification( mico_notify_EASYLINK_WPS_COMPLETED, (void *)AirkissNotify_AirkissCompleteHandler );
  MICORemoveNotification( mico_notify_EASYLINK_GET_EXTRA_DATA, (void *)AirkissNotify_AirkissGetExtraDataHandler );
  MICORemoveNotification( mico_notify_SYS_WILL_POWER_OFF, (void *)AirkissNotify_SYSWillPowerOffHandler );

  mico_rtos_deinit_semaphore(&airkiss_sem);
  airkiss_sem = NULL;
}

OSStatus stopAirkiss( mico_Context_t * const inContext)
{
  (void)inContext;
  micoWlanStopAirkiss();
  return kNoErr;
}

void airkiss_thread(void *inContext)
{
  OSStatus err = kNoErr;
  mico_Context_t *Context = inContext;
  int fd;
  struct sockaddr_t addr;
  int i = 0;
  
  airkiss_log_trace();
  require_action(airkiss_sem, threadexit, err = kNotPreparedErr);
  airkiss_log("Start airkiss");
  
  micoWlanStartAirkiss(Airkiss_TimeOut/1000);
  
  mico_rtos_get_semaphore(&airkiss_sem, MICO_WAIT_FOREVER);
  if(AirkissFailed == false)
    _airkissConnectWiFi(Context);
  

  err = mico_rtos_get_semaphore(&airkiss_sem, Airkiss_ConnectWlan_Timeout);
  require_noerr(err, reboot);

  fd = socket( AF_INET, SOCK_DGRM, IPPROTO_UDP );
  if (fd < 0)
    goto threadexit;
  
  addr.s_ip = INADDR_BROADCAST;
  addr.s_port = 10000;
  airkiss_log("Send UDP to WECHAT");
  while(1){
    sendto(fd, &airkiss_data, 1, 0, &addr, sizeof(addr));
    
    msleep(10);
    i++;
    if (i > 20)
      break;
  }  
  Context->flashContentInRam.micoSystemConfig.configured = allConfigured;
  MICOUpdateConfiguration( Context );
  MicoSystemReboot();
threadexit:
  _cleanAirkissResource( Context );
  ConfigWillStop( Context );
  mico_rtos_delete_thread( NULL );
  return;
  
/*SSID or Password is not correct, module cannot connect to wlan, so reboot and enter Airkiss again*/
reboot:
  MicoSystemReboot();
  return;
}

