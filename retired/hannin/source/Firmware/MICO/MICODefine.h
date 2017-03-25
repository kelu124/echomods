/**
******************************************************************************
* @file    MICODefine.h 
* @author  William Xu
* @version V1.0.0
* @date    05-May-2014
* @brief   This file provide constant definition and type declaration for MICO
*          running.
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

#ifndef __MICODEFINE_H
#define __MICODEFINE_H

#include "Common.h"
#include "Debug.h"
#include "MICO.h"
//#include "JSON-C/json.h"
#include "MICOAppDefine.h"

#define CONFIG_MODE_EASYLINK                    (2)
#define CONFIG_MODE_SOFT_AP                     (3)
#define CONFIG_MODE_EASYLINK_WITH_SOFTAP        (4)
#define CONFIG_MODE_WPS                         (5)
#define CONFIG_MODE_WPS_WITH_SOFTAP             (6)
#define CONFIG_MODE_WAC                         (7)
#define CONFIG_MODE_AIRKISS                     (8)

#define EASYLINK_BYPASS_NO                      (0)
#define EASYLINK_BYPASS                         (1)
#define EASYLINK_SOFT_AP_BYPASS                 (2)

#define MICO_CLI_ENABLE
//#define MFG_MODE_AUTO /**< Device enter MFG mode if MICO settings are erased. */

/* Define MICO service thread stack size */
#define STACK_SIZE_LOCAL_CONFIG_SERVER_THREAD   0x300
#define STACK_SIZE_LOCAL_CONFIG_CLIENT_THREAD   0x450
#define STACK_SIZE_NTP_CLIENT_THREAD            0x450
#define STACK_SIZE_MICO_SYSTEM_MONITOR_THREAD   0x300

#define CONFIG_SERVICE_PORT     8000

#define APPLICATION_WATCHDOG_TIMEOUT_SECONDS  10 /**< Watch-dog enabled by MICO's main thread:
                                                     5 seconds to reload. */

#define maxSsidLen          32
#define maxKeyLen           64
#define maxNameLen          32
#define maxIpLen            16


typedef enum  {
  /*All settings are in default state, module will enter easylink mode when powered on. 
  Press down Easyink button for 3 seconds (defined by RestoreDefault_TimeOut) to enter this mode */
  unConfigured,
  /*Module will enter easylink mode temperaly when powered on, and go back to allConfigured
    mode after time out (Defined by EasyLink_TimeOut), This mode is used for changing wlan
    settings if module is moved to a new wlan enviroment. Press down Easyink button to
    enter this mode */                
  wLanUnConfigured,
  /*Normal working mode, module use the configured settings to connecte to wlan, and run 
    user's threads*/
  allConfigured,
  /*If MFG_MODE_AUTO is enabled and MICO settings are erased (maybe a fresh device just has 
    been programed or MICO settings is damaged), module will enter MFG mode when powered on. */
  mfgConfigured
}Config_State_t;

typedef enum
{
    eState_Normal,
    eState_Software_Reset,
    eState_Wlan_Powerdown,
    eState_Restore_default,
    eState_Standby,
} SYS_State_t;


/* Upgrade iamge should save this table to flash */
typedef struct  _boot_table_t {
  uint32_t start_address; // the address of the bin saved on flash.
  uint32_t length; // file real length
  uint8_t version[8];
  uint8_t type; // B:bootloader, P:boot_table, A:application, D: 8782 driver
  uint8_t upgrade_type; //u:upgrade, 
  uint8_t reserved[6];
}boot_table_t;

typedef struct _mico_sys_config_t
{
  /*Device identification*/
  char            name[maxNameLen];

  /*Wi-Fi configuration*/
  char            ssid[maxSsidLen];
  char            user_key[maxKeyLen]; 
  int             user_keyLength;
  char            key[maxKeyLen]; 
  int             keyLength;
  char            bssid[6];
  int             channel;
  SECURITY_TYPE_E security;

  /*Power save configuration*/
  bool            rfPowerSaveEnable;
  bool            mcuPowerSaveEnable;

  /*Local IP configuration*/
  bool            dhcpEnable;
  char            localIp[maxIpLen];
  char            netMask[maxIpLen];
  char            gateWay[maxIpLen];
  char            dnsServer[maxIpLen];

  /*EasyLink configuration*/
  Config_State_t  configured;
  uint8_t        easyLinkByPass;
  uint32_t        easylinkServerIP;

  /*Services in MICO system*/
  bool            bonjourEnable;
  bool            configServerEnable;

  /*Update seed number when configuration is changed*/
  int32_t         seed;
} mico_sys_config_t;

typedef struct _flash_configuration_t {

  /*OTA options*/
  boot_table_t             bootTable;
  /*MICO system core configuration*/
  mico_sys_config_t        micoSystemConfig;
  /*Application configuration*/
  application_config_t     appConfig; 
} flash_content_t;

typedef struct _current_mico_status_t 
{
  /*MICO system Running status*/
  SYS_State_t           sys_state;
  char                  localIp[maxIpLen];
  char                  netMask[maxIpLen];
  char                  gateWay[maxIpLen];
  char                  dnsServer[maxIpLen];
  char                  mac[18];
  mico_semaphore_t      sys_state_change_sem;
} current_mico_status_t;

typedef struct _mico_Context_t
{
  /*Flash content*/
  flash_content_t           flashContentInRam;
  mico_mutex_t              flashContentInRam_mutex;

  /*Running status*/
  current_mico_status_t     micoStatus;
  current_app_status_t      appStatus;
} mico_Context_t;

#define CONFIG_DATA_SIZE (sizeof(application_config_t)-sizeof(uint32_t))

OSStatus MICOStartBonjourService        ( WiFi_Interface interface, mico_Context_t * const inContext );
OSStatus MICOStartConfigServer          ( mico_Context_t * const inContext );
OSStatus MICOStopConfigServer           ( void );
OSStatus MICOStartNTPClient             ( mico_Context_t * const inContext );
OSStatus MICOStartApplication           ( mico_Context_t * const inContext );

OSStatus MICORestoreDefault             ( mico_Context_t * const inContext );
OSStatus MICOReadConfiguration          ( mico_Context_t * const inContext );
OSStatus MICOUpdateConfiguration        ( mico_Context_t * const inContext );
#ifdef MFG_MODE_AUTO
OSStatus MICORestoreMFG                 ( mico_Context_t * const inContext );
#endif

mico_Context_t *getGlobalContext(void);
void mico_mfg_test( mico_Context_t * const inContext );

#endif /* __MICO_DEFINE_H */
