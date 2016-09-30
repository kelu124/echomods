/**
******************************************************************************
* @file    EasyLink.c 
* @author  William Xu
* @version V1.0.0
* @date    05-May-2014
* @brief   This file provide the easylink function and FTC server for quick 
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
#include "MICONotificationCenter.h"

#include "MicoPlatform.h"
#include "StringUtils.h"
#include "HTTPUtils.h"
#include "SocketUtils.h"

#include "EasyLink.h"
#include "SoftAp/EasyLinkSoftAP.h"
  
// EasyLink HTTP messages
#define kEasyLinkURLAuth          "/auth-setup"

#define easylink_log(M, ...) custom_log("EasyLink", M, ##__VA_ARGS__)
#define easylink_log_trace() custom_log_trace("EasyLink")

static mico_semaphore_t      easylink_sem;
static mico_semaphore_t      config_finished_sem;
static int                   easylinkClient_fd;
static bool                  easylink_thread_should_exit = false;
static bool                  easylink_softap_should_start = false;
static bool                  easylink_wlan_should_close = false;

static void easylink_thread(void *inContext);

static OSStatus _FTCRespondInComingMessage(int fd, HTTPHeader_t* inHeader, mico_Context_t * const inContext);

static uint8_t *httpResponse = NULL;
static HTTPHeader_t *httpHeader = NULL;

extern OSStatus     ConfigIncommingJsonMessage    ( const char *input, mico_Context_t * const inContext );
extern json_object* ConfigCreateReportJsonMessage ( mico_Context_t * const inContext );
extern void         ConfigWillStart               ( mico_Context_t * const inContext );
extern void         ConfigWillStop                ( mico_Context_t * const inContext );
extern void         ConfigEasyLinkIsSuccess       ( mico_Context_t * const inContext );
extern void         ConfigSoftApWillStart         ( mico_Context_t * const inContext );
extern OSStatus     ConfigELRecvAuthData          ( char * userInfo, mico_Context_t * const inContext );
extern OSStatus     MICOStartBonjourService       ( WiFi_Interface interface, mico_Context_t * const inContext );
extern OSStatus     MICOstartConfigServer         ( mico_Context_t * const inContext );

void EasyLinkNotify_WifiStatusHandler(WiFiEvent event, mico_Context_t * const inContext)
{
  easylink_log_trace();
  IPStatusTypedef para;

  require(inContext, exit);
  switch (event) {
  case NOTIFY_STATION_UP:
    mico_rtos_set_semaphore(&easylink_sem);
    micoWlanGetIPStatus(&para, Station);
    strncpy(inContext->flashContentInRam.micoSystemConfig.localIp, para.ip, maxIpLen);
    strncpy(inContext->flashContentInRam.micoSystemConfig.netMask, para.mask, maxIpLen);
    strncpy(inContext->flashContentInRam.micoSystemConfig.gateWay, para.gate, maxIpLen);
    strncpy(inContext->flashContentInRam.micoSystemConfig.dnsServer, para.dns, maxIpLen);
    break;
  default:
    break;
  }
exit:
  return;
}

void EasyLinkNotify_EasyLinkButtonClickedHandler(mico_Context_t * const inContext)
{
  (void)inContext;
}


void EasyLinkNotify_WiFIParaChangedHandler(apinfo_adv_t *ap_info, char *key, int key_len, mico_Context_t * const inContext)
{
  easylink_log_trace();
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

void EasyLinkNotify_DHCPCompleteHandler(IPStatusTypedef *pnet, mico_Context_t * const inContext)
{
  easylink_log_trace();
  require(inContext, exit);
  strcpy((char *)inContext->micoStatus.localIp, pnet->ip);
  strcpy((char *)inContext->micoStatus.netMask, pnet->mask);
  strcpy((char *)inContext->micoStatus.gateWay, pnet->gate);
  strcpy((char *)inContext->micoStatus.dnsServer, pnet->dns);
exit:
  return;
}

void EasyLinkNotify_EasyLinkCompleteHandler(network_InitTypeDef_st *nwkpara, mico_Context_t * const inContext)
{
  OSStatus err;
  easylink_log_trace();
  easylink_log("EasyLink return");
  require_action(inContext, exit, err = kParamErr);
  require_action(nwkpara, exit, err = kTimeoutErr);
  
  mico_rtos_lock_mutex(&inContext->flashContentInRam_mutex);
  memcpy(inContext->flashContentInRam.micoSystemConfig.ssid, nwkpara->wifi_ssid, maxSsidLen);
  memset(inContext->flashContentInRam.micoSystemConfig.bssid, 0x0, 6);
  memcpy(inContext->flashContentInRam.micoSystemConfig.user_key, nwkpara->wifi_key, maxKeyLen);
  inContext->flashContentInRam.micoSystemConfig.user_keyLength = strlen(nwkpara->wifi_key);
  mico_rtos_unlock_mutex(&inContext->flashContentInRam_mutex);
  easylink_log("Get SSID: %s, Key: %s", inContext->flashContentInRam.micoSystemConfig.ssid, inContext->flashContentInRam.micoSystemConfig.user_key);
  return;

/*EasyLink timeout or error*/    
exit:
  easylink_log("ERROR, err: %d", err);
#if ( MICO_CONFIG_MODE == CONFIG_MODE_EASYLINK_WITH_SOFTAP)
  easylink_softap_should_start = true;
#else
  /*so roll back to previous settings  (if it has) and connect*/
  if(inContext->flashContentInRam.micoSystemConfig.configured != unConfigured){
    inContext->flashContentInRam.micoSystemConfig.configured = allConfigured;
    MICOUpdateConfiguration(inContext);
  }else{
    /*module should pow down in default setting*/
    easylink_wlan_should_close = true;
    micoWlanPowerOff();
  }
#endif
  easylink_thread_should_exit = true;
  mico_rtos_set_semaphore(&easylink_sem);

  return;
}

// Data = AuthData#FTCServer(localIp/netMask/gateWay/dnsServer)
void EasyLinkNotify_EasyLinkGetExtraDataHandler(int datalen, char* data, mico_Context_t * const inContext)
{
  OSStatus err;
  int index ;
  char address[16];
  easylink_log_trace();
  uint32_t *ipInfo, ipInfoCount;
  require_action(inContext, exit, err = kParamErr);
  char *debugString;

  debugString = DataToHexStringWithSpaces( (const uint8_t *)data, datalen );
  easylink_log("Get user info: %s", debugString);
  free(debugString);

  for(index = datalen - 1; index>=0; index-- ){
    if(data[index] == '#' &&( (datalen - index) == 5 || (datalen - index) == 25 ) )
      break;
  }
  require_action(index >= 0, exit, err = kParamErr);

  data[index++] = 0x0;
  ipInfo = (uint32_t *)&data[index];
  ipInfoCount = (datalen - index)/sizeof(uint32_t);
  require_action(ipInfoCount >= 1, exit, err = kParamErr);
  mico_rtos_lock_mutex(&inContext->flashContentInRam_mutex);
  inContext->flashContentInRam.micoSystemConfig.easylinkServerIP = *(uint32_t *)(ipInfo);
  
  if(ipInfoCount == 1){
    inContext->flashContentInRam.micoSystemConfig.dhcpEnable = true;
    inet_ntoa( address, inContext->flashContentInRam.micoSystemConfig.easylinkServerIP);
    easylink_log("Get auth info: %s, EasyLink server ip address: %s", data, address);
  }else{
    inContext->flashContentInRam.micoSystemConfig.dhcpEnable = false;
    ipInfo = (uint32_t *)&data[index];
    inet_ntoa(inContext->flashContentInRam.micoSystemConfig.localIp, *(uint32_t *)(ipInfo+1));
    inet_ntoa(inContext->flashContentInRam.micoSystemConfig.netMask, *(uint32_t *)(ipInfo+2));
    inet_ntoa(inContext->flashContentInRam.micoSystemConfig.gateWay, *(uint32_t *)(ipInfo+3));
    inet_ntoa(inContext->flashContentInRam.micoSystemConfig.dnsServer, *(uint32_t *)(ipInfo+4));
    strcpy((char *)inContext->micoStatus.localIp, inContext->flashContentInRam.micoSystemConfig.localIp);
    strcpy((char *)inContext->micoStatus.netMask, inContext->flashContentInRam.micoSystemConfig.netMask);
    strcpy((char *)inContext->micoStatus.gateWay, inContext->flashContentInRam.micoSystemConfig.gateWay);
    strcpy((char *)inContext->micoStatus.dnsServer, inContext->flashContentInRam.micoSystemConfig.dnsServer);
    inet_ntoa( address, inContext->flashContentInRam.micoSystemConfig.easylinkServerIP);
    easylink_log("Get auth info: %s, EasyLink server ip address: %s, local IP info:%s %s %s %s ", data, address, inContext->flashContentInRam.micoSystemConfig.localIp,\
    inContext->flashContentInRam.micoSystemConfig.netMask, inContext->flashContentInRam.micoSystemConfig.gateWay,inContext->flashContentInRam.micoSystemConfig.dnsServer);
  }
  mico_rtos_unlock_mutex(&inContext->flashContentInRam_mutex);

  require_noerr(ConfigELRecvAuthData(data, inContext), exit);
  
  easylink_softap_should_start = false;
  mico_rtos_set_semaphore(&easylink_sem);
  ConfigEasyLinkIsSuccess(inContext);
  return;

exit:
  easylink_log("ERROR, err: %d", err);
  ConfigWillStop(inContext);
  MicoSystemReboot();
}

OSStatus startEasyLink( mico_Context_t * const inContext)
{
  easylink_log_trace();
  OSStatus err = kUnknownErr;
  easylinkClient_fd = -1;

  err = MICOAddNotification( mico_notify_WIFI_STATUS_CHANGED, (void *)EasyLinkNotify_WifiStatusHandler );
  require_noerr(err, exit);
  err = MICOAddNotification( mico_notify_WiFI_PARA_CHANGED, (void *)EasyLinkNotify_WiFIParaChangedHandler );
  require_noerr(err, exit);
  err = MICOAddNotification( mico_notify_EASYLINK_WPS_COMPLETED, (void *)EasyLinkNotify_EasyLinkCompleteHandler );
  require_noerr(err, exit);
  err = MICOAddNotification( mico_notify_EASYLINK_GET_EXTRA_DATA, (void *)EasyLinkNotify_EasyLinkGetExtraDataHandler );
  require_noerr(err, exit);
  err = MICOAddNotification( mico_notify_DHCP_COMPLETED, (void *)EasyLinkNotify_DHCPCompleteHandler );
  require_noerr( err, exit );    
  
  // Start the EasyLink thread
  ConfigWillStart(inContext);
  mico_rtos_init_semaphore(&easylink_sem, 1);
  mico_rtos_init_semaphore(&config_finished_sem, 1);

  err = mico_rtos_create_thread(NULL, MICO_APPLICATION_PRIORITY, "EASYLINK", easylink_thread, 0x1000, (void*)inContext );
  require_noerr_action( err, exit, easylink_log("ERROR: Unable to start the EasyLink thread.") );

  mico_rtos_get_semaphore( &config_finished_sem, MICO_WAIT_FOREVER ); 
  mico_rtos_deinit_semaphore( &config_finished_sem );

  if(easylink_softap_should_start == true){
      /* EasyLink  failed, start soft ap configuration */
      mico_thread_msleep(20);
      startEasyLinkSoftAP( inContext );
  }

exit:
  return err;
}

void connect_wifi_normal( mico_Context_t * const inContext)
{
  easylink_log_trace();
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
  easylink_log("connect to %s.....", wNetConfig.ap_info.ssid);
}

void connect_wifi_fast( mico_Context_t * const inContext)
{
  easylink_log_trace();
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
  easylink_log("Connect to %s.....\r\n", wNetConfig.ap_info.ssid);
}

OSStatus _connectFTCServer( mico_Context_t * const inContext, int *fd)
{
  OSStatus    err;
  struct      sockaddr_t addr;
  json_object *easylink_report = NULL;
  const char  *json_str;
  char host[16] = {0};
  
  size_t      httpResponseLen = 0;

  *fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  addr.s_ip = inContext->flashContentInRam.micoSystemConfig.easylinkServerIP; 
  addr.s_port = FTC_PORT;  
  err = connect(*fd, &addr, sizeof(addr));
  require_noerr(err, exit);

  easylink_log("Connect to FTC server success, fd: %d", *fd);

  easylink_report = ConfigCreateReportJsonMessage( inContext );
  require( easylink_report, exit );

  json_str = json_object_to_json_string(easylink_report);
  require( json_str, exit );

  inet_ntoa( host, inContext->flashContentInRam.micoSystemConfig.easylinkServerIP);
  easylink_log("Send config object=%s", json_str);
  //err =  CreateHTTPMessage( "POST", kEasyLinkURLAuth, kMIMEType_JSON, (uint8_t *)json_str, strlen(json_str), &httpResponse, &httpResponseLen );
  err =  CreateHTTPMessageWithHost( "POST", kEasyLinkURLAuth, host, addr.s_port, kMIMEType_JSON, (uint8_t *)json_str, strlen(json_str), &httpResponse, &httpResponseLen );
  require_noerr( err, exit );
  require( httpResponse, exit );

  json_object_put(easylink_report);

  err = SocketSend( *fd, httpResponse, httpResponseLen );
  free(httpResponse);
  require_noerr( err, exit );
  easylink_log("Current configuration sent");

exit:
  return err;
}


void _cleanEasyLinkResource( mico_Context_t * const inContext )
{
  (void)inContext;
  if(easylinkClient_fd != -1)
    SocketClose(&easylinkClient_fd);

  if(httpHeader != NULL)
    free( httpHeader );

  /*module should power down under default setting*/ 
  MICORemoveNotification( mico_notify_WIFI_STATUS_CHANGED, (void *)EasyLinkNotify_WifiStatusHandler );
  MICORemoveNotification( mico_notify_WiFI_PARA_CHANGED, (void *)EasyLinkNotify_WiFIParaChangedHandler );
  MICORemoveNotification( mico_notify_EASYLINK_WPS_COMPLETED, (void *)EasyLinkNotify_EasyLinkCompleteHandler );
  MICORemoveNotification( mico_notify_EASYLINK_GET_EXTRA_DATA, (void *)EasyLinkNotify_EasyLinkGetExtraDataHandler );
  MICORemoveNotification( mico_notify_DHCP_COMPLETED, (void *)EasyLinkNotify_DHCPCompleteHandler );

  mico_rtos_deinit_semaphore(&easylink_sem);
  easylink_sem = NULL;
}

OSStatus stopEasyLink( mico_Context_t * const inContext)
{
  (void)inContext;
  micoWlanStopEasyLink();
   if(easylinkClient_fd != -1)
    SocketClose(&easylinkClient_fd);
  return kNoErr;
}

void easylink_thread(void *inContext)
{
  OSStatus err = kNoErr;
  mico_Context_t *Context = inContext;
  fd_set readfds;
  int reConnCount = 0;
  int clientFdIsSet;

  easylink_log_trace();
  require_action(easylink_sem, threadexit, err = kNotPreparedErr);
      
  if(Context->flashContentInRam.micoSystemConfig.easyLinkByPass == EASYLINK_BYPASS){
    Context->flashContentInRam.micoSystemConfig.easyLinkByPass = EASYLINK_BYPASS_NO;
    MICOUpdateConfiguration(Context);
    connect_wifi_fast(Context);
  }else if(Context->flashContentInRam.micoSystemConfig.easyLinkByPass == EASYLINK_SOFT_AP_BYPASS){
    ConfigWillStop( Context );
    startEasyLinkSoftAP( Context );
    mico_rtos_delete_thread(NULL);
    return;
  }else{
#ifdef EasyLink_Plus
    easylink_log("Start easylink plus mode");
    micoWlanStartEasyLinkPlus(EasyLink_TimeOut/1000);
#else
    easylink_log("Start easylink V2");
    micoWlanStartEasyLink(EasyLink_TimeOut/1000);
#endif 
    mico_rtos_get_semaphore(&easylink_sem, MICO_WAIT_FOREVER);
    /* EasyLink  success or failed and roll back to previous settings, connect new wlan */
    if(easylink_softap_should_start == false && easylink_wlan_should_close == false ){
      connect_wifi_normal( Context );
    }
    if( easylink_thread_should_exit == true )
        goto threadexit;
  }

  err = mico_rtos_get_semaphore(&easylink_sem, EasyLink_ConnectWlan_Timeout);
  require_noerr(err, reboot);
  
  httpHeader = HTTPHeaderCreate();
  require_action( httpHeader, threadexit, err = kNoMemoryErr );
  HTTPHeaderClear( httpHeader );
    
  while(1){
    if(easylinkClient_fd == -1){
      err = _connectFTCServer(inContext, &easylinkClient_fd);
      require_noerr(err, Reconn);
    }else{
      FD_ZERO(&readfds);  
      FD_SET(easylinkClient_fd, &readfds);

      if(httpHeader->len == 0){
        err = select(1, &readfds, NULL, NULL, NULL);
        require(err>=1, threadexit);
        clientFdIsSet = FD_ISSET(easylinkClient_fd, &readfds);
      }
  
      if(clientFdIsSet||httpHeader->len){
        err = SocketReadHTTPHeader( easylinkClient_fd, httpHeader );

        switch ( err )
        {
          case kNoErr:
            // Read the rest of the HTTP body if necessary
              err = SocketReadHTTPBody( easylinkClient_fd, httpHeader );
              require_noerr(err, Reconn);

              PrintHTTPHeader(httpHeader);
              // Call the HTTPServer owner back with the acquired HTTP header
              err = _FTCRespondInComingMessage( easylinkClient_fd, httpHeader, Context );
              require_noerr( err, Reconn );
              // Reuse HTTPHeader
              HTTPHeaderClear( httpHeader );
              if( easylink_thread_should_exit == true ){
                goto threadexit;
              }

          break;

          case EWOULDBLOCK:
              // NO-OP, keep reading
          break;

          case kNoSpaceErr:
            easylink_log("ERROR: Cannot fit HTTPHeader.");
            goto Reconn;

          case kConnectionErr:
            // NOTE: kConnectionErr from SocketReadHTTPHeader means it's closed
            easylink_log("ERROR: Connection closed.");
              /*Roll back to previous settings (if it has) and reboot*/
            if(Context->flashContentInRam.micoSystemConfig.configured == wLanUnConfigured ){
              Context->flashContentInRam.micoSystemConfig.configured = allConfigured;
              MICOUpdateConfiguration( Context );
              MicoSystemReboot();
            }else{
              micoWlanPowerOff();
              msleep(20);
            }
            goto threadexit;

          default:
            easylink_log("ERROR: HTTP Header parse internal error: %d", err);
            goto Reconn;
        }
      }
    }
    continue;
Reconn:
    HTTPHeaderClear( httpHeader );
    SocketClose(&easylinkClient_fd);
    easylinkClient_fd = -1;
    require(reConnCount < 6, reboot);
    reConnCount++;
    sleep(5);
  }  

threadexit:
  ConfigWillStop( Context );
  _cleanEasyLinkResource( Context );
  mico_rtos_set_semaphore( &config_finished_sem ); 
  mico_rtos_delete_thread( NULL );
  return;
  
/*SSID or Password is not correct, module cannot connect to wlan, so reboot and enter EasyLink again*/
reboot:
  MicoSystemReboot();
  return;
}

OSStatus _FTCRespondInComingMessage(int fd, HTTPHeader_t* inHeader, mico_Context_t * const inContext)
{
    OSStatus err = kUnknownErr;
    const char *        value;
    size_t              valueSize;

    easylink_log_trace();

    switch(inHeader->statusCode){
      case kStatusAccept:
        easylink_log("Easylink server accepted!");
        err = kNoErr;
        goto exit;

      case kStatusOK:
        easylink_log("Easylink server respond status OK!");
        err = HTTPGetHeaderField( inHeader->buf, inHeader->len, "Content-Type", NULL, NULL, &value, &valueSize, NULL );
        require_noerr(err, exit);
        if( strnicmpx( value, strlen(kMIMEType_JSON), kMIMEType_JSON ) == 0 ){
          easylink_log("Receive JSON config data!");
          err = ConfigIncommingJsonMessage( inHeader->extraDataPtr, inContext);
          inContext->flashContentInRam.micoSystemConfig.configured = allConfigured;
          err = MICOUpdateConfiguration(inContext);
          easylink_thread_should_exit = true;
        }
#ifdef MICO_FLASH_FOR_UPDATE
        else if(strnicmpx( value, strlen(kMIMEType_JSON), kMIMEType_MXCHIP_OTA ) == 0){
          easylink_log("Receive OTA data!");
          mico_rtos_lock_mutex(&inContext->flashContentInRam_mutex);
          memset(&inContext->flashContentInRam.bootTable, 0, sizeof(boot_table_t));
          inContext->flashContentInRam.bootTable.length = inHeader->contentLength;
          inContext->flashContentInRam.bootTable.start_address = UPDATE_START_ADDRESS;
          inContext->flashContentInRam.bootTable.type = 'A';
          inContext->flashContentInRam.bootTable.upgrade_type = 'U';
          inContext->flashContentInRam.micoSystemConfig.easyLinkByPass = EASYLINK_BYPASS;
          MICOUpdateConfiguration(inContext);
          mico_rtos_unlock_mutex(&inContext->flashContentInRam_mutex);
          SocketClose(&fd);
          easylink_thread_should_exit = true;
        }
#endif
        else{
          return kUnsupportedDataErr;
        }
        err = kNoErr;
        goto exit;
        
      default:
        goto exit;
    }

 exit:
    return err;

}



