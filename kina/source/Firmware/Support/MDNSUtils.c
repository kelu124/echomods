/**
******************************************************************************
* @file    MDNSUtils.c
* @author  William Xu
* @version V1.0.0
* @date    05-May-2014
* @brief   This header contains function called by mdns protocol 
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

#include "MDNSUtils.h"
#include "SocketUtils.h"

static int mDNS_fd = -1;

typedef struct
{
  char* hostname;
  char* instance_name;
  char* service_name;
  char* txt_att;
  char	instance_name_suffix[4]; // This variable should only be modified by the DNS-SD library
  uint32_t  ttl;
  uint16_t  port;
  bool  anounce;
} dns_sd_service_record_t;

static WiFi_Interface _interface;


#define APP_Available_Offset               0
#define Support_TLV_Config_Offset          2

#define Problem_Detected_Offset            0
#define Not_Configured_Offset              1


#define MFi_SERVICE_QUERY_NAME             "_services._dns-sd._udp.local."


static bool _suspend_MFi_bonjour;
static int _bonjour_announce_time = 0;
static int _bonjour_announce = 0;
static bool _bonjour_should_stop = false;


//#define  debug_out 

//#ifdef debug_out
//#define  _debug_out debug_out
//#else
#define _debug_out(format, ...) do {;}while(0)

#define mdns_utils_log(M, ...) custom_log("mDNS Utils", M, ##__VA_ARGS__)
#define mdns_utils_log_trace() custom_log_trace("mDNS Utils")
//#endif

static dns_sd_service_record_t*   available_services	= NULL;
static uint8_t	available_service_count;

static int dns_get_next_question( dns_message_iterator_t* iter, dns_question_t* q, dns_name_t* name );
static int dns_compare_name_to_string( dns_name_t* name, const char* string, const char* fun, const int line );
static int dns_create_message( dns_message_iterator_t* message, uint16_t size );
static void dns_write_header( dns_message_iterator_t* iter, uint16_t id, uint16_t flags, uint16_t question_count, uint16_t answer_count, uint16_t authorative_count );
static void dns_write_record( dns_message_iterator_t* iter, const char* name, uint16_t record_class, uint16_t record_type, uint32_t ttl, uint8_t* rdata );
static void mdns_send_message(int fd, dns_message_iterator_t* message );
static void dns_free_message( dns_message_iterator_t* message );
static void mdns_process_query(int fd, dns_name_t* name, dns_question_t* question, dns_message_iterator_t* source );
static void dns_write_record( dns_message_iterator_t* iter, const char* name, uint16_t record_class, uint16_t record_type, uint32_t ttl, uint8_t* rdata );
static void dns_write_uint16( dns_message_iterator_t* iter, uint16_t data );
static void dns_write_uint32( dns_message_iterator_t* iter, uint32_t data );
static void dns_write_bytes( dns_message_iterator_t* iter, uint8_t* data, uint16_t length );
static uint16_t dns_read_uint16( dns_message_iterator_t* iter );
static void dns_skip_name( dns_message_iterator_t* iter );
static void dns_write_name( dns_message_iterator_t* iter, const char* src );

static mico_mutex_t bonjour_mutex = NULL;
static mico_thread_t mfi_bonjour_thread_handler;
static void _bonjour_thread(void *arg);

static char *__strdup(char *src)
{
  int len;
  char *dst;
  
  if (src == NULL)
    return NULL;
  
  if (src[0] == 0)
    return NULL;
  
  len = strlen(src) + 1;
  dst = (char*)malloc(len);
  if (dst) 
    memcpy(dst, src, len);
  return dst;
}

void process_dns_questions(int fd, dns_message_iterator_t* iter )
{
  dns_name_t name;
  dns_question_t question;
  dns_message_iterator_t response;
  IPStatusTypedef para;
  int a = 0;
  int question_processed;
  uint32_t myip;
  
  micoWlanGetIPStatus(&para, _interface);
  myip = htonl(inet_addr(para.ip));
  if(myip == 0) {
    _debug_out("UDP multicast test: IP error.\r\n");
    return;
  }
  
  memset( &response, 0, sizeof(dns_message_iterator_t) );
  
  for ( a = 0; a < htons(iter->header->question_count); ++a )
  {
    if (iter->iter > iter->end)
      break;
    if(dns_get_next_question( iter, &question, &name )==0)
      break;
    question_processed = 0;
    switch ( question.question_type ){
    case RR_TYPE_PTR:
      if ( available_services != NULL ){
        // Check if its a query for all available services  
        if ( dns_compare_name_to_string( &name, MFi_SERVICE_QUERY_NAME, __FUNCTION__, __LINE__ ) ){
          int b = 0;
          _debug_out("UDP multicast test: Recv a SERVICE QUERY request.\r\n");
          if(dns_create_message( &response, 512 )) {
            dns_write_header(&response, iter->header->id, 0x8400, 0, available_service_count, 0 );          
            for ( b = 0; b < available_service_count; ++b ){
              dns_write_record( &response, MFi_SERVICE_QUERY_NAME, RR_CLASS_IN, RR_TYPE_PTR, 1500, (uint8_t*) available_services[b].service_name );
            }
            mdns_send_message(fd, &response );
            dns_free_message( &response );
            question_processed = 1;
          }
        }
        // else check if its one of our records
        else {
          int b = 0;
          for ( b = 0; b < available_service_count; ++b ){
            //printf("UDP multicast test: Recv a SERVICE Detail request: %s.\r\n", name);
            if ( dns_compare_name_to_string( &name, available_services[b].service_name, __FUNCTION__, __LINE__ )){
              // Send the PTR, TXT, SRV and A records
              if(dns_create_message( &response, 512 )){
                dns_write_header( &response, iter->header->id, 0x8400, 0, 4, 0 );
                //dns_write_record( &response, MFi_SERVICE_QUERY_NAME, RR_CLASS_IN, RR_TYPE_PTR, 1500, (u8*) available_services[b].service_name );
                dns_write_record( &response, available_services[b].service_name, RR_CLASS_IN, RR_TYPE_PTR, 1500, (uint8_t*) available_services[b].instance_name );
                dns_write_record( &response, available_services[b].instance_name, RR_CACHE_FLUSH|RR_CLASS_IN, RR_TYPE_TXT, 1500, (uint8_t*) available_services[b].txt_att );
                dns_write_record( &response, available_services[b].instance_name, RR_CACHE_FLUSH|RR_CLASS_IN, RR_TYPE_SRV, 1500, (uint8_t*) &available_services[b]);
                dns_write_record( &response, available_services[b].hostname, RR_CACHE_FLUSH|RR_CLASS_IN, RR_TYPE_A, 1500, (uint8_t*) &myip);
                mdns_send_message(fd, &response );
                dns_free_message( &response );
                question_processed = 1;
              }
              else{
                _debug_out("UDP multicast test: Send error.\r\n");
              }
            }
          }
        }
      }
      break;
    }
    if (!question_processed ){
      _debug_out("UDP multicast test: Recv a mDNS request.\r\n");
      mdns_process_query(fd, &name, &question, iter);
    }
  }
}

static void mdns_process_query(int fd, dns_name_t* name, 
                               dns_question_t* question, dns_message_iterator_t* source )
{
  dns_message_iterator_t response;
  IPStatusTypedef para;
  uint32_t myip;
  
  micoWlanGetIPStatus(&para, _interface);
  myip = htonl(inet_addr(para.ip));
  
  memset( &response, 0, sizeof(dns_message_iterator_t) );
  
  switch ( question->question_type )
  {
  case RR_QTYPE_ANY:
  case RR_TYPE_A:
    if ( dns_compare_name_to_string( name, available_services->hostname, __FUNCTION__, __LINE__) ){				
      _debug_out("UDP multicast test: Recv RR_TYPE_A.\r\n");
      if(dns_create_message( &response, 256 )){
        dns_write_header( &response, source->header->id, 0x8400, 0, 1, 0 );
        dns_write_record( &response, available_services->hostname, RR_CLASS_IN | RR_CACHE_FLUSH, RR_TYPE_A, 300, (uint8_t *)&myip);
        mdns_send_message(fd, &response );
        dns_free_message( &response );
        return;
      }
    }    
  default:
    _debug_out("UDP multicast test: Request not support type: %d.---------------------\r\n", question->question_type);
  }
}


static int dns_get_next_question( dns_message_iterator_t* iter, dns_question_t* q, dns_name_t* name )
{
  // Set the name pointers and then skip it
  name->start_of_name   = (uint8_t*) iter->iter;
  name->start_of_packet = (uint8_t*) iter->header;
  dns_skip_name( iter );
  if (iter->iter > iter->end)
    return 0;
  
  // Read the type and class
  q->question_type  = dns_read_uint16( iter );
  q->question_class = dns_read_uint16( iter );
  return 1;
}

static int dns_compare_name_to_string( dns_name_t* name, const char* string, const char* fun, int line )
{
  uint8_t section_length;
  int finished = 0;
  int result   = 1;
  uint8_t* buffer 	  = name->start_of_name;
  _debug_out("UDP multicast test: CMP called by %s@%d.\r\n", fun, line );
  char *temp;
  
  while ( !finished )
  {
    // Check if the name is compressed. If so, find the uncompressed version
    while ( *buffer & 0xC0 )
    {
      uint16_t offset = ( *buffer++ ) << 8;
      offset += *buffer;
      offset &= 0x3FFF;
      buffer = name->start_of_packet + offset;
      _debug_out("UDP multicast test: Recv a compressed name.\r\n");
    }
    
    // Compare section
    section_length = *( buffer++ );
    temp = malloc(section_length+1);
    temp[section_length] = 0;
    memcpy(temp, buffer, section_length );
    _debug_out("UDP multicast test: Recv a name: %s.\r\n", temp);
    free(temp);
    if ( strncmp( (char*) buffer, string, section_length ) )
    {
      result	 = 0;
      finished = 1;
    }
    string += section_length + 1;
    buffer += section_length;
    
    // Check if we've finished comparing
    if ( *buffer == 0 || *string == 0 )
    {
      finished = 1;
      // Check if one of the strings has more data
      if ( *buffer != 0 || *string != 0 )
      {
        result = 0;
      }
    }
  }
  
  return result;
}

static int dns_create_message( dns_message_iterator_t* message, uint16_t size )
{
  message->header = (dns_message_header_t*) malloc( size );
  if ( message->header == NULL )
  {
    return 0;
  }
  
  message->iter = (uint8_t *) message->header + sizeof(dns_message_header_t);
  return 1;
}

static void dns_free_message( dns_message_iterator_t* message )
{
  free(message->header);
  message->header = NULL;
}

static void dns_write_string( dns_message_iterator_t* iter, const char* src )
{
  uint8_t* segment_length_pointer;
  uint8_t  segment_length;
  
  while ( *src != 0 && *src != 0xC0)
  {
    /* Remember where we need to store the segment length and reset the counter*/
    segment_length_pointer = iter->iter++;
    segment_length = 0;
    
    /* Copy bytes until '.' or end of string*/
    while ( *src != '.' && *src != 0 && *src != 0xC0)
    {
      if (*src == '/')
        src++; // skip '/'
      
      *iter->iter++ = *src++;
      ++segment_length;
    }
    
    /* Store the length of the segment*/
    *segment_length_pointer = segment_length;
    
    /* Check if we stopped because of a '.', if so, skip it*/
    if ( *src == '.' )
    {
      ++src;
    }
    
  }
  
  if (*src == 0xC0) { // compress name
    *iter->iter++ = *src++;
    *iter->iter++ = *src++;
  } else {
    /* Add the ending null */
    *iter->iter++ = 0;
  }
}


static void dns_write_header( dns_message_iterator_t* iter, uint16_t id, uint16_t flags, uint16_t question_count, uint16_t answer_count, uint16_t authorative_count )
{
  memset( iter->header, 0, sizeof(dns_message_header_t) );
  iter->header->id				= htons(id);
  iter->header->flags 			= htons(flags);
  iter->header->question_count	= htons(question_count);
  iter->header->name_server_count = htons(authorative_count);
  iter->header->answer_count		= htons(answer_count);
}


static void dns_write_record( dns_message_iterator_t* iter, const char* name, uint16_t record_class, uint16_t record_type, uint32_t ttl, uint8_t* rdata )
{
  uint8_t* rd_length;
  uint8_t* temp_ptr;
  
  /* Write the name, type, class, TTL*/
  dns_write_name	( iter, name );
  dns_write_uint16( iter, record_type );
  dns_write_uint16( iter, record_class );
  dns_write_uint32( iter, ttl );
  
  /* Keep track of where we store the rdata length*/
  rd_length	= iter->iter;
  iter->iter += 2;
  temp_ptr	= iter->iter;
  
  switch ( record_type )
  {
  case RR_TYPE_A:
    dns_write_bytes( iter, rdata, 4 );
    break;
    
  case RR_TYPE_PTR:
  case RR_TYPE_TXT:
    dns_write_name( iter, (const char*) rdata );
    break;
    
  case RR_TYPE_SRV:
    /* Set priority and weight to 0*/
    dns_write_uint16( iter, 0 );
    dns_write_uint16( iter, 0 );
    
    /* Write the port*/
    dns_write_uint16( iter, ( (dns_sd_service_record_t*) rdata )->port );
    
    /* Write the hostname*/
    dns_write_string( iter, ( (dns_sd_service_record_t*) rdata )->hostname );
    break;
  default:
    break;
  }
  // Write the rdata length
  rd_length[0] = ( iter->iter - temp_ptr ) >> 8;
  rd_length[1] = ( iter->iter - temp_ptr ) & 0xFF;
}

static void mdns_send_message(int fd, dns_message_iterator_t* message )
{
  struct sockaddr_t addr;
  if(_suspend_MFi_bonjour == true)
    return;
  
  addr.s_ip = inet_addr("224.0.0.251");
  addr.s_port = 5353;
  _debug_out("UDP multicast test: Send a mDNS respond!+++++++++++++++++++++++++++\r\n");
  sendto(fd, message->header, message->iter - (uint8_t*)message->header, 0, &addr, sizeof(addr));
  addr.s_ip = inet_addr("255.255.255.255");
  addr.s_port = 5353;
  sendto(fd, message->header, message->iter - (uint8_t*)message->header, 0, &addr, sizeof(addr));
}

static void dns_write_uint16( dns_message_iterator_t* iter, uint16_t data )
{
  // We cannot assume the u8 alignment of iter->iter so we can't just typecast and assign
  iter->iter[0] = data >> 8;
  iter->iter[1] = data & 0xFF;
  iter->iter += 2;
}

static void dns_write_uint32( dns_message_iterator_t* iter, uint32_t data )
{
  iter->iter[0] = data >> 24;
  iter->iter[1] = data >> 16;
  iter->iter[2] = data >> 8;
  iter->iter[3] = data & 0xFF;
  iter->iter += 4;
}

static void dns_write_bytes( dns_message_iterator_t* iter, uint8_t* data, uint16_t length )
{
  int a = 0;
  
  for ( a = 0; a < length; ++a )
  {
    iter->iter[a] = data[a];
  }
  iter->iter += length;
}

static uint16_t dns_read_uint16( dns_message_iterator_t* iter )
{
  uint16_t temp = (uint16_t) ( *iter->iter++ ) << 8;
  temp += (uint16_t) ( *iter->iter++ );
  return temp;
}

static void dns_skip_name( dns_message_iterator_t* iter )
{
  while ( *iter->iter != 0 )
  {
    // Check if the name is compressed
    if ( *iter->iter & 0xC0 )
    {
      iter->iter += 1; // Normally this should be 2, but we have a ++ outside the while loop
      break;
    }
    else
    {
      iter->iter += (uint32_t) *iter->iter + 1;
    }
    if (iter->iter > iter->end)
      break;
  }
  // Skip the null u8
  ++iter->iter;
}

static void dns_write_name( dns_message_iterator_t* iter, const char* src )
{
  dns_write_string( iter, src );
}


void bonjour_service_init(bonjour_init_t init)
{
  int len;
  IPStatusTypedef para;

  _interface = init.interface;

  if(bonjour_mutex == NULL)
    mico_rtos_init_mutex( &bonjour_mutex );

  mico_rtos_lock_mutex( &bonjour_mutex );
  if(available_services) {
    //suspend_bonjour_service(ENABLE);
    if(available_services->service_name)  free(available_services->service_name);
    if(available_services->hostname)  free(available_services->hostname);
    if(available_services->instance_name)  free(available_services->instance_name);
    if(available_services->txt_att)  free(available_services->txt_att);
    free(available_services);
  }

  micoWlanGetIPStatus(&para, _interface);

  available_service_count = 1;
  available_services = (void *)malloc(sizeof(dns_sd_service_record_t) * 1);
  memset(available_services, 0x0, sizeof(dns_sd_service_record_t) * 1);

  available_services->service_name = (char*)__strdup(init.service_name);

  available_services->hostname = (char*)__strdup(init.host_name);

  len = strlen(init.instance_name);
  available_services->instance_name = (char*)malloc(len+3);//// 0xc00c+\0
  memcpy(available_services->instance_name, init.instance_name, len);
  available_services->instance_name[len]= 0xc0;
  available_services->instance_name[len+1]= 0x0c;
  available_services->instance_name[len+2]= 0;
  
  available_services->txt_att = (char*)__strdup(init.txt_record);

  available_services->port = init.service_port;
  mico_rtos_unlock_mutex( &bonjour_mutex );
}

void bonjour_update_txt_record(char *txt_record)
{
  
  mico_rtos_lock_mutex( &bonjour_mutex );
  if(available_services->txt_att)  free(available_services->txt_att);
  
  available_services->txt_att = (char*)__strdup(txt_record);

  _bonjour_announce = 1;
  mico_rtos_unlock_mutex( &bonjour_mutex );

}

void mfi_mdns_handler(int fd, uint8_t* pkt, int pkt_len)
{

  dns_message_iterator_t iter;
  
  iter.header = (dns_message_header_t*) pkt;
  iter.iter   = (uint8_t*) iter.header + sizeof(dns_message_header_t);
  iter.end = pkt+pkt_len;
  
  // Check if the message is a response (otherwise its a query)
  if ( ntohs(iter.header->flags) & DNS_MESSAGE_IS_A_RESPONSE )
  {
  }
  else
  {
    process_dns_questions(fd, &iter );
  }
}

void mfi_bonjour_send(int fd)
{
  dns_message_iterator_t response;
  uint32_t myip;
  IPStatusTypedef para;
  micoWlanGetIPStatus(&para, _interface);
  myip = htonl(inet_addr(para.ip));
  if(myip == 0) return;
  int b = 0;
    
  if(dns_create_message( &response, 512 )) {
    dns_write_header(&response, 0x0, 0x8400, 0, available_service_count, 0 );          
    for ( b = 0; b < available_service_count; ++b ){
      dns_write_record( &response, MFi_SERVICE_QUERY_NAME, RR_CLASS_IN, RR_TYPE_PTR, 1500, (uint8_t*) available_services[b].service_name );
    }
    mdns_send_message(fd, &response );
    dns_free_message( &response );
  }

  for ( b = 0; b < available_service_count; ++b ){
      if(dns_create_message( &response, 512 )){
        dns_write_header( &response, 0x0, 0x8400, 0, 4, 0 );
        dns_write_record( &response, available_services[b].service_name, RR_CLASS_IN, RR_TYPE_PTR, 1500, (uint8_t*) available_services[b].instance_name );
        dns_write_record( &response, available_services[b].instance_name, RR_CACHE_FLUSH|RR_CLASS_IN, RR_TYPE_TXT, 1500, (uint8_t*) available_services[b].txt_att );
        dns_write_record( &response, available_services[b].instance_name, RR_CACHE_FLUSH|RR_CLASS_IN, RR_TYPE_SRV, 1500, (uint8_t*) &available_services[b]);
        dns_write_record( &response, available_services[b].hostname, RR_CACHE_FLUSH|RR_CLASS_IN, RR_TYPE_A, 1500, (uint8_t*) &myip);
        mdns_send_message(fd, &response );
        dns_free_message( &response );
      }
  }
}


void mfi_bonjour_remove_record(int fd)
{
  dns_message_iterator_t response;
  uint32_t myip;
  IPStatusTypedef para;
  micoWlanGetIPStatus(&para, _interface);
  myip = htonl(inet_addr(para.ip));
  int b = 0;

  for ( b = 0; b < available_service_count; ++b ){
    if(dns_create_message( &response, 512 )){
      dns_write_header( &response, 0x0, 0x8400, 0, 4, 0 );
      dns_write_record( &response, available_services[b].service_name, RR_CLASS_IN, RR_TYPE_PTR, 0, (uint8_t*) available_services[b].instance_name );
      dns_write_record( &response, available_services[b].instance_name, RR_CACHE_FLUSH|RR_CLASS_IN, RR_TYPE_TXT, 0, (uint8_t*) available_services[b].txt_att );
      dns_write_record( &response, available_services[b].instance_name, RR_CACHE_FLUSH|RR_CLASS_IN, RR_TYPE_SRV, 0, (uint8_t*) &available_services[b]);
      dns_write_record( &response, available_services[b].hostname, RR_CACHE_FLUSH|RR_CLASS_IN, RR_TYPE_A, 0, (uint8_t*) &myip);
      mdns_send_message(fd, &response );
      mico_thread_msleep(20);
      mdns_send_message(fd, &response );
      dns_free_message( &response );
    }
  }
}

int start_bonjour_service(void)
{
  return mico_rtos_create_thread(&mfi_bonjour_thread_handler, MICO_APPLICATION_PRIORITY, "Bonjour", _bonjour_thread, 0x500, NULL );
}

void stop_bonjour_service( void )
{
  suspend_bonjour_service( true );
  _bonjour_should_stop = true;
  mico_thread_msleep( 1200 );

  available_service_count = 0;
  
  if(available_services) {
    if(available_services->service_name)  free(available_services->service_name);
    if(available_services->hostname)  free(available_services->hostname);
    if(available_services->instance_name)  free(available_services->instance_name);
    if(available_services->txt_att)  free(available_services->txt_att);
    free(available_services);
    available_services = NULL;
  }
  
  if(bonjour_mutex != NULL){
    mico_rtos_deinit_mutex( &bonjour_mutex );
    bonjour_mutex = NULL;
  }
}

void suspend_bonjour_service(bool state)
{
  mico_rtos_lock_mutex( &bonjour_mutex );
  if(state == true){
    _bonjour_announce = 0;
    mfi_bonjour_remove_record(mDNS_fd);
  }
  else{
    _bonjour_announce = 1;
    _bonjour_announce_time = 0;
  }
  mico_rtos_unlock_mutex( &bonjour_mutex );
}

void _bonjour_thread(void *arg)
{
  uint8_t *buf = NULL;
  int con = -1;
  fd_set readfds;
  struct timeval_t t;
  struct sockaddr_t addr;
  socklen_t addrLen;
  uint32_t opt;
  (void)arg;
  OSStatus err;
  
  buf = malloc(1500);
  
  t.tv_sec = 1;
  t.tv_usec = 0;
  
  mDNS_fd = socket(AF_INET, SOCK_DGRM, IPPROTO_UDP);
  require_action(IsValidSocket( mDNS_fd ), exit, err = kNoResourcesErr );
  opt = 0xE00000FB; //"224.0.0.251"
  setsockopt(mDNS_fd, SOL_SOCKET, IP_ADD_MEMBERSHIP, &opt, 4);
  addr.s_port = 5353;
  addr.s_ip = INADDR_ANY;
  err = bind(mDNS_fd, &addr, sizeof(addr));
  require_noerr(err, exit);

  _bonjour_announce = 1;
  
  while(1) {
    /*Send bonjour info when wifi is connected */
    if(_bonjour_announce){
      mico_rtos_lock_mutex( &bonjour_mutex );
      mfi_bonjour_send(mDNS_fd);
     
      _bonjour_announce_time ++;
      if(_bonjour_announce_time > 1){
        _bonjour_announce_time = 0;
        _bonjour_announce = 0;
      }
      mico_rtos_unlock_mutex( &bonjour_mutex );
    }
    
    if( _bonjour_should_stop == true ){
      _bonjour_should_stop = false;
      goto exit;
    }

    /*Check status on erery sockets on bonjour query */
    FD_ZERO(&readfds);
    FD_SET(mDNS_fd, &readfds);
    select(mDNS_fd+1, &readfds, NULL, NULL, &t);
    
    /*Read data from udp and send data back */ 
    if (FD_ISSET(mDNS_fd, &readfds)) {
      con = recvfrom(mDNS_fd, buf, 1500, 0, &addr, &addrLen); 
      mico_rtos_lock_mutex( &bonjour_mutex );
      mfi_mdns_handler(mDNS_fd, (uint8_t *)buf, con);
      mico_rtos_unlock_mutex( &bonjour_mutex );
    }
  }
exit:
  mdns_utils_log("Exit: mDNS thread exit with err = %d", err);
  SocketClose( &mDNS_fd );
  if(buf) free(buf);
  mico_rtos_delete_thread(NULL);
}



