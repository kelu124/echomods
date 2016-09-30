/**
******************************************************************************
* @file    MDNSUtils.h 
* @author  William Xu
* @version V1.0.0
* @date    05-May-2014
* @brief   This header contains function prototypes called by mdns protocol 
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


#ifndef __MDNS_H
#define __MDNS_H

#include "Common.h"
#include "MICO.h"

/**************************************************************************************************************
 * INCLUDES
 **************************************************************************************************************/

#define DNS_MESSAGE_IS_A_RESPONSE           0x8000
#define DNS_MESSAGE_OPCODE                  0x7800
#define DNS_MESSAGE_AUTHORITATIVE           0x0400
#define DNS_MESSAGE_TRUNCATION              0x0200
#define DNS_MESSAGE_RECURSION_DESIRED       0x0100
#define DNS_MESSAGE_RECURSION_AVAILABLE     0x0080
#define DNS_MESSAGE_RESPONSE_CODE           0x000F

typedef enum
{
    DNS_NO_ERROR        = 0,
    DNS_FORMAT_ERROR    = 1,
    DNS_SERVER_FAILURE  = 2,
    DNS_NAME_ERROR      = 3,
    DNS_NOT_IMPLEMENTED = 4,
    DNS_REFUSED         = 5
} dns_message_response_code_t;

typedef enum
{
    RR_TYPE_A      = 1,     // A - Host Address
    RR_TYPE_NS     = 2,
    RR_TYPE_MD     = 3,
    RR_TYPE_MF     = 4,
    RR_TYPE_CNAME  = 5,
    RR_TYPE_SOA    = 6,
    RR_TYPE_MB     = 7,
    RR_TYPE_MG     = 8,
    RR_TYPE_MR     = 9,
    RR_TYPE_NULL   = 10,
    RR_TYPE_WKS    = 11,
    RR_TYPE_PTR    = 12,    // PTR - Domain Name pointer
    RR_TYPE_HINFO  = 13,    // HINFO - Host Information
    RR_TYPE_MINFO  = 14,
    RR_TYPE_MX     = 15,
    RR_TYPE_TXT    = 16,
    RR_TYPE_SRV    = 33,    // SRV - Service Location Record
    RR_QTYPE_AXFR  = 252,
    RR_QTYPE_MAILB = 253,
    RR_QTYPE_AILA  = 254,
    RR_QTYPE_ANY   = 255
} dns_resource_record_type_t;

typedef enum
{
    RR_CLASS_IN  = 1,
    RR_CLASS_CS  = 2,
    RR_CLASS_CH  = 3,
    RR_CLASS_HS  = 4,
    RR_CLASS_ALL = 255
} dns_resource_record_class_t;

#define RR_CACHE_FLUSH   0x8000

/**************************************************************************************************************
 * STRUCTURES
 **************************************************************************************************************/

typedef struct
{
  uint8_t* start_of_name;
  uint8_t* start_of_packet; // Used for compressed names;
} dns_name_t;

typedef struct
{
  uint16_t id;
  uint16_t flags;
  uint16_t question_count;
  uint16_t answer_count;
  uint16_t name_server_count;
  uint16_t additional_record_count;
} dns_message_header_t;

typedef struct
{
    dns_message_header_t* header; // Also used as start of packet for compressed names
    uint8_t* iter;
    uint8_t* end;
} dns_message_iterator_t;

typedef struct
{
  uint16_t question_type;
  uint16_t question_class;
} dns_question_t;

typedef struct
{
  uint16_t record_type;
  uint16_t record_class;
  uint32_t ttl;
  uint16_t rd_length;
  dns_message_iterator_t rdata;
} dns_record_t;


typedef struct
{
  //char *name;
  char *service_name;
  char *host_name;
  char *instance_name;
  char *txt_record;
  uint16_t service_port;
  WiFi_Interface interface;
} bonjour_init_t;

void bonjour_service_init(bonjour_init_t init);

void bonjour_update_txt_record(char *txt_record);

int start_bonjour_service(void);

void suspend_bonjour_service(bool state);

void stop_bonjour_service(void);



#endif
