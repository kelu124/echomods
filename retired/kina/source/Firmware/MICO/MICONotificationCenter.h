/**
******************************************************************************
* @file    MICONotificationCenter.h 
* @author  William Xu
* @version V1.0.0
* @date    05-May-2014
* @brief   This file provide function prototypes for operations on MICO's 
*          notification center
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


#ifndef __MICONOTIFICATIONCENTER_H__
#define __MICONOTIFICATIONCENTER_H__

//#include "MICODefine.h"
#include "Common.h"

typedef enum {
  NOTIFY_STATION_UP = 1,
  NOTIFY_STATION_DOWN,

  NOTIFY_AP_UP,
  NOTIFY_AP_DOWN,
} WiFiEvent;

typedef enum{
  /* MICO system defined notifications */
  mico_notify_WIFI_SCAN_COMPLETED,          //void (*function)(ScanResult *pApList, mico_Context_t * const inContext);
  mico_notify_WIFI_STATUS_CHANGED,          //void (*function)(WiFiEvent status, mico_Context_t * const inContext);
  mico_notify_WiFI_PARA_CHANGED,            //void (*function)(apinfo_adv_t *ap_info, char *key, int key_len, mico_Context_t * const inContext);
  mico_notify_DHCP_COMPLETED,               //void (*function)(IPStatusTypedef *pnet, mico_Context_t * const inContext);
  mico_notify_EASYLINK_WPS_COMPLETED,       //void (*function)(network_InitTypeDef_st *nwkpara, mico_Context_t * const inContext);
  mico_notify_EASYLINK_GET_EXTRA_DATA,      //void (*function)(int datalen, char*data, mico_Context_t * const inContext);
  mico_notify_TCP_CLIENT_CONNECTED,         //void (*function)(char *str, int len, mico_Context_t * const inContext);
  mico_notify_DNS_RESOLVE_COMPLETED,        //void (*function)(char *str, int len, mico_Context_t * const inContext);
  mico_notify_READ_APP_INFO,                //void (*function)(int fd, mico_Context_t * const inContext);
  mico_notify_SYS_WILL_POWER_OFF,           //void (*function)(mico_Context_t * const inContext);
  mico_notify_WIFI_CONNECT_FAILED,          //void join_fail(OSStatus err, mico_Context_t * const inContext);
  mico_notify_WIFI_SCAN_ADV_COMPLETED,      //void (*function)(ScanResult_adv *pApList, mico_Context_t * const inContext);
  mico_notify_WIFI_Fatal_ERROR,             //void (*function)(mico_Context_t * const inContext);
  mico_notify_Stack_Overflow_ERROR,         //void (*function)(char *taskname, mico_Context_t * const inContext);
 
  /* User defined notifications */_

} mico_notify_types_t;

OSStatus MICOInitNotificationCenter   ( void * const inContext );

OSStatus MICOAddNotification          ( mico_notify_types_t notify_type, void *functionAddress );

OSStatus MICORemoveNotification       ( mico_notify_types_t notify_type, void *functionAddress );

void sendNotifySYSWillPowerOff(void);
void system_version(char *str, int len);



#endif


