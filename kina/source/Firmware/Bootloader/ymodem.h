/**
* @file    lymodem.c 
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LYMODEM_H_
#define __LYMODEM_H_

/* Includes ------------------------------------------------------------------*/
#include "platform.h"
#include "Common.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define PACKET_SEQNO_INDEX      (1)
#define PACKET_SEQNO_COMP_INDEX (2)

#define PACKET_HEADER           (3)
#define PACKET_TRAILER          (2)
#define PACKET_OVERHEAD         (PACKET_HEADER + PACKET_TRAILER)
#define PACKET_SIZE             (128)
#define PACKET_1K_SIZE          (1024)

#define FILE_NAME_LENGTH        (256)
#define FILE_SIZE_LENGTH        (16)

#define SOH                     (0x01)  /* start of 128-byte data packet */
#define STX                     (0x02)  /* start of 1024-byte data packet */
#define EOT                     (0x04)  /* end of transmission */
#define ACK                     (0x06)  /* acknowledge */
#define NAK                     (0x15)  /* negative acknowledge */
#define CA                      (0x18)  /* two of these in succession aborts transfer */
#define CRC16                   (0x43)  /* 'C' == 0x43, request 16-bit CRC */

#define ABORT1                  (0x41)  /* 'A' == 0x41, abort by user */
#define ABORT2                  (0x61)  /* 'a' == 0x61, abort by user */

#define NAK_TIMEOUT             (100)
#define MAX_ERRORS              (40)

/* Exported functions ------------------------------------------------------- */
int32_t Ymodem_Receive (uint8_t *buf, mico_flash_t flash, uint32_t flashdestination, int32_t maxRecvSize);
uint8_t Ymodem_Transmit (mico_flash_t, uint32_t, const  uint8_t* , uint32_t );

#endif  /* __LYMODEM_H_ */


