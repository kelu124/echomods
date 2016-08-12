/**
******************************************************************************
* @file    EasyLinkSoftAP.c 
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
#include "platform_config.h"
#include "StringUtils.h"
#include "HTTPUtils.h"
#include "SocketUtils.h"
#include "MDNSUtils.h"

#include "EasyLinkSoftAP.h"
  
#define easylink_uap_log(M, ...) custom_log("EasyLink uAP", M, ##__VA_ARGS__)
#define easylink_uap_log_trace() custom_log_trace("EasyLink uAP")

#define KEY_SSID          "SSID"
#define KEY_PASSWORD      "PASSWORD"
#define KEY_DHCP          "DHCP"
#define KEY_IP            "IP"
#define KEY_NETMASK       "NETMASK"
#define KEY_GATEWAY       "GATEWAY"
#define KEY_DNS1          "DNS1"
#define KEY_DNS2          "DNS2"


bool uap_config_mode = false;
mico_semaphore_t uap_config_finished_sem = NULL;

static int _bonjourStarted = false;

extern OSStatus     ConfigIncommingJsonMessage    ( const char *input, mico_Context_t * const inContext );
extern json_object* ConfigCreateReportJsonMessage ( mico_Context_t * const inContext );
extern void         ConfigWillStart               ( mico_Context_t * const inContext );
extern void         ConfigWillStop                ( mico_Context_t * const inContext );
extern void         ConfigEasyLinkIsSuccess       ( mico_Context_t * const inContext );
extern void         ConfigSoftApWillStart         ( mico_Context_t * const inContext );
extern OSStatus     ConfigELRecvAuthData          ( char * userInfo, mico_Context_t * const inContext );
extern OSStatus     MICOStartBonjourService       ( WiFi_Interface interface, mico_Context_t * const inContext );
extern OSStatus     MICOstartConfigServer         ( mico_Context_t * const inContext );

static OSStatus _initBonjourForEasyLink( WiFi_Interface interface, mico_Context_t * const inContext );

extern void connect_wifi_fast( mico_Context_t * const inContext);
extern void connect_wifi_normal( mico_Context_t * const inContext);



static void _EasyLinkNotify_WifiStatusHandler(WiFiEvent event, mico_Context_t * const inContext)
{
  easylink_uap_log_trace();
  IPStatusTypedef para;

  require(inContext, exit);
  switch (event) {
  case NOTIFY_STATION_UP:
    micoWlanGetIPStatus(&para, Station);
    strncpy(inContext->flashContentInRam.micoSystemConfig.localIp, para.ip, maxIpLen);
    strncpy(inContext->flashContentInRam.micoSystemConfig.netMask, para.mask, maxIpLen);
    strncpy(inContext->flashContentInRam.micoSystemConfig.gateWay, para.gate, maxIpLen);
    strncpy(inContext->flashContentInRam.micoSystemConfig.dnsServer, para.dns, maxIpLen);
    _initBonjourForEasyLink( Station, inContext );
    suspend_bonjour_service(false);
    break;
  case NOTIFY_STATION_DOWN:
    suspend_bonjour_service(true);
    break;
  default:
    break;
  }
exit:
  return;
}

static void _EasyLinkNotify_SYSWillPoerOffHandler( mico_Context_t * const inContext)
{
  (void)inContext;
  if(_bonjourStarted == true){
    suspend_bonjour_service(true);
  }
}

static void _EasyLinkNotify_WiFIParaChangedHandler(apinfo_adv_t *ap_info, char *key, int key_len, mico_Context_t * const inContext)
{
  easylink_uap_log_trace();
  require(inContext, exit);

  easylink_uap_log("Wi-Fi para changed callback");
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

static void _EasyLinkNotify_DHCPCompleteHandler(IPStatusTypedef *pnet, mico_Context_t * const inContext)
{
  easylink_uap_log_trace();
  require(inContext, exit);
  strcpy((char *)inContext->micoStatus.localIp, pnet->ip);
  strcpy((char *)inContext->micoStatus.netMask, pnet->mask);
  strcpy((char *)inContext->micoStatus.gateWay, pnet->gate);
  strcpy((char *)inContext->micoStatus.dnsServer, pnet->dns);
exit:
  return;
}

static OSStatus _initBonjourForEasyLink( WiFi_Interface interface, mico_Context_t * const inContext )
{
  char *temp_txt= NULL;
  char *temp_txt2;
  OSStatus err = kNoErr;
  net_para_st para;
  bonjour_init_t init;

  temp_txt = malloc(500);
  require_action(temp_txt, exit, err = kNoMemoryErr);

  memset(&init, 0x0, sizeof(bonjour_init_t));

  micoWlanGetIPStatus(&para, Station);

  init.service_name = "_easylink_config._tcp.local.";

  /*   name#xxxxxx.local.  */
  snprintf( temp_txt, 100, "%s#%c%c%c%c%c%c.local.", inContext->flashContentInRam.micoSystemConfig.name, 
                                                     inContext->micoStatus.mac[9],  inContext->micoStatus.mac[10], \
                                                     inContext->micoStatus.mac[12], inContext->micoStatus.mac[13], \
                                                     inContext->micoStatus.mac[15], inContext->micoStatus.mac[16] );
  init.host_name = (char*)__strdup(temp_txt);

  /*   name#xxxxxx.   */
  snprintf( temp_txt, 100, "%s#%c%c%c%c%c%c",        inContext->flashContentInRam.micoSystemConfig.name, 
                                                     inContext->micoStatus.mac[9],  inContext->micoStatus.mac[10], \
                                                     inContext->micoStatus.mac[12], inContext->micoStatus.mac[13], \
                                                     inContext->micoStatus.mac[15], inContext->micoStatus.mac[16] );
  init.instance_name = (char*)__strdup(temp_txt);

  init.service_port = FTC_PORT;
  init.interface = interface;

  temp_txt2 = __strdup_trans_dot(inContext->micoStatus.mac);
  sprintf(temp_txt, "MAC=%s.", temp_txt2);
  free(temp_txt2);

  temp_txt2 = __strdup_trans_dot(FIRMWARE_REVISION);
  sprintf(temp_txt, "%sFirmware Rev=%s.", temp_txt, temp_txt2);
  free(temp_txt2);
  
  temp_txt2 = __strdup_trans_dot(HARDWARE_REVISION);
  sprintf(temp_txt, "%sHardware Rev=%s.", temp_txt, temp_txt2);
  free(temp_txt2);

  temp_txt2 = __strdup_trans_dot(MicoGetVer());
  sprintf(temp_txt, "%sMICO OS Rev=%s.", temp_txt, temp_txt2);
  free(temp_txt2);

  temp_txt2 = __strdup_trans_dot(MODEL);
  sprintf(temp_txt, "%sModel=%s.", temp_txt, temp_txt2);
  free(temp_txt2);

  temp_txt2 = __strdup_trans_dot(PROTOCOL);
  sprintf(temp_txt, "%sProtocol=%s.", temp_txt, temp_txt2);
  free(temp_txt2);

  temp_txt2 = __strdup_trans_dot(MANUFACTURER);
  sprintf(temp_txt, "%sManufacturer=%s.", temp_txt, temp_txt2);
  free(temp_txt2);
  
  if(interface == Soft_AP)
    sprintf(temp_txt, "%swlan unconfigured=T.", temp_txt);
  else
    sprintf(temp_txt, "%swlan unconfigured=F.", temp_txt);

  sprintf(temp_txt, "%sSeed=%u.", temp_txt, inContext->flashContentInRam.micoSystemConfig.seed);
  init.txt_record = (char*)__strdup(temp_txt);

  bonjour_service_init(init);

  free(init.host_name);
  free(init.instance_name);
  free(init.txt_record);

  err = MICOAddNotification( mico_notify_SYS_WILL_POWER_OFF, (void *)_EasyLinkNotify_SYSWillPoerOffHandler );
  require_noerr( err, exit ); 

exit:
  if(temp_txt) free(temp_txt);
  return err;
}

OSStatus startEasyLinkSoftAP( mico_Context_t * const inContext)
{
  easylink_uap_log_trace();
  OSStatus err = kUnknownErr;
  network_InitTypeDef_st wNetConfig;

  uap_config_mode = true;

  err = MICOAddNotification( mico_notify_WIFI_STATUS_CHANGED, (void *)_EasyLinkNotify_WifiStatusHandler );
  require_noerr(err, exit);
  err = MICOAddNotification( mico_notify_WiFI_PARA_CHANGED, (void *)_EasyLinkNotify_WiFIParaChangedHandler );
  require_noerr(err, exit);
  err = MICOAddNotification( mico_notify_DHCP_COMPLETED, (void *)_EasyLinkNotify_DHCPCompleteHandler );
  require_noerr( err, exit );    

  mico_rtos_init_semaphore( &uap_config_finished_sem, 1 );

  ConfigWillStart(inContext);
  ConfigSoftApWillStart( inContext );

  if(inContext->flashContentInRam.micoSystemConfig.easyLinkByPass == EASYLINK_BYPASS_NO){
    memset(&wNetConfig, 0, sizeof(network_InitTypeDef_st));
    wNetConfig.wifi_mode = Soft_AP;
    snprintf(wNetConfig.wifi_ssid, 32, "EasyLink_%c%c%c%c%c%c", inContext->micoStatus.mac[9],  inContext->micoStatus.mac[10],
                                                                inContext->micoStatus.mac[12], inContext->micoStatus.mac[13],
                                                                inContext->micoStatus.mac[15], inContext->micoStatus.mac[16] );
    strcpy((char*)wNetConfig.wifi_key, "");
    strcpy((char*)wNetConfig.local_ip_addr, "10.10.10.1");
    strcpy((char*)wNetConfig.net_mask, "255.255.255.0");
    strcpy((char*)wNetConfig.gateway_ip_addr, "10.10.10.1");
    wNetConfig.dhcpMode = DHCP_Server;
    micoWlanStart(&wNetConfig);
    easylink_uap_log("Establish soft ap: %s.....", wNetConfig.wifi_ssid);
    err = _initBonjourForEasyLink( Soft_AP , inContext );
    require_noerr(err, exit);
  }else{
    err = _initBonjourForEasyLink( Station , inContext );
    connect_wifi_fast(inContext);
    require_noerr(err, exit);
  }

  _bonjourStarted = true;
  start_bonjour_service();
  
  err = MICOStartConfigServer( inContext );
  require_noerr( err, exit );

  mico_rtos_get_semaphore( &uap_config_finished_sem, MICO_WAIT_FOREVER ); 
  mico_rtos_deinit_semaphore( &uap_config_finished_sem );

  err = MICORemoveNotification( mico_notify_SYS_WILL_POWER_OFF, (void *)_EasyLinkNotify_SYSWillPoerOffHandler );
  MICOStopConfigServer( );
  stop_bonjour_service( );

exit:
  uap_config_mode = false;
  return err;
}

OSStatus ConfigIncommingJsonMessageUAP( const char *input, mico_Context_t * const inContext )
{
  OSStatus err = kNoErr;
  json_object *new_obj;
  easylink_uap_log_trace();
  inContext->flashContentInRam.micoSystemConfig.easyLinkByPass = EASYLINK_BYPASS_NO;

  new_obj = json_tokener_parse(input);
  require_action(new_obj, exit, err = kUnknownErr);
  easylink_uap_log("Recv config object=%s", json_object_to_json_string(new_obj));
  json_object_object_foreach(new_obj, key, val) {
    if(!strcmp(key, KEY_SSID)){
      strncpy(inContext->flashContentInRam.micoSystemConfig.ssid, json_object_get_string(val), maxSsidLen);
      inContext->flashContentInRam.micoSystemConfig.channel = 0;
      memset(inContext->flashContentInRam.micoSystemConfig.bssid, 0x0, 6);
      inContext->flashContentInRam.micoSystemConfig.security = SECURITY_TYPE_AUTO;
      memcpy(inContext->flashContentInRam.micoSystemConfig.key, inContext->flashContentInRam.micoSystemConfig.user_key, maxKeyLen);
      inContext->flashContentInRam.micoSystemConfig.keyLength = inContext->flashContentInRam.micoSystemConfig.user_keyLength;
    }else if(!strcmp(key, KEY_PASSWORD)){
      inContext->flashContentInRam.micoSystemConfig.security = SECURITY_TYPE_AUTO;
      strncpy(inContext->flashContentInRam.micoSystemConfig.key, json_object_get_string(val), maxKeyLen);
      strncpy(inContext->flashContentInRam.micoSystemConfig.user_key, json_object_get_string(val), maxKeyLen);
      inContext->flashContentInRam.micoSystemConfig.keyLength = strlen(inContext->flashContentInRam.micoSystemConfig.key);
      inContext->flashContentInRam.micoSystemConfig.user_keyLength = strlen(inContext->flashContentInRam.micoSystemConfig.key);
      memcpy(inContext->flashContentInRam.micoSystemConfig.key, inContext->flashContentInRam.micoSystemConfig.user_key, maxKeyLen);
      inContext->flashContentInRam.micoSystemConfig.keyLength = inContext->flashContentInRam.micoSystemConfig.user_keyLength;
    }else if(!strcmp(key, KEY_DHCP)){
      inContext->flashContentInRam.micoSystemConfig.dhcpEnable   = json_object_get_boolean(val);
    }else if(!strcmp(key, KEY_IP)){
      strncpy(inContext->flashContentInRam.micoSystemConfig.localIp, json_object_get_string(val), maxIpLen);
    }else if(!strcmp(key, KEY_NETMASK)){
      strncpy(inContext->flashContentInRam.micoSystemConfig.netMask, json_object_get_string(val), maxIpLen);
    }else if(!strcmp(key, KEY_GATEWAY)){
      strncpy(inContext->flashContentInRam.micoSystemConfig.gateWay, json_object_get_string(val), maxIpLen);
    }else if(!strcmp(key, KEY_DNS1)){
      strncpy(inContext->flashContentInRam.micoSystemConfig.dnsServer, json_object_get_string(val), maxIpLen);
    }
  }
  json_object_put(new_obj);

exit:
  return err; 
}
