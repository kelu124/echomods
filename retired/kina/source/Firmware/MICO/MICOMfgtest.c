#include "time.h"
#include "MicoPlatform.h"
#include "platform.h"
#include "MICODefine.h"
#include "MICOAppDefine.h"
#include "MICONotificationCenter.h"
#include "platform_config.h"

#ifdef USE_MiCOKit_EXT
  #include "micokit_ext.h"
  #define MFG_FUNCTION            3
#else
  #define MFG_FUNCTION            1
#endif

/* MFG test demo BEGIN */
extern int mfg_connect(char *ssid);
extern int mfg_scan(void);
extern void mfg_option(int use_udp, uint32_t remoteaddr);
extern char* system_lib_version(void);
extern void wlan_get_mac_address(char *mac);

static char cmd_str[64];
static void uartRecvMfg_thread(void *inContext);
static size_t _uart_get_one_packet(uint8_t* inBuf, int inBufLen);




void mf_printf(char *str)
{
  MicoUartSend( MFG_TEST, str, strlen(str));
}

static void mf_putc(char ch)
{
  MicoUartSend( MFG_TEST, &ch, 1);
}

static int get_line()
{
#define CNTLQ      0x11
#define CNTLS      0x13
#define DEL        0x7F
#define BACKSPACE  0x08
#define CR         0x0D
#define LF         0x0A
  
  char *p = cmd_str;
  int i = 0;
  char c;
  
  memset(cmd_str, 0, sizeof(cmd_str));
  while(1) {
    if( MicoUartRecv( MFG_TEST, p, 1, 100) != kNoErr)
      continue;
    
    mf_putc(*p);
    if (*p == BACKSPACE  ||  *p == DEL)  {
      if(i>0) {
        c = 0x20;
        mf_putc(c); 
        mf_putc(*p); 
        p--;
        i--; 
      }
      continue;
    }
    if(*p == CR || *p == LF) {
      *p = 0;
      return i;
    }
    
    p++;
    i++;
    if (i>sizeof(cmd_str))
      break;
  }
  
  return 0;
}


/**
* @brief  Display the Main Menu on HyperTerminal
* @param  None
* @retval None
*/
static char * ssid_get(void)
{
  char *cmd;
  int is_use_udp = 1;
  uint32_t remote_addr = 0xFFFFFFFF;
  
  while (1)  {                                 /* loop forever                */
    mf_printf ("\r\nMXCHIP_MFMODE> ");
    get_line();
    cmd = cmd_str;
    if (strncmp(cmd, "tcp ", 4) == 0) {
      mf_printf ("\r\n");
      remote_addr = inet_addr(cmd+4);
      if (remote_addr == 0)
        remote_addr = 0xffffffff;
      sprintf(cmd, "Use TCP send packet to 0x%X\r\n", (unsigned int)remote_addr);
      mf_printf (cmd);
      is_use_udp = 0;
    } else if (strncmp(cmd, "udp ", 4) == 0) {
      mf_printf ("\r\n");
      remote_addr = inet_addr(cmd+4);
      if (remote_addr == 0)
        remote_addr = 0xffffffff;
      sprintf(cmd, "Use UDP send packet to 0x%X\r\n", (unsigned int)remote_addr);
      mf_printf (cmd);
    }  else if (strncmp(cmd, "ssid ", 5) == 0) {
      mf_printf ("\r\n");
      return cmd+5;
    } else {
      mf_printf ("Please input as \"ssid <ssid_string>\"");
      continue;
    }
  }
  
  mfg_option(is_use_udp, remote_addr);
}

#if (MFG_FUNCTION == 1) 
void mico_mfg_test(mico_Context_t *inContex)
{
  char str[64];
  char mac[6];
  char *ssid;
  UNUSED_PARAMETER(inContex);
  mico_uart_config_t uart_config;
  volatile ring_buffer_t  rx_buffer;
  volatile uint8_t *      rx_data;
  
  rx_data = malloc(50);
  require(rx_data, exit);
  
  /* Initialize UART interface */
  uart_config.baud_rate    = 115200;
  uart_config.data_width   = DATA_WIDTH_8BIT;
  uart_config.parity       = NO_PARITY;
  uart_config.stop_bits    = STOP_BITS_1;
  uart_config.flow_control = FLOW_CONTROL_DISABLED;
  uart_config.flags = UART_WAKEUP_DISABLE;
  
  ring_buffer_init  ( (ring_buffer_t *)&rx_buffer, (uint8_t *)rx_data, 50 );
  MicoUartInitialize( MFG_TEST, &uart_config, (ring_buffer_t *)&rx_buffer );  
  
  sprintf(str, "Library Version: %s\r\n", system_lib_version());
  mf_printf(str);
  mf_printf("APP Version: ");
  memset(str, 0, sizeof(str));
  system_version(str, sizeof(str));
  mf_printf(str);
  mf_printf("\r\n");
  memset(str, 0, sizeof(str));
  wlan_driver_version(str, sizeof(str));
  mf_printf("Driver: ");
  mf_printf(str);
  mf_printf("\r\n");
  wlan_get_mac_address(mac);
  sprintf(str, "MAC: %02X-%02X-%02X-%02X-%02X-%02X\r\n",
          mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  mf_printf(str);
  
  mfg_scan();
  
  ssid = ssid_get();
  mfg_connect(ssid);
  
exit:
  mico_thread_sleep(MICO_NEVER_TIMEOUT);
}
#elif (MFG_FUNCTION == 2)
void mico_mfg_test(mico_Context_t *inContext)
{
  network_InitTypeDef_adv_st wNetConfig;
  int testCommandFd, scanFd;
  uint8_t *buf = NULL;
  int recvLength = -1;
  fd_set readfds;
  struct timeval_t t;
  struct sockaddr_t addr;
  socklen_t addrLen;
  mico_uart_config_t uart_config;
  volatile ring_buffer_t  rx_buffer;
  volatile uint8_t *       rx_data;
  OSStatus err;
  
  buf = malloc(1500);
  require_action(buf, exit, err = kNoMemoryErr);
  rx_data = malloc(2048);
  require_action(rx_data, exit, err = kNoMemoryErr);
  
  /* Connect to a predefined Wlan */
  memset( &wNetConfig, 0x0, sizeof(network_InitTypeDef_adv_st) );
  
  strncpy( (char*)wNetConfig.ap_info.ssid, "William Xu", maxSsidLen );
  wNetConfig.ap_info.security = SECURITY_TYPE_AUTO;
  memcpy( wNetConfig.key, "mx099555", maxKeyLen );
  wNetConfig.key_len = strlen( "mx099555" );
  wNetConfig.dhcpMode = DHCP_Client;
  
  wNetConfig.wifi_retry_interval = 100;
  micoWlanStartAdv(&wNetConfig);
  
  /* Initialize UART interface */
  uart_config.baud_rate    = 115200;
  uart_config.data_width   = DATA_WIDTH_8BIT;
  uart_config.parity       = NO_PARITY;
  uart_config.stop_bits    = STOP_BITS_1;
  uart_config.flow_control = FLOW_CONTROL_DISABLED;
  uart_config.flags = UART_WAKEUP_DISABLE;
  
  ring_buffer_init  ( (ring_buffer_t *)&rx_buffer, (uint8_t *)rx_data, 2048 );
  MicoUartInitialize( UART_FOR_APP, &uart_config, (ring_buffer_t *)&rx_buffer );
  err = mico_rtos_create_thread(NULL, MICO_APPLICATION_PRIORITY, "MFG UART Recv", uartRecvMfg_thread, 0x300, (void*)inContext );
  
  /* Initialize UDP interface */
  t.tv_sec = 5;
  t.tv_usec = 0;
  
  scanFd = socket(AF_INET, SOCK_DGRM, IPPROTO_UDP);
  require_action(IsValidSocket( scanFd ), exit, err = kNoResourcesErr );
  
  addr.s_port = 23230;
  addr.s_ip = INADDR_ANY;
  err = bind(scanFd, &addr, sizeof(addr));
  require_noerr(err, exit);
  
  testCommandFd = socket(AF_INET, SOCK_DGRM, IPPROTO_UDP);
  require_action(IsValidSocket( testCommandFd ), exit, err = kNoResourcesErr );
  
  addr.s_port = 23231;
  addr.s_ip = INADDR_ANY;
  err = bind(testCommandFd, &addr, sizeof(addr));
  require_noerr(err, exit);
  
  while(1) {
    /*Check status on erery sockets on bonjour query */
    FD_ZERO( &readfds );
    FD_SET( testCommandFd, &readfds );
    FD_SET( scanFd, &readfds );
    select( 1, &readfds, NULL, NULL, &t );
    
    /* Scan and return MAC address */ 
    if (FD_ISSET(scanFd, &readfds)) {
      recvLength = recvfrom(scanFd, buf, 1500, 0, &addr, &addrLen); 
      sendto(scanFd, inContext->micoStatus.mac, sizeof(inContext->micoStatus.mac), 0, &addr, addrLen);
    }
    
    /* Recv UDP data and send to COM */
    if (FD_ISSET(testCommandFd, &readfds)) {
      recvLength = recvfrom(testCommandFd, buf, 1500, 0, &addr, &addrLen); 
      MicoUartSend(UART_FOR_APP, buf, recvLength);
    }
  }
  
exit:
  if(buf) free(buf);  
}

#elif (MFG_FUNCTION == 3)   // MicoKit MFG TEST
void mico_mfg_test(mico_Context_t *inContext)
{
  micokit_ext_mfg_test(inContext);  // MicoKit-EXT board mfg test
}
#endif

void uartRecvMfg_thread(void *inContext)
{
  mico_Context_t *Context = inContext;
  int recvlen;
  uint8_t *inDataBuffer;
  
  inDataBuffer = malloc(500);
  require(inDataBuffer, exit);
  
  while(1) {
    recvlen = _uart_get_one_packet(inDataBuffer, 500);
    if (recvlen <= 0)
      continue; 
    else{
      /* if(......)   Should valid the UART input */
      Context->flashContentInRam.micoSystemConfig.configured = unConfigured;
      MICOUpdateConfiguration ( Context );
    }
  }
  
exit:
  if(inDataBuffer) free(inDataBuffer);
}


static size_t _uart_get_one_packet(uint8_t* inBuf, int inBufLen)
{
  
  int datalen;
  
  while(1) {
    if( MicoUartRecv( UART_FOR_APP, inBuf, inBufLen, 500) == kNoErr){
      return inBufLen;
    }
    else{
      datalen = MicoUartGetLengthInBuffer( UART_FOR_APP );
      if(datalen){
        MicoUartRecv(UART_FOR_APP, inBuf, datalen, 500);
        return datalen;
      }
    }
    
  }
  
}


/* MFG test demo END */














