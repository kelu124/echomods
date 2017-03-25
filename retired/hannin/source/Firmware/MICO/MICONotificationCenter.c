/**
******************************************************************************
* @file    MICONotificationCenter.c 
* @author  William Xu
* @version V1.0.0
* @date    05-May-2014
* @brief   This file provide functions for operations on MICO's  notification 
*          center
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


#include "MICONotificationCenter.h"
#include "Common.h"
#include "Mico.h"

typedef struct _Notify_list{
  void  *function;
  struct _Notify_list *next;
  void  *contex;
} _Notify_list_t;

static void * _Context;

_Notify_list_t* Notify_list[20] = {NULL};

/* MICO system defined notifications */
typedef void (*mico_notify_WIFI_SCAN_COMPLETE_function)           ( ScanResult *pApList, void * inContext );
typedef void (*mico_notify_WIFI_SCAN_ADV_COMPLETE_function)       ( ScanResult_adv *pApAdvList, void * inContext );
typedef void (*mico_notify_WIFI_STATUS_CHANGED_function)          ( WiFiEvent status, void * inContext );
typedef void (*mico_notify_WiFI_PARA_CHANGED_function)            ( apinfo_adv_t *ap_info, char *key, int key_len, void * inContext );
typedef void (*mico_notify_DHCP_COMPLETE_function)                ( IPStatusTypedef *pnet, void * inContext );
typedef void (*mico_notify_EASYLINK_COMPLETE_function)            ( network_InitTypeDef_st *nwkpara, void * inContext );
typedef void (*mico_notify_EASYLINK_GET_EXTRA_DATA_function)      ( int datalen, char*data, void * inContext );
typedef void (*mico_notify_TCP_CLIENT_CONNECTED_function)         ( int fd, void * inContext );
typedef void (*mico_notify_DNS_RESOLVE_COMPLETED_function)        ( uint8_t *hostname, uint32_t ip, void * inContext );
typedef void (*mico_notify_READ_APP_INFO_function)                ( char *str, int len, void * inContext );
typedef void (*mico_notify_SYS_WILL_POWER_OFF_function)           ( void * inContext );
typedef void (*mico_notify_WIFI_CONNECT_FAILED_function)          ( OSStatus err, void * inContext );
typedef void (*mico_notify_WIFI_FATAL_ERROR_function)             ( void * inContext );
typedef void (*mico_notify_STACK_OVERFLOW_ERROR_function)         ( char *taskname, void * const inContext );

/* User defined notifications */

void ApListCallback(ScanResult *pApList)
{
  _Notify_list_t *temp =  Notify_list[mico_notify_WIFI_SCAN_COMPLETED];
  if(temp == NULL)
    return;
  else{
    do{
      ((mico_notify_WIFI_SCAN_COMPLETE_function)(temp->function))(pApList, _Context);
      temp = temp->next;
    }while(temp!=NULL);
  }
}

void ApListAdvCallback(ScanResult_adv *pApAdvList)
{
  _Notify_list_t *temp =  Notify_list[mico_notify_WIFI_SCAN_ADV_COMPLETED];
  if(temp == NULL)
    return;
  else{
    do{
      ((mico_notify_WIFI_SCAN_ADV_COMPLETE_function)(temp->function))(pApAdvList, _Context);
      temp = temp->next;
    }while(temp!=NULL);
  }
}

void WifiStatusHandler(WiFiEvent status)
{
  _Notify_list_t *temp =  Notify_list[mico_notify_WIFI_STATUS_CHANGED];
  if(temp == NULL)
    return;
  else{
    do{
      ((mico_notify_WIFI_STATUS_CHANGED_function)(temp->function))(status, _Context);
      temp = temp->next;
    }while(temp!=NULL);
  }
}

void connected_ap_info(apinfo_adv_t *ap_info, char *key, int key_len)
{
  _Notify_list_t *temp =  Notify_list[mico_notify_WiFI_PARA_CHANGED];
  if(temp == NULL)
    return;
  else{
    do{
      ((mico_notify_WiFI_PARA_CHANGED_function)(temp->function))(ap_info, key, key_len, _Context);
      temp = temp->next;
    }while(temp!=NULL);
  }
}

void NetCallback(IPStatusTypedef *pnet)
{
  _Notify_list_t *temp =  Notify_list[mico_notify_DHCP_COMPLETED];
  if(temp == NULL)
    return;
  else{
    do{
      ((mico_notify_DHCP_COMPLETE_function)(temp->function))(pnet, _Context);
      temp = temp->next;
    }while(temp!=NULL);
  }
}

void RptConfigmodeRslt(network_InitTypeDef_st *nwkpara)
{
  _Notify_list_t *temp =  Notify_list[mico_notify_EASYLINK_WPS_COMPLETED];
  if(temp == NULL)
    return;
  else{
    do{
      ((mico_notify_EASYLINK_COMPLETE_function)(temp->function))(nwkpara, _Context);
      temp = temp->next;
    }while(temp!=NULL);
  }
}

void easylink_user_data_result(int datalen, char*data)
{
  _Notify_list_t *temp =  Notify_list[mico_notify_EASYLINK_GET_EXTRA_DATA];
  if(temp == NULL)
    return;
  else{
    do{
      ((mico_notify_EASYLINK_GET_EXTRA_DATA_function)(temp->function))(datalen, data, _Context);
      temp = temp->next;
    }while(temp!=NULL);
  }  
}

void socket_connected(int fd)
{
  _Notify_list_t *temp =  Notify_list[mico_notify_TCP_CLIENT_CONNECTED];
  if(temp == NULL)
    return;
  else{
    do{
      ((mico_notify_TCP_CLIENT_CONNECTED_function)(temp->function))(fd, _Context);
      temp = temp->next;
    }while(temp!=NULL);
  }    
}

void dns_ip_set(uint8_t *hostname, uint32_t ip)
{
  _Notify_list_t *temp =  Notify_list[mico_notify_DNS_RESOLVE_COMPLETED];
  if(temp == NULL)
    return;
  else{
    do{
      ((mico_notify_DNS_RESOLVE_COMPLETED_function)(temp->function))(hostname, ip, _Context);
      temp = temp->next;
    }while(temp!=NULL);
  }    
}


void system_version(char *str, int len){
  _Notify_list_t *temp =  Notify_list[mico_notify_READ_APP_INFO];
  if(Notify_list[mico_notify_READ_APP_INFO] == NULL)
    return;
  else{
    do{
      ((mico_notify_READ_APP_INFO_function)(temp->function))(str, len, _Context);
      temp = temp->next;
    }while(temp!=NULL);
  }
}

void sendNotifySYSWillPowerOff(void)
{
  _Notify_list_t *temp =  Notify_list[mico_notify_SYS_WILL_POWER_OFF];
  if(temp == NULL)
    return;
  else{
    do{
      ((mico_notify_SYS_WILL_POWER_OFF_function)(temp->function))(_Context);
      temp = temp->next;
    }while(temp!=NULL);
  }    
}

void join_fail(OSStatus err)
{
  _Notify_list_t *temp =  Notify_list[mico_notify_WIFI_CONNECT_FAILED];
  if(temp == NULL)
    return;
  else{
    do{
      ((mico_notify_WIFI_CONNECT_FAILED_function)(temp->function))(err, _Context);
      temp = temp->next;
    }while(temp!=NULL);
  }    
}

void wifi_reboot_event(void)
{
  _Notify_list_t *temp =  Notify_list[mico_notify_WIFI_Fatal_ERROR];
  if(temp == NULL)
    return;
  else{
    do{
      ((mico_notify_WIFI_FATAL_ERROR_function)(temp->function))(_Context);
      temp = temp->next;
    }while(temp!=NULL);
  }    
}

void mico_rtos_stack_overflow(char *taskname)
{
  _Notify_list_t *temp =  Notify_list[mico_notify_Stack_Overflow_ERROR];
  if(temp == NULL)
    return;
  else{
    do{
      ((mico_notify_STACK_OVERFLOW_ERROR_function)(temp->function))(taskname, _Context);
      temp = temp->next;
    }while(temp!=NULL);
  }    
}


OSStatus MICOInitNotificationCenter  ( void * const inContext )
{
  OSStatus err = kNoErr;
  require_action(inContext, exit, err = kParamErr);
  _Context = inContext;
exit:
  return err;
}

OSStatus MICOAddNotification( mico_notify_types_t notify_type, void *functionAddress )
{
  OSStatus err = kNoErr;
  _Notify_list_t *temp =  Notify_list[notify_type];
  _Notify_list_t *notify = (_Notify_list_t *)malloc(sizeof(_Notify_list_t));
  require_action(notify, exit, err = kNoMemoryErr);
  notify->function = functionAddress;
  notify->next = NULL;
  if(Notify_list[notify_type] == NULL){
    Notify_list[notify_type] = notify;
    notify->next = NULL;
  }else{
    if(temp->function == functionAddress)
        return kNoErr;   //Nodify already exist
    while(temp->next!=NULL){
      temp = temp->next;
      if(temp->function == functionAddress)
        return kNoErr;   //Nodify already exist
    }
    temp->next = notify;
  }
exit:
  return err;
}

OSStatus MICORemoveNotification( mico_notify_types_t notify_type, void *functionAddress )
{
  OSStatus err = kNoErr;
  _Notify_list_t *temp2;
  _Notify_list_t *temp = Notify_list[notify_type];
  require_action(Notify_list[notify_type], exit, err = kDeletedErr);
  do{
    if(temp->function == functionAddress){
      if(temp == Notify_list[notify_type]){  //first element
        Notify_list[notify_type] = Notify_list[notify_type]->next;
        free(temp);
      }else{
        temp2->next = temp->next;
        free(temp);
      }
       break;
    }
    require_action(temp->next!=NULL, exit, err = kNotFoundErr);
    temp2 = temp;
    temp = temp->next;
  }while(temp != NULL);

exit:
  return err;
}




// void WatchDog(void)
// {
  
// }


// void RptConfigmodeRslt(network_InitTypeDef_st *nwkpara)
// {

// }


// void NetCallback(net_para_st *pnet)
// {

// }





// void dns_ip_set(u8 *hostname, u32 ip)
// {

// }


// void socket_connected(int fd)
// {

// }