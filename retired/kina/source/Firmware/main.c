#include "MICO.h"
#include "MICOSystemMonitor.h"
#include "MICONotificationCenter.h"
#include "adc.h"

#define main_log(M, ...) custom_log("main", M, ##__VA_ARGS__)

static mico_timer_t wdgReloadTimer;
static mico_Context_t context;
static mico_system_monitor_t micoMonitor;
static mico_semaphore_t networkIsReady_semaphore;

static uint16_t udpBuffer[Adc_BufferLength];

static void WdgReloadTimer_h(void* arg)
{
  (void)(arg);
  MICOUpdateSystemMonitor(&micoMonitor, APPLICATION_WATCHDOG_TIMEOUT_SECONDS*1000);
}

static void micoNotify_WifiStatus_h(WiFiEvent event, mico_Context_t * const inContext)
{
  if (event == NOTIFY_STATION_UP) mico_rtos_set_semaphore(&networkIsReady_semaphore);
}

void micoNotify_ConnectFailed_h(OSStatus err, mico_Context_t * const inContext)
{
}

void micoNotify_WlanFatalErr_h(mico_Context_t * const inContext)
{
  MicoSystemReboot();
}

void micoNotify_StackOverflowErr_h(char *taskname, mico_Context_t * const inContext)
{
  MicoSystemReboot(); 
}

int application_start( void )
{
  MICOInitNotificationCenter(&context);
  MICOAddNotification(mico_notify_WIFI_CONNECT_FAILED, (void *)micoNotify_ConnectFailed_h);
  MICOAddNotification(mico_notify_WIFI_Fatal_ERROR, (void *)micoNotify_WlanFatalErr_h);
  MICOAddNotification(mico_notify_Stack_Overflow_ERROR, (void *)micoNotify_StackOverflowErr_h);
  MICOAddNotification(mico_notify_WIFI_STATUS_CHANGED, (void *)micoNotify_WifiStatus_h);
  
  MicoInit();
  Adc_Init();
  
  MICORegisterSystemMonitor(&micoMonitor, APPLICATION_WATCHDOG_TIMEOUT_SECONDS*1000);
  mico_init_timer(&wdgReloadTimer, APPLICATION_WATCHDOG_TIMEOUT_SECONDS*1000/2, WdgReloadTimer_h, NULL);
  mico_start_timer(&wdgReloadTimer);
  
  mico_rtos_init_semaphore(&networkIsReady_semaphore, 1);
  
  // Config for WiFI connection
  network_InitTypeDef_adv_st wNetConfig = 
  {
    .ap_info = 
    {
      .ssid = "HomeNetwork",
      .channel = 0,
      .security = SECURITY_TYPE_AUTO
    },
    .key = "0000000000000000",
    .key_len = 16,
    .dhcpMode = DHCP_Client,
    .wifi_retry_interval = 100
  };
  
  // Connect to a router
  micoWlanStartAdv(&wNetConfig);
  
  // Wait until connection is ready
  if (mico_rtos_get_semaphore(&networkIsReady_semaphore, 30000) != kNoErr)
  {
    main_log("Connection to WiFi AP took too long");
  }
  
  else
  {
    // Create UDP socket
    int fd = socket(AF_INET, SOCK_DGRM, IPPROTO_UDP);
    
    // Set parameters of UDP server
    struct sockaddr_t addr;
    addr.s_ip = 0xC0A80103;
    addr.s_port = 6666;
    
    Adc_Start();
   
    while(1)
    {
      // Get data from the ADC queue
      if (mico_rtos_pop_from_queue(&Adc_Data_queue, udpBuffer, 10000) == kNoErr)
      {
        // Send data to UDP server
        sendto(fd, udpBuffer, sizeof(udpBuffer), 0, &addr, sizeof(addr));
      }
    }
  }
  
  mico_rtos_delete_thread(NULL);
  return 0;
}