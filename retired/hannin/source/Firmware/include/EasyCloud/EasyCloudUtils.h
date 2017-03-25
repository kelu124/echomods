/**
  ******************************************************************************
  * @file    EasyCloudUtils.h 
  * @author  Eshen.Wang
  * @version V1.0.0
  * @date    29-Nov-2014
  * @brief   This header contains function prototypes for some utils functions.
  * @NOTE    These are support functions not supplied in MICO support, could be
  *          removed if MICO has these utils.
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

#ifndef __EASYCLOUD_UTILS_H__
#define __EASYCLOUD_UTILS_H__

//#include <stdarg.h>
#include "Common.h"

//#include "HTTPUtils.h"
#include "URLUtils.h"
#include "MicoPlatform.h"


// ============================= from HTTP utils ===============================
#define ECS_kHTTPPostMethod     "POST"
#define ECS_kHTTPGetMethod      "GET"

      // Status-Code    =
      //       "100"  ; Section 10.1.1: Continue
      //     | "101"  ; Section 10.1.2: Switching Protocols
      //     | "200"  ; Section 10.2.1: OK
      //     | "201"  ; Section 10.2.2: Created
      //     | "202"  ; Section 10.2.3: Accepted
      //     | "203"  ; Section 10.2.4: Non-Authoritative Information
      //     | "204"  ; Section 10.2.5: No Content
      //     | "205"  ; Section 10.2.6: Reset Content
      //     | "206"  ; Section 10.2.7: Partial Content
      //     | "207"  ; ???           : Multi-Status
      //     | "300"  ; Section 10.3.1: Multiple Choices
      //     | "301"  ; Section 10.3.2: Moved Permanently
      //     | "302"  ; Section 10.3.3: Found
      //     | "303"  ; Section 10.3.4: See Other
      //     | "304"  ; Section 10.3.5: Not Modified
      //     | "305"  ; Section 10.3.6: Use Proxy
      //     | "307"  ; Section 10.3.8: Temporary Redirect
      //     | "400"  ; Section 10.4.1: Bad Request
      //     | "401"  ; Section 10.4.2: Unauthorized
      //     | "402"  ; Section 10.4.3: Payment Required
      //     | "403"  ; Section 10.4.4: Forbidden
      //     | "404"  ; Section 10.4.5: Not Found
      //     | "405"  ; Section 10.4.6: Method Not Allowed
      //     | "406"  ; Section 10.4.7: Not Acceptable


#define ECS_kStatusAccept               202
#define ECS_kStatusOK                   200
#define ECS_kStatusNoConetnt            204
#define ECS_kStatusPartialContent       206
#define ECS_kStatusBadRequest           400
#define ECS_kStatusNotFound             404
#define ECS_kStatusMethodNotAllowed     405
#define ECS_kStatusForbidden            403  
#define ECS_kStatusAuthenticationErr    470  
#define ECS_kStatusInternalServerErr    500      

#define ECS_kMIMEType_Binary                "application/octet-stream"
#define ECS_kMIMEType_DMAP                  "application/x-dmap-tagged"
#define ECS_kMIMEType_ImagePrefix           "image/"
#define ECS_kMIMEType_JSON                  "application/json"
#define ECS_kMIMEType_SDP                   "application/sdp"
#define ECS_kMIMEType_TextHTML              "text/html"
#define ECS_kMIMEType_TextParameters        "text/parameters"
#define ECS_kMIMEType_TextPlain             "text/plain"
#define ECS_kMIMEType_TLV8                  "application/x-tlv8" // 8-bit type, 8-bit length, N-byte value.
#define ECS_kMIMEType_Pairing_TLV8          "application/pairing+tlv8" // 8-bit type, 8-bit length, N-byte value.
#define ECS_kMIMEType_MXCHIP_OTA            "application/ota-stream"
#define ECS_kMIMEType_EASYCLOUD_OTA         "application/octet-stream"  // EasyCloud

#define ECS_kTransferrEncodingType_CHUNKED  "chunked"

#define ECS_OTA_Data_Length_per_read        1024


typedef struct
{
    char                buf[ 512 ];        //! Buffer holding the start line and all headers.
    size_t              len;                //! Number of bytes in the header.
    char *              extraDataPtr;       //! Ptr for any extra data beyond the header, it is alloced when http header is received.
    char *              otaDataPtr;         //! Ptr for any OTA data beyond the header, it is alloced when one OTA package is received.
    size_t              extraDataLen;       //! Length of any extra data beyond the header.

    const char *        methodPtr;          //! Request method (e.g. "GET"). "$" for interleaved binary data.
    size_t              methodLen;          //! Number of bytes in request method.
    const char *        urlPtr;             //! Request absolute or relative URL or empty if not a request.
    size_t              urlLen;             //! Number of bytes in URL.
    URLComponents       url;                //! Parsed URL components.
    const char *        protocolPtr;        //! Request or response protocol (e.g. "HTTP/1.1").
    size_t              protocolLen;        //! Number of bytes in protocol.
    int                 statusCode;         //! Response status code (e.g. 200 for HTTP OK).
    const char *        reasonPhrasePtr;    //! Response reason phrase (e.g. "OK" for an HTTP 200 OK response).
    size_t              reasonPhraseLen;    //! Number of bytes in reason phrase.

    uint8_t             channelID;          //! Interleaved binary data channel ID. 0 for other message types.
    uint64_t            contentLength;      //! Number of bytes following the header. May be 0.
    bool                persistent;         //! true=Do not close the connection after this message.

    int                 firstErr;           //! First error that occurred or kNoErr.

    bool                dataEndedbyClose;
    bool                chunkedData;        //! true=Application should read the next chunked data.
    char *              chunkedDataBufferPtr;     //! Ptr for any extra data beyond the header, it is alloced when http header is received.
    size_t              chunkedDataBufferLen; //! Total buffer length that stores the chunkedData, private use only


} ECS_HTTPHeader_t;

void ECS_PrintHTTPHeader( ECS_HTTPHeader_t *inHeader );

bool ECS_findHeader ( ECS_HTTPHeader_t *inHeader,  char **  outHeaderEnd);

int ECS_HTTPScanFHeaderValue( const char *inHeaderPtr, size_t inHeaderLen, const char *inName, const char *inFormat, ... );

int ECS_findCRLF( const char *inDataPtr , size_t inDataLen, char **  nextDataPtr );

int ECS_findChunkedDataLength( const char *inChunkPtr , size_t inChunkLen, char **  chunkedDataPtr, const char *inFormat, ... );

int ECS_SocketReadHTTPHeader( int inSock, ECS_HTTPHeader_t *inHeader );

int ECS_SocketReadHTTPBody( int inSock, ECS_HTTPHeader_t *inHeader );

int ECS_HTTPHeaderParse( ECS_HTTPHeader_t *ioHeader );

int ECS_HTTPHeaderMatchMethod( ECS_HTTPHeader_t *inHeader, const char *method );

int ECS_HTTPHeaderMatchURL( ECS_HTTPHeader_t *inHeader, const char *url );

char* ECS_HTTPHeaderMatchPartialURL( ECS_HTTPHeader_t *inHeader, const char *url );


int ECS_HTTPGetHeaderField( const char *inHeaderPtr, 
                             size_t     inHeaderLen, 
                             const char *inName, 
                             const char **outNamePtr, 
                             size_t     *outNameLen, 
                             const char **outValuePtr, 
                             size_t     *outValueLen, 
                             const char **outNext );

ECS_HTTPHeader_t * ECS_HTTPHeaderCreate( void );
void ECS_HTTPHeaderClear( ECS_HTTPHeader_t *inHeader );

int ECS_CreateSimpleHTTPOKMessage( uint8_t **outMessage, size_t *outMessageSize );

OSStatus ECS_CreateSimpleHTTPMessage( const char *contentType, 
                                     uint8_t *inData, size_t inDataLen, 
                                     uint8_t **outMessage, size_t *outMessageSize );
OSStatus ECS_CreateSimpleHTTPMessageNoCopy( const char *contentType, size_t inDataLen, 
                                           uint8_t **outMessage, size_t *outMessageSize );

OSStatus ECS_CreateHTTPRespondMessageNoCopy( int status, const char *contentType, 
                                            size_t inDataLen, 
                                            uint8_t **outMessage, size_t *outMessageSize );

OSStatus ECS_CreateHTTPMessage( const char *methold, const char *url, 
                               const char *contentType, 
                               uint8_t *inData, size_t inDataLen, 
                               uint8_t **outMessage, size_t *outMessageSize );


//=============================== add by WES ===================================
OSStatus ECS_CreateHTTPMessageEx( const char *methold, const char * host, 
                             const char *url, const char *contentType, 
                             uint8_t *inData, size_t inDataLen, 
                             uint8_t **outMessage, size_t *outMessageSize );
OSStatus ECS_CreateHTTPMessageWithRange( const char *methold, const char * host, 
                             const char *url, const char *contentType, 
                             uint64_t rangeStart,
                             uint8_t *inData, size_t inDataLen, 
                             uint8_t **outMessage, size_t *outMessageSize );

OSStatus ECS_CreateSimpleHTTPFailedMessage( uint8_t **outMessage, 
                                       size_t *outMessageSize );
OSStatus ECS_CreateHTTPFailedMessage(const uint8_t *errCode, const uint8_t *errMsg,
                                     const char *contentType, size_t contentLen,
                                     uint8_t *errData, size_t errDataLen, 
                                     uint8_t **outMessage, size_t *outMessageSize );
int ECS_SocketReadHTTPHeaderEx( int inSock, ECS_HTTPHeader_t *inHeader );
OSStatus ECS_SocketReadHTTPBodyEx( int inSock, ECS_HTTPHeader_t *inHeader );

//#ifdef MICO_FLASH_FOR_UPDATE

// OTA flash address
typedef struct _ecs_ota_flash_params_t {
  mico_flash_t flash_type;             // internal flash or spi flash
  uint32_t update_flashStartAddress;
  uint32_t update_flashEndAddress;
  uint32_t update_flashSize;
}ecs_ota_flash_params_t;

void ECS_initFlashStorageParams(ecs_ota_flash_params_t flashStorageParams);

uint32_t ECS_getFlashStorageAddress(void);
void ECS_resetFlashStorageAddress(void);
uint64_t ECS_getDownloadedFileSize(void);
void ECS_FlashWriteDone(void);
char* ECS_getRomFileMD5_32(void);


//#endif


// ============================= STRING UTILS ==============================

char* ECS_DataToHexStringLowercase( const uint8_t *inBuf, size_t inBufLen );
// string replace, dst string must be freed by user
char* ECS_str_replace(char *dst, const char *src, const unsigned int srcLen, char *old_str, char *new_str);


#endif // __EASYCLOUD_UTILS_H__

