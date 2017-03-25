/**
******************************************************************************
* @file    micokit_ext.c
* @author  Eshen Wang
* @version V1.0.0
* @date    8-May-2015
* @brief   micokit extension board manufacture test operations..
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


#include "MicoPlatform.h"
#include "MICONotificationCenter.h"
#include "micokit_ext.h"
#include "MiCODefine.h"

#include "temp_hum_sensor\BME280\bme280_user.h"
#include "temp_hum_sensor\DHT11\DHT11.h"

extern mico_semaphore_t      mfg_test_state_change_sem;
extern volatile int16_t      mfg_test_module_number;

//---------------------------- user modules functions --------------------------

// Key1 clicked callback:  previous test module in test mode
void user_key1_clicked_callback(void)
{
  if(NULL != mfg_test_state_change_sem){
    if( 0 < mfg_test_module_number){
      mfg_test_module_number = (mfg_test_module_number - 1)%(MFG_TEST_MAX_MODULE_NUM+1);
    }
    else{
      mfg_test_module_number = MFG_TEST_MAX_MODULE_NUM;
    }
    mico_rtos_set_semaphore(&mfg_test_state_change_sem);  // go back to previous module
  }
  return;
}

// Key1 long pressed callback
void user_key1_long_pressed_callback(void)
{
  return;
}

// Key2 clicked callback:  next test module in test mode
void user_key2_clicked_callback(void)
{
  if(NULL != mfg_test_state_change_sem){
    mfg_test_module_number = (mfg_test_module_number+1)%(MFG_TEST_MAX_MODULE_NUM+1);
    mico_rtos_set_semaphore(&mfg_test_state_change_sem);  // start next module
  }
  return;
}

// Key2 long pressed callback(use for enter MFG MODE when reset)
void user_key2_long_pressed_callback(void)
{
  return;
}


//---------------------------- MFG TEST FOR EXT-BOARD --------------------------
#define mfg_test_oled_test_string    "abcdefghijklmnop123456789012345612345678901234561234567890123456"
#define OLED_MFG_TEST_PREFIX         "TEST:"

mico_semaphore_t mfg_test_state_change_sem = NULL;
volatile int16_t mfg_test_module_number = 0;
volatile bool scanap_done = false;
extern void wlan_get_mac_address(char *mac);

static void mf_printf(char *str)
{
  OLED_Clear();
  OLED_ShowString(0,0,(uint8_t*)str);
}

void mico_notify_WifiScanCompleteHandler( ScanResult *pApList, void * inContext )
{
    char str[64] = {'\0'};
    pApList->ApList[0].ssid[10] = '\0';  // truncate first 10 char
    sprintf(str, "%s Wi-Fi\r\nScan AP:\r\nssid :%10s\r\npower:%10d", OLED_MFG_TEST_PREFIX,
             pApList->ApList[0].ssid, pApList->ApList[0].ApPower);
    mf_printf(str);
    scanap_done = true;
}

void micokit_ext_mfg_test(mico_Context_t *inContext)
{
  OSStatus err = kUnknownErr;
  char str[64] = {'\0'};
  char mac[6];
  
  int rgb_led_hue = 0;
  
  uint8_t dht11_ret = 0;
  uint8_t dht11_temp_data = 0;
  uint8_t dht11_hum_data = 0;
  
  int light_ret = 0;
  uint16_t light_sensor_data = 0;
  
  int infrared_ret = 0;
  uint16_t infrared_reflective_data = 0;
  
  int32_t bme280_temp = 0;
  uint32_t bme280_hum = 0;
  uint32_t bme280_press = 0;
  
  UNUSED_PARAMETER(inContext);
  
  mico_rtos_init_semaphore(&mfg_test_state_change_sem, 1); 
  err = MICOAddNotification( mico_notify_WIFI_SCAN_COMPLETED, (void *)mico_notify_WifiScanCompleteHandler );
  require_noerr( err, exit );
  
  while(1){
    switch(mfg_test_module_number){
    case 0:  // mfg mode start
      {
        sprintf(str, "%s\r\nStart:\r\n%s\r\n%s", "TEST MODE", "  next: Key2", "  prev: Key1");
        mf_printf(str);
        while(kNoErr != mico_rtos_get_semaphore(&mfg_test_state_change_sem, MICO_WAIT_FOREVER));
        break;
      }
    case 1:  // OLED
      {
        while(kNoErr != mico_rtos_get_semaphore(&mfg_test_state_change_sem, 0))
        {
          sprintf(str, "%s OLED\r\n", OLED_MFG_TEST_PREFIX);
          mf_printf(str);
          mico_thread_msleep(300);
          
          mf_printf(mfg_test_oled_test_string);
          mico_thread_msleep(300);
        }
        OLED_Clear();
        break;
      }
    case 2:  // RGB_LED
      {
        sprintf(str, "%s RGB LED\r\nBlink: \r\n      R=>G=>B", OLED_MFG_TEST_PREFIX);
        mf_printf(str);
        
        while(kNoErr != mico_rtos_get_semaphore(&mfg_test_state_change_sem, 0))
        {
          hsb2rgb_led_open(rgb_led_hue, 100, 50);
          rgb_led_hue += 120;
          if(rgb_led_hue >= 360){
            rgb_led_hue = 0;
          }
          mico_thread_msleep(300);
        }
        hsb2rgb_led_open(0, 0, 0);
        break;
      }
    case 3: // infrared sensor
      {
        while(kNoErr != mico_rtos_get_semaphore(&mfg_test_state_change_sem, 0))
        {
          infrared_ret = infrared_reflective_read(&infrared_reflective_data);
          if(0 == infrared_ret){ 
            sprintf(str, "%s Infrared\r\nInfrared: %d", OLED_MFG_TEST_PREFIX,
                    infrared_reflective_data);
            mf_printf(str);
          }
          mico_thread_msleep(300);
        }
        break;
      }
    case 4: // DC Motor
      {
        sprintf(str, "%s DC Motor\r\nRun:\r\n     on : 500ms\r\n     off: 500ms", OLED_MFG_TEST_PREFIX);
        mf_printf(str);
        
        while(kNoErr != mico_rtos_get_semaphore(&mfg_test_state_change_sem, 0))
        {
          dc_motor_set(1);
          mico_thread_msleep(500);
          dc_motor_set(0);
          mico_thread_msleep(500);
        }
        dc_motor_set(0);
        break;
      }
    case 5: // BME280
      {
        while(kNoErr != mico_rtos_get_semaphore(&mfg_test_state_change_sem, 0))
        {
          err = bme280_sensor_init();
          if(kNoErr != err){
            sprintf(str, "%s BME280\r\nMoule not found!", OLED_MFG_TEST_PREFIX);
            mf_printf(str);
            // goto next mdoule
            mico_thread_msleep(500);
            mfg_test_module_number = (mfg_test_module_number+1)%(MFG_TEST_MAX_MODULE_NUM+1);
            break;
          }
          else{
            mico_thread_msleep(500);
            err = bme280_data_readout(&bme280_temp, &bme280_press, &bme280_hum);
            if(kNoErr == err){
              sprintf(str, "%s BME280\r\nT: %3.1fC\r\nH: %3.1f%%\r\nP: %5.2fkPa", OLED_MFG_TEST_PREFIX,
                      (float)bme280_temp/100, (float)bme280_hum/1024, (float)bme280_press/1000);
              mf_printf(str);
            }
            else{
              sprintf(str, "%s BME280\r\nRead error!", OLED_MFG_TEST_PREFIX);
              mf_printf(str);
            }
          }
          mico_thread_msleep(500);
        }
        break;
      }
    case 6: // DHT11
      {
        while(kNoErr != mico_rtos_get_semaphore(&mfg_test_state_change_sem, 0))
        {
          dht11_ret = DHT11_Read_Data(&dht11_temp_data, &dht11_hum_data);
          if(0 == dht11_ret){
            sprintf(str, "%s DHT11\r\nT: %3.1fC\r\nH: %3.1f%%", OLED_MFG_TEST_PREFIX,
                    (float)dht11_temp_data, (float)dht11_hum_data);
            mf_printf(str);
          }
          mico_thread_sleep(1);   // DHT11 must >= 1s
        }
        break;
      }
    case 7:   // Light sensor
      {
        while(kNoErr != mico_rtos_get_semaphore(&mfg_test_state_change_sem, 0))
        {
          light_ret = light_sensor_read(&light_sensor_data);
          if(0 == light_ret){
            sprintf(str, "%s Light\r\nLight: %d", OLED_MFG_TEST_PREFIX,
                    light_sensor_data);
            mf_printf(str);
          }
          mico_thread_msleep(300);
        }
        break;
      }
    case 8: // wifi
      {
        wlan_get_mac_address(mac);
        sprintf(str, "%s Wi-Fi\r\nMAC:\r\n    %02X%02X%02X%02X%02X%02X", OLED_MFG_TEST_PREFIX,
                mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
        mf_printf(str);
        //mico_thread_msleep(500);
        
        scanap_done = false;
        micoWlanStartScan();
        while((!scanap_done) || (kNoErr != mico_rtos_get_semaphore(&mfg_test_state_change_sem, MICO_WAIT_FOREVER)));
        break;
      }
    default:
      goto exit;  // error
      break;
    }
  }
  
exit:
  mico_thread_sleep(MICO_NEVER_TIMEOUT);
}
