/**
******************************************************************************
* @file    FogCloudServiceDef.h 
* @author  Eshen Wang
* @version V0.2.0
* @date    23-Nov-2014
* @brief   This header contains the public defines for FogCloud service. 
  operation
******************************************************************************
* @attention
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
* TIME. AS A RESULT, MXCHIP Inc. SHALL NOT BE HELD LIABLE FOR ANY
* DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
* CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
* <h2><center>&copy; COPYRIGHT 2014 MXCHIP Inc.</center></h2>
******************************************************************************
*/ 


#ifndef __EASYFOGCLOUD_SERVICE_DEF_H_
#define __EASYFOGCLOUD_SERVICE_DEF_H_

#include "Common.h"

/*******************************************************************************
 * DEFINES
 ******************************************************************************/

// string length in bytes
#define MAX_SIZE_DOMAIN_NAME            64

#define MAX_SIZE_BSSID                  18

#define MAX_SIZE_PRODUCT_ID             37
#define MAX_SIZE_PRODUCT_KEY            37

#define MAX_SIZE_LOGIN_ID               37
#define MAX_SIZE_DEV_PASSWD             37
   
#define MAX_SIZE_USER_TOKEN             33
#define MAX_SIZE_DEVICE_TOKEN           33
   
#define MAX_SIZE_DEVICE_ID              37
#define MAX_SIZE_DEVICE_KEY             37

#define MAX_SIZE_DEVICE_NAME            32

#define MAX_SIZE_FW_VERSION             32
#define MAX_SIZE_FILE_PATH              256
#define MAX_SIZE_FILE_MD5               64
   
#define MAX_SIZE_SUBSCRIBE_TOPIC        256
#define MAX_SIZE_PUBLISH_TOPIC          256

// default values for easycloud server
#define DEFAULT_CLOUD_SERVER            "api.easylink.io"
#define DEFAULT_CLOUD_PORT              80

// default values for MQTT server
#define DEFAULT_MQTT_SERVER             "api.easylink.io"
#define DEFAULT_MQTT_PORT               1883
#define DEFAULT_MQTT_PORT_SSL           8883
// in seconds, here set 30s
#define DEFAULT_MQTT_CLLIENT_KEEPALIVE_INTERVAL    15

 /*******************************************************************************
 * STRUCTURES
 ******************************************************************************/

typedef enum {
  FOGCLOUD_STOPPED = 1,      //service stopped
  FOGCLOUD_STARTED = 2,      //service start up
  FOGCLOUD_CONNECTED = 3,    //service work ok
  FOGCLOUD_DISCONNECTED = 4  //service diconnected from server
} easycloud_service_state_t;

typedef struct _easycloud_service_status_t {
  //service running status
  easycloud_service_state_t  state;
  //device status info
  bool                    isActivated;
  char                    deviceId[MAX_SIZE_DEVICE_ID];
  char                    masterDeviceKey[MAX_SIZE_DEVICE_KEY];
  
  char                    latestRomVersion[MAX_SIZE_FW_VERSION];
  char                    bin_file[MAX_SIZE_FILE_PATH];
  char                    bin_md5[MAX_SIZE_FILE_MD5];
  uint64_t                bin_file_size;
  
  char                    device_name[MAX_SIZE_DEVICE_NAME];
} easycloud_service_status_t;
 
//message recived callback function prototype
typedef void (*easycloudMsgRecvCallBack)(void* const context, 
                                         const char* topic,
                                         const unsigned int topicLen,
                                         unsigned char* msg, unsigned int msgLen);
typedef void (*easycloudStatusChangedCallback)(void* const context,
                                               easycloud_service_status_t serviceStateInfo);

typedef struct _easycloud_service_config_t {
  /* product properties */
  char                    bssid[MAX_SIZE_BSSID];
  char                    productId[MAX_SIZE_PRODUCT_ID];
  char                    productKey[MAX_SIZE_PRODUCT_KEY];
  
  /* easycloud server info */
  char                    cloudServerDomain[MAX_SIZE_DOMAIN_NAME];
  int                     cloudServerPort;
  char                    mqttServerDomain[MAX_SIZE_DOMAIN_NAME];
  int                     mqttServerPort;
  uint16_t                mqttKeepAliveInterval;
  
  /* device settings */
  char                    loginId[MAX_SIZE_LOGIN_ID];      // user login id
  char                    devPasswd[MAX_SIZE_DEV_PASSWD];  // master device password set by user
  char                    userToken[MAX_SIZE_USER_TOKEN];  // user token
  
  /* callback */
  easycloudMsgRecvCallBack  msgRecvhandler;                // message received callback
  easycloudStatusChangedCallback statusNotify;             // cloud servie status changed callback
  //user context
  void* context;
} easycloud_service_config_t;

typedef struct _easycloud_service_context_t {
  /*easycloud service config info*/
  easycloud_service_config_t service_config_info;
  //mico_mutex_t service_config_info_mutex;
  
  /*easycloud service running status*/
  easycloud_service_status_t service_status;
} easycloud_service_context_t;

/* dev activate or authorize request data */
typedef struct _dev_activate_data_t {
  char                   loginId[MAX_SIZE_LOGIN_ID];
  char                   devPasswd[MAX_SIZE_DEV_PASSWD];
  char                   user_token[MAX_SIZE_USER_TOKEN];
} MVDActivateRequestData_t, MVDAuthorizeRequestData_t, MVDOTARequestData_t, MVDResetRequestData_t;

/* params for download file from server */
typedef struct _dev_download_file_data_t {
  char                   file_path[MAX_SIZE_FILE_PATH];
  char                   file_checksum[MAX_SIZE_FILE_MD5];
  char                   file_version[MAX_SIZE_FW_VERSION];
} MVDDownloadFileRequestData_t;

#endif
