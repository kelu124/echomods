/**
******************************************************************************
* @file    HTTPUtils.c 
* @author  William Xu
* @version V1.0.0
* @date    05-May-2014
* @brief   These functions assist with interacting with HTTP clients and servers.
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


#include "MICO.h"
#include "StringUtils.h"
#include "HTTPUtils.h"
#include "MicoPlatform.h"
#include "platform.h"

#include <errno.h>
#include <stdarg.h>

#define kCRLFNewLine     "\r\n"
#define kCRLFLineEnding  "\r\n\r\n"

#define http_utils_log(M, ...) custom_log("HTTPUtils", M, ##__VA_ARGS__)

#define READ_LENGTH 1500

OSStatus onReceivedDataCallbackDefault(struct _HTTPHeader_t * httpHeader, uint32_t pos, uint8_t * data, size_t len, void * userContext )
{
  UNUSED_PARAMETER(httpHeader);
  UNUSED_PARAMETER(pos);
  UNUSED_PARAMETER(data);
  UNUSED_PARAMETER(len);
  UNUSED_PARAMETER(userContext);
  return kUnsupportedErr;
}

int SocketReadHTTPHeader( int inSock, HTTPHeader_t *inHeader )
{
  int        err =0;
  char *          buf;
  char *          dst;
  char *          lim;
  char *          end;
  size_t          len;
  ssize_t         n;
  
  buf = inHeader->buf;
  dst = buf + inHeader->len;
  lim = buf + sizeof( inHeader->buf );
  for( ;; )
  {
    if(findHeader( inHeader,  &end ))
      break ;
    n = read( inSock, dst, (size_t)( lim - dst ) );
    if(      n  > 0 ) len = (size_t) n;
    else  { err = kConnectionErr; goto exit; }
    dst += len;
    inHeader->len += len;
  }
  
  inHeader->len = (size_t)( end - buf );
  err = HTTPHeaderParse( inHeader );
  require_noerr( err, exit );
  inHeader->extraDataLen = (size_t)( dst - end );
  if(inHeader->extraDataPtr) {
    free((uint8_t *)inHeader->extraDataPtr);
    inHeader->extraDataPtr = 0;
  }

  /* For chunked extra data without content length */
  if(inHeader->chunkedData == true){
    inHeader->chunkedDataBufferLen = (inHeader->extraDataLen > READ_LENGTH)? inHeader->extraDataLen:READ_LENGTH;
    inHeader->chunkedDataBufferPtr = calloc(inHeader->chunkedDataBufferLen, sizeof(uint8_t)); //Make extra data buffer larger than chunk length
    require_action(inHeader->chunkedDataBufferPtr, exit, err = kNoMemoryErr);
    memcpy((uint8_t *)inHeader->chunkedDataBufferPtr, end, inHeader->extraDataLen);
    inHeader->extraDataPtr = inHeader->chunkedDataBufferPtr;
    return kNoErr;
  }

  /* Extra data with content length */

  if (inHeader->contentLength != 0){ //Content length >0, create a memory buffer (Content length) and store extra data
    size_t copyDataLen = (inHeader->contentLength >= inHeader->extraDataLen)? inHeader->extraDataLen : inHeader->contentLength;
    if(inHeader->onReceivedDataCallback && (inHeader->onReceivedDataCallback)(inHeader, 0, (uint8_t *)end, copyDataLen, inHeader->userContext)==kNoErr){
      inHeader->isCallbackSupported = true;
      inHeader->extraDataPtr = calloc(READ_LENGTH, sizeof(uint8_t));
      require_action(inHeader->extraDataPtr, exit, err = kNoMemoryErr);
    }else{
      inHeader->isCallbackSupported = false;
      inHeader->extraDataPtr = calloc(inHeader->contentLength , sizeof(uint8_t));
      require_action(inHeader->extraDataPtr, exit, err = kNoMemoryErr);
      memcpy((uint8_t *)inHeader->extraDataPtr, end, copyDataLen);
    }
    err = kNoErr;
  } /* Extra data without content length, data is ended by conntection close */
  // else if(inHeader->extraDataLen != 0){ //Content length =0, but extra data length >0, create a memory buffer (1500)and store extra data
  //   inHeader->dataEndedbyClose = true;
  //   inHeader->extraDataPtr = calloc(1500, sizeof(uint8_t));
  //   require_action(inHeader->extraDataPtr, exit, err = kNoMemoryErr);
  //   memcpy((uint8_t *)inHeader->extraDataPtr, end, inHeader->extraDataLen);
  //   (inHeader->onReceivedDataCallback)(inHeader, 0, (uint8_t *)inHeader->extraDataPtr, inHeader->extraDataLen, inHeader->userContext);

  //   err = kNoErr;
  // }
  else
    return kNoErr;
  
exit:
  return err;
}


bool findHeader ( HTTPHeader_t *inHeader,  char **  outHeaderEnd)
{
  char *dst = inHeader->buf + inHeader->len;
  char *buf = (char *)inHeader->buf;
  char *src = (char *)inHeader->buf;
  size_t          len;
  
  // Check for interleaved binary data (4 byte header that begins with $). See RFC 2326 section 10.12.
  if( ( ( dst - buf ) >= 4 ) && ( buf[ 0 ] == '$' ) )
  {
    *outHeaderEnd = buf + 4;
    return true;
  }
  
  // Find an empty line (separates the header and body). The HTTP spec defines it as CRLFCRLF, but some
  // use LFLF or weird combos like CRLFLF so this handles CRLFCRLF, LFLF, and CRLFLF (but not CRCR).
  *outHeaderEnd = dst;
  for( ;; )
  {
    while( ( src < *outHeaderEnd ) && ( *src != '\n' ) ) ++src;
    if( src >= *outHeaderEnd ) break;
    
    len = (size_t)( *outHeaderEnd - src );
    if( ( len >= 3 ) && ( src[ 1 ] == '\r' ) && ( src[ 2 ] == '\n' ) ) // CRLFCRLF or LFCRLF.
    {
      *outHeaderEnd = src + 3;
      return true;
    }
    else if( ( len >= 2 ) && ( src[ 1 ] == '\n' ) ) // LFLF or CRLFLF.
    {
      *outHeaderEnd = src + 2;
      return true;
    }
    else if( len <= 1 )
    {
      break;
    }
    ++src;
  }
  return false;
}

OSStatus SocketReadHTTPBody( int inSock, HTTPHeader_t *inHeader )
{
  OSStatus err = kParamErr;
  ssize_t readResult;
  int selectResult;
  fd_set readSet;
  size_t    lastChunkLen, chunckheaderLen; 
  char *nextPackagePtr;
  struct timeval_t t;
  size_t          readLength;
  uint32_t pos = 0;
  t.tv_sec = 5;
  t.tv_usec = 0;
  
  require( inHeader, exit );
  err = kNotReadableErr;
  
  FD_ZERO( &readSet );
  FD_SET( inSock, &readSet );

  /* Chunked data without content length */
  if( inHeader->chunkedData == true ){
    do{
      /* Find Chunk data length */
      while ( findChunkedDataLength( inHeader->chunkedDataBufferPtr, inHeader->extraDataLen, &inHeader->extraDataPtr ,"%llu", &inHeader->contentLength ) == false){
        require_action(inHeader->extraDataLen < inHeader->chunkedDataBufferLen, exit, err=kMalformedErr );

        selectResult = select( inSock + 1, &readSet, NULL, NULL, NULL );
        require_action( selectResult >= 1, exit, err = kNotReadableErr );

        readResult = read( inSock, inHeader->chunkedDataBufferPtr + inHeader->extraDataLen, (size_t)( inHeader->chunkedDataBufferLen - inHeader->extraDataLen ) );

        if( readResult  > 0 ) inHeader->extraDataLen += readResult;
        else { err = kConnectionErr; goto exit; }
      }

      chunckheaderLen = inHeader->extraDataPtr - inHeader->chunkedDataBufferPtr;

      /* Check the last chunk */
      if(inHeader->contentLength == 0){ 
        while( findCRLF( inHeader->extraDataPtr, inHeader->extraDataLen - chunckheaderLen, &nextPackagePtr ) == false){ //find CRLF
          selectResult = select( inSock + 1, &readSet, NULL, NULL, NULL );
          require_action( selectResult >= 1, exit, err = kNotReadableErr );

          readResult = read( inSock,
                            (uint8_t *)( inHeader->extraDataPtr + inHeader->extraDataLen - chunckheaderLen ),
                            256 - inHeader->extraDataLen ); //Assume chunk trailer length is less than 256 (256 is the min chunk buffer, maybe dangerous

          if( readResult  > 0 ) inHeader->extraDataLen += readResult;
          else { err = kConnectionErr; goto exit; }
          (inHeader->onReceivedDataCallback)(inHeader, inHeader->extraDataLen - readResult, (uint8_t *)inHeader->extraDataPtr, readResult, inHeader->userContext);
        }

        err = kNoErr;
        goto exit;
      } 
      else{ // Read chunk data
        /* Chunk package already exist, callback, move to buffer's head */
        if( inHeader->extraDataLen >= inHeader->contentLength + chunckheaderLen + 2 ){
          require_action( *(inHeader->extraDataPtr + inHeader->contentLength ) == '\r' &&
                          *(inHeader->extraDataPtr + inHeader->contentLength + 1 ) == '\n', 
                          exit, err = kMalformedErr);

          (inHeader->onReceivedDataCallback)(inHeader,  pos, 
                                                        (uint8_t *)inHeader->extraDataPtr, 
                                                        inHeader->contentLength, 
                                                        inHeader->userContext);
          pos+=inHeader->contentLength;

          /* Move next chunk to chunked data buffer header point */
          lastChunkLen = inHeader->extraDataPtr - inHeader->chunkedDataBufferPtr + inHeader->contentLength;
          if(inHeader->contentLength) lastChunkLen += 2;  //Last chunck data has a CRLF tail
          memmove( inHeader->chunkedDataBufferPtr, inHeader->chunkedDataBufferPtr + lastChunkLen, inHeader->chunkedDataBufferLen - lastChunkLen  );
          inHeader->extraDataLen -= lastChunkLen;
        }
        /* Chunck exist without the last LF, generate callback abd recv LF */
        /* Callback , read LF */
        else if(inHeader->extraDataLen == inHeader->contentLength + chunckheaderLen +1){ //recv CR 

          require_action( *(inHeader->chunkedDataBufferPtr + inHeader->extraDataLen - 1) == '\r' ,
                          exit, err = kMalformedErr);

          (inHeader->onReceivedDataCallback)(inHeader,  pos, 
                                                        (uint8_t *)inHeader->extraDataPtr, 
                                                        inHeader->extraDataLen - chunckheaderLen-1, 
                                                        inHeader->userContext);
          pos+=inHeader->extraDataLen - chunckheaderLen-1;
          selectResult = select( inSock + 1, &readSet, NULL, NULL, NULL );
          require_action( selectResult >= 1, exit, err = kNotReadableErr );

          readResult = read( inSock, (uint8_t *)inHeader->extraDataPtr, 1);

          if( readResult  > 0 ) {}
          else { err = kConnectionErr; goto exit; }

          require_action( *(inHeader->extraDataPtr) == '\n', exit, err = kMalformedErr);
          inHeader->extraDataLen = 0;
        }
        else{
          /* Callback , read , callback , read CRLF */
          (inHeader->onReceivedDataCallback)(inHeader, pos, 
                                                       (uint8_t *)inHeader->extraDataPtr, 
                                                       inHeader->extraDataLen - chunckheaderLen, 
                                                       inHeader->userContext);
          pos += inHeader->extraDataLen - chunckheaderLen;

          while ( inHeader->extraDataLen < inHeader->contentLength + chunckheaderLen  ){
            selectResult = select( inSock + 1, &readSet, NULL, NULL, NULL );
            require_action( selectResult >= 1, exit, err = kNotReadableErr );

            if( inHeader->contentLength - (inHeader->extraDataLen - chunckheaderLen) > inHeader->chunkedDataBufferLen - chunckheaderLen)
              //Data needed is greater than valid buffer size
              readLength = inHeader->chunkedDataBufferLen - chunckheaderLen; 
            else
              //Data needed is less than valid buffer size
              readLength = inHeader->contentLength - (inHeader->extraDataLen - chunckheaderLen) ; 

            readResult = read( inSock, (uint8_t *)inHeader->extraDataPtr, readLength);
            
            if( readResult  > 0 ) inHeader->extraDataLen += readResult;
            else { err = kConnectionErr; goto exit; }

            (inHeader->onReceivedDataCallback)(inHeader, pos, 
                                                         (uint8_t *)inHeader->extraDataPtr, 
                                                         readResult, 
                                                         inHeader->userContext);
            pos += readResult;
          } 

          selectResult = select( inSock + 1, &readSet, NULL, NULL, NULL );
          require_action( selectResult >= 1, exit, err = kNotReadableErr );

          readResult = read( inSock, (uint8_t *)inHeader->extraDataPtr, 2);

          if( readResult  > 0 ) {}
          else { err = kConnectionErr; goto exit; }


          require_action( *(inHeader->extraDataPtr) == '\r' &&
                          *(inHeader->extraDataPtr+1 ) == '\n', 
                          exit, err = kMalformedErr);

          inHeader->extraDataLen = 0;
        }
      }
    }while(inHeader->contentLength != 0);
  }

  /* We has extra data but total length is not clear, store them to 1500 bytes buffer 
     return when connection is disconnected by remote server */
  // if( inHeader->dataEndedbyClose == true){ 
  //   if(inHeader->contentLength == 0) { //First read body, return using data received by SocketReadHTTPHeader
  //     inHeader->contentLength = inHeader->extraDataLen;
  //   }else{
  //     selectResult = select( inSock + 1, &readSet, NULL, NULL, NULL );
  //     require_action( selectResult >= 1, exit, err = kNotReadableErr );
      
  //     readResult = read( inSock,
  //                       (uint8_t*)( inHeader->extraDataPtr ),
  //                       1500 );
  //     if( readResult  > 0 ) inHeader->contentLength = readResult;
  //     else { err = kConnectionErr; goto exit; }
  //   }
  //   err = kNoErr;
  //   goto exit;
  // }
  

  while ( inHeader->extraDataLen < inHeader->contentLength )
  {
    selectResult = select( inSock + 1, &readSet, NULL, NULL, &t );
    require_action( selectResult >= 1, exit, err = kNotReadableErr );

    if(inHeader->isCallbackSupported == true){
      /* We has extra data, and we give these data to application by onReceivedDataCallback function */
      readLength = inHeader->contentLength - inHeader->extraDataLen > READ_LENGTH? READ_LENGTH:inHeader->contentLength - inHeader->extraDataLen;
      readResult = read( inSock,
                        (uint8_t*)( inHeader->extraDataPtr),
                        readLength );
      
      if( readResult  > 0 ) inHeader->extraDataLen += readResult;
      else { err = kConnectionErr; goto exit; }      
      (inHeader->onReceivedDataCallback)(inHeader, inHeader->extraDataLen - readResult, (uint8_t *)inHeader->extraDataPtr, readResult, inHeader->userContext);
    }else{
      /* We has extra data and we has a predefined buffer to store the total extra data return when all data has received*/
      readResult = read( inSock,
                        (uint8_t*)( inHeader->extraDataPtr + inHeader->extraDataLen ),
                        ( inHeader->contentLength - inHeader->extraDataLen ) );
      
      if( readResult  > 0 ) inHeader->extraDataLen += readResult;
      else { err = kConnectionErr; goto exit; }
    }
  }
  err = kNoErr;
  
exit:
  if(err != kNoErr) inHeader->len = 0;
  return err;
}

//===========================================================================================================================
//  HTTPHeader_Parse
//
//  Parses an HTTP header. This assumes the "buf" and "len" fields are set. The other fields are set by this function.
//===========================================================================================================================

OSStatus HTTPHeaderParse( HTTPHeader_t *ioHeader )
{
  OSStatus            err;
  const char *        src;
  const char *        end;
  const char *        ptr;
  char                c;
  const char *        value;
  size_t              valueSize;
  int                 x;
  
  require_action( ioHeader->len < sizeof( ioHeader->buf ), exit, err = kParamErr );
  
  // Reset fields up-front to good defaults to simplify handling of unused fields later.
  
  ioHeader->methodPtr         = "";
  ioHeader->methodLen         = 0;
  ioHeader->urlPtr            = "";
  ioHeader->urlLen            = 0;
  memset( &ioHeader->url, 0, sizeof( ioHeader->url ) );
  ioHeader->protocolPtr       = "";
  ioHeader->protocolLen       = 0;
  ioHeader->statusCode        = -1;
  ioHeader->reasonPhrasePtr   = "";
  ioHeader->reasonPhraseLen   = 0;
  ioHeader->channelID         = 0;
  ioHeader->contentLength     = 0;
  ioHeader->persistent        = false;
  
  // Check for a 4-byte interleaved binary data header (see RFC 2326 section 10.12). It has the following format:
  //
  //      '$' <1:channelID> <2:dataSize in network byte order> ... followed by dataSize bytes of binary data.
  src = ioHeader->buf;
  if( ( ioHeader->len == 4 ) && ( src[ 0 ] == '$' ) )
  {
    const uint8_t *     usrc;
    
    usrc = (const uint8_t *) src;
    ioHeader->channelID     =   usrc[ 1 ];
    ioHeader->contentLength = ( usrc[ 2 ] << 8 ) | usrc[ 3 ];
    
    ioHeader->methodPtr = src;
    ioHeader->methodLen = 1;
    
    err = kNoErr;
    goto exit;
  }
  
  // Parse the start line. This will also determine if it's a request or response.
  // Requests are in the format <method> <url> <protocol>/<majorVersion>.<minorVersion>, for example:
  //
  //      GET /abc/xyz.html HTTP/1.1
  //      GET http://www.host.com/abc/xyz.html HTTP/1.1
  //      GET http://user:password@www.host.com/abc/xyz.html HTTP/1.1
  //
  // Responses are in the format <protocol>/<majorVersion>.<minorVersion> <statusCode> <reasonPhrase>, for example:
  //
  //      HTTP/1.1 404 Not Found
  ptr = src;
  end = src + ioHeader->len;
  for( c = 0; ( ptr < end ) && ( ( c = *ptr ) != ' ' ) && ( c != '/' ); ++ptr ) {}
  require_action( ptr < end, exit, err = kMalformedErr );
  
  if( c == ' ' ) // Requests have a space after the method. Responses have '/' after the protocol.
  {
    ioHeader->methodPtr = src;
    ioHeader->methodLen = (size_t)( ptr - src );
    ++ptr;
    
    // Parse the URL.
    ioHeader->urlPtr = ptr;
    while( ( ptr < end ) && ( *ptr != ' ' ) ) ++ptr;
    ioHeader->urlLen = (size_t)( ptr - ioHeader->urlPtr );
    require_action( ptr < end, exit, err = kMalformedErr );
    ++ptr;
    
    err = URLParseComponents( ioHeader->urlPtr, ioHeader->urlPtr + ioHeader->urlLen, &ioHeader->url, NULL );
    require_noerr( err, exit );
    
    // Parse the protocol and version.
    ioHeader->protocolPtr = ptr;
    while( ( ptr < end ) && ( ( c = *ptr ) != '\r' ) && ( c != '\n' ) ) ++ptr;
    ioHeader->protocolLen = (size_t)( ptr - ioHeader->protocolPtr );
    require_action( ptr < end, exit, err = kMalformedErr );
    ++ptr;
  }
  else // Response
  {
    // Parse the protocol version.
    ioHeader->protocolPtr = src;
    for( ++ptr; ( ptr < end ) && ( *ptr != ' ' ); ++ptr ) {}
    ioHeader->protocolLen = (size_t)( ptr - ioHeader->protocolPtr );
    require_action( ptr < end, exit, err = kMalformedErr );
    ++ptr;
    
    // Parse the status code.
    x = 0;
    for( c = 0; ( ptr < end ) && ( ( c = *ptr ) >= '0' ) && ( c <= '9' ); ++ptr ) x = ( x * 10 ) + ( c - '0' ); 
    ioHeader->statusCode = x;
    if( c == ' ' ) ++ptr;
    
    // Parse the reason phrase.
    ioHeader->reasonPhrasePtr = ptr;
    while( ( ptr < end ) && ( ( c = *ptr ) != '\r' ) && ( c != '\n' ) ) ++ptr;
    ioHeader->reasonPhraseLen = (size_t)( ptr - ioHeader->reasonPhrasePtr );
    require_action( ptr < end, exit, err = kMalformedErr );
    ++ptr;
  }
  
  // There should at least be a blank line after the start line so make sure there's more data.
  require_action( ptr < end, exit, err = kMalformedErr );
  
  // Determine persistence. Note: HTTP 1.0 defaults to non-persistent if a Connection header field is not present.
  err = HTTPGetHeaderField( ioHeader->buf, ioHeader->len, "Connection", NULL, NULL, &value, &valueSize, NULL );
  if( err )   ioHeader->persistent = (Boolean)( strnicmpx( ioHeader->protocolPtr, ioHeader->protocolLen, "HTTP/1.0" ) != 0 );
  else        ioHeader->persistent = (Boolean)( strnicmpx( value, valueSize, "close" ) != 0 );

  err = HTTPGetHeaderField( ioHeader->buf, ioHeader->len, "Transfer-Encoding", NULL, NULL, &value, &valueSize, NULL );
  if( err )   ioHeader->chunkedData = false;
  else        ioHeader->chunkedData = (Boolean)( strnicmpx( value, valueSize, kTransferrEncodingType_CHUNKED ) == 0 );
  
  // Content-Length is such a common field that we get it here during general parsing.
  HTTPScanFHeaderValue( ioHeader->buf, ioHeader->len, "Content-Length", "%llu", &ioHeader->contentLength );

  err = kNoErr;
  
exit:
  return err;
}

int findCRLF( const char *inDataPtr , size_t inDataLen, char **  nextDataPtr ) //find CRLF
{
  char *dst = (char *)inDataPtr + inDataLen;
  char *src = (char *)inDataPtr;
  size_t          len;
  
  // Find an empty line (separates the length and data).
  for( ;; )
  {
    while( ( src < dst ) && ( *src != '\r' ) ) ++src;
    if( src >= dst ) break;
    
    len = (size_t)( dst - src );

    if( ( len >= 2 ) && ( src[ 1 ] == '\n' ) ) // CRLF
    {
       *nextDataPtr = src + 2;
      return true;
    }
    else if( len <= 1 )
    {
      break;
    }
    ++src;
  }
  return false;  
}

int findChunkedDataLength( const char *inChunkPtr , size_t inChunkLen, char **  chunkedDataPtr, const char *inFormat, ... )
{
  char *dst = (char *)inChunkPtr + inChunkLen;
  char *src = (char *)inChunkPtr;
  size_t          len;
  va_list         args;
  
  // Find an empty line (separates the length and data).
  *chunkedDataPtr = dst;
  for( ;; )
  {
    while( ( src < *chunkedDataPtr ) && ( *src != '\r' ) ) ++src;
    if( src >= *chunkedDataPtr ) break;
    
    len = (size_t)( *chunkedDataPtr - src );

    if( ( len >= 2 ) && ( src[ 1 ] == '\n' ) ) // CRLF
    {
      if(*inChunkPtr == 0x30){ //last chunk
        *chunkedDataPtr = src + 2;
        va_start( args, inFormat );
        VSNScanF( "0", 1, "%llu", args);
        va_end( args );
        return true;
      }

      *chunkedDataPtr = src + 2;
      va_start( args, inFormat );
      VSNScanF( inChunkPtr, src - inChunkPtr, "%x", args);
      va_end( args );
      return true;
    }
    else if( len <= 1 )
    {
      break;
    }
    ++src;
  }
  return false;  
}

OSStatus HTTPGetHeaderField( const char *inHeaderPtr, 
                            size_t     inHeaderLen, 
                            const char *inName, 
                            const char **outNamePtr, 
                            size_t     *outNameLen, 
                            const char **outValuePtr, 
                            size_t     *outValueLen, 
                            const char **outNext )
{
  const char *        src;
  const char *        end;
  size_t              matchLen;
  char                c;
  
  if( inHeaderLen == kSizeCString ) inHeaderLen = strlen( inHeaderPtr );
  src = inHeaderPtr;
  end = src + inHeaderLen;
  matchLen = inName ? strlen( inName ) : 0;
  for( ;; )
  {
    const char *        linePtr;
    const char *        lineEnd;
    size_t              lineLen;
    const char *        valuePtr;
    const char *        valueEnd;
    
    // Parse a line and check if it begins with the header field we're looking for.
    linePtr = src;
    while( ( src < end ) && ( ( c = *src ) != '\r' ) && ( c != '\n' ) ) ++src;
    if( src >= end ) break;
    lineEnd = src;
    lineLen = (size_t)( src - linePtr );
    if( ( src < end ) && ( *src == '\r' ) ) ++src;
    if( ( src < end ) && ( *src == '\n' ) ) ++src;
    
    if( !inName ) // Null name means to find the next header for iteration.
    {
      const char *        nameEnd;
      
      nameEnd = linePtr;
      while( ( nameEnd < lineEnd ) && ( *nameEnd != ':' ) ) ++nameEnd;
      if( nameEnd >= lineEnd ) continue;
      matchLen = (size_t)( nameEnd - linePtr );
    }
    else if( ( lineLen <= matchLen ) || ( linePtr[ matchLen ] != ':' ) || 
            ( strnicmp( linePtr, inName, matchLen ) != 0 ) )
    {
      continue;
    }
    
    // Found the header field. Separate name and value and skip leading whitespace in the value.
    valuePtr = linePtr + matchLen + 1;
    valueEnd = lineEnd;
    while( ( valuePtr < valueEnd ) && ( ( ( c = *valuePtr ) == ' ' ) || ( c == '\t' ) ) ) ++valuePtr;
    
    // If the next line is a continuation line then keep parsing until we get to the true end.
    while( ( src < end ) && ( ( ( c = *src ) == ' ' ) || ( c == '\t' ) ) )
    {
      ++src;
      while( ( src < end ) && ( ( c = *src ) != '\r' ) && ( c != '\n' ) ) ++src;
      valueEnd = src;
      if( ( src < end ) && ( *src == '\r' ) ) ++src;
      if( ( src < end ) && ( *src == '\n' ) ) ++src;
    }
    
    if( outNamePtr )    *outNamePtr     = linePtr;
    if( outNameLen )    *outNameLen     = matchLen;
    if( outValuePtr )   *outValuePtr    = valuePtr;
    if( outValueLen )   *outValueLen    = (size_t)( valueEnd - valuePtr );
    if( outNext )       *outNext        = src;
    return( kNoErr );
  }
  return kNotFoundErr;
}

int HTTPScanFHeaderValue( const char *inHeaderPtr, size_t inHeaderLen, const char *inName, const char *inFormat, ... )
{
  int                 n;
  const char *        valuePtr;
  size_t              valueLen;
  va_list             args;
  
  n = (int) HTTPGetHeaderField( inHeaderPtr, inHeaderLen, inName, NULL, NULL, &valuePtr, &valueLen, NULL );
  require_noerr_quiet( n, exit );
  
  va_start( args, inFormat );
  n = VSNScanF( valuePtr, valueLen, inFormat, args );
  va_end( args );
  
exit:
  return( n );
}

OSStatus HTTPHeaderMatchMethod( HTTPHeader_t *inHeader, const char *method )
{
  if( strnicmpx( inHeader->methodPtr, inHeader->methodLen, method ) == 0 )
    return kNoErr;
  
  return kNotFoundErr;
}

OSStatus HTTPHeaderMatchURL( HTTPHeader_t *inHeader, const char *url )
{
  if( strnicmp_suffix( inHeader->url.pathPtr, inHeader->url.pathLen, url ) == 0 )
    return kNoErr;
  
  return kNotFoundErr;
}

char* HTTPHeaderMatchPartialURL( HTTPHeader_t *inHeader, const char *url )
{
  return strnstr_suffix( inHeader->url.pathPtr, inHeader->url.pathLen, url);
}

HTTPHeader_t * HTTPHeaderCreate( void )
{
  HTTPHeader_t *httpHeader;
  httpHeader = calloc(1, sizeof(HTTPHeader_t));
  httpHeader->onReceivedDataCallback = onReceivedDataCallbackDefault;
  return httpHeader;
}

HTTPHeader_t * HTTPHeaderCreateWithCallback( onReceivedDataCallback inRecvFunc, onClearCallback onClearFunc, void * context )
{
  HTTPHeader_t *httpHeader;
  httpHeader = HTTPHeaderCreate();
  httpHeader->userContext = context;
  httpHeader->onReceivedDataCallback = inRecvFunc;
  httpHeader->onClearCallback = onClearFunc;
  return httpHeader;
}

void HTTPHeaderClear( HTTPHeader_t *inHeader )
{
  char *nextPackagePtr;
  size_t chunckheaderLen = inHeader->extraDataPtr - inHeader->chunkedDataBufferPtr;

  if(inHeader->onClearCallback)
    (inHeader->onClearCallback)(inHeader, inHeader->userContext);

  if(inHeader->chunkedData && (uint32_t *)inHeader->chunkedDataBufferPtr){ //chunk data
    /* Possible to read the header of the next http package */
    if(findCRLF( inHeader->extraDataPtr, inHeader->extraDataLen - chunckheaderLen, &nextPackagePtr ) ){
      if( nextPackagePtr <= inHeader->chunkedDataBufferPtr + inHeader->extraDataLen ){ //We get some data belongs to next http package
        inHeader->len = inHeader->extraDataLen - (nextPackagePtr - inHeader->chunkedDataBufferPtr);
        if(inHeader->len > 512)
          inHeader->len = 0;
        else
          memcpy(inHeader->buf, nextPackagePtr, inHeader->len);
      } else
        inHeader->len = 0;
    }

    inHeader->extraDataLen = 0;
    free((uint32_t *)inHeader->chunkedDataBufferPtr);
    inHeader->chunkedDataBufferPtr = NULL;   
    inHeader->extraDataPtr = NULL;   
    inHeader->chunkedData = false;
  }else{

    /* We get some data belongs to next http package, this only could happen two or more
      packages are received by SocketReadHTTPHeader */ 
    if( inHeader->extraDataLen > inHeader->contentLength ){ 
      inHeader->len = inHeader->extraDataLen - inHeader->contentLength;
      memcpy(inHeader->buf, inHeader->extraDataPtr + inHeader->contentLength, inHeader->len);
    } else
      inHeader->len = 0;

    inHeader->extraDataLen = 0;
    if((uint32_t *)inHeader->extraDataPtr) {
      free((uint32_t *)inHeader->extraDataPtr);
      inHeader->extraDataPtr = NULL;
    } 
    inHeader->dataEndedbyClose = false;
  }

  inHeader->isCallbackSupported = false;

}

OSStatus CreateSimpleHTTPOKMessage( uint8_t **outMessage, size_t *outMessageSize )
{
  OSStatus err = kNoMemoryErr;
  *outMessage = malloc( 200 );
  require( *outMessage, exit );
  
  sprintf( (char*)*outMessage,
          "%s %s %s%s",
          "HTTP/1.1", "200", "OK", kCRLFLineEnding );
  *outMessageSize = strlen( (char*)*outMessage );
  
  err = kNoErr;
  
exit:
  return err;
}



OSStatus CreateSimpleHTTPMessage( const char *contentType, uint8_t *inData, size_t inDataLen, uint8_t **outMessage, size_t *outMessageSize )
{
  uint8_t *endOfHTTPHeader;  
  OSStatus err = kParamErr;
  
  
  require( contentType, exit );
  require( inData, exit );
  require( inDataLen, exit );
  
  
  err = kNoMemoryErr;
  *outMessage = malloc( inDataLen + 200 );
  require( *outMessage, exit );
  
  // Create HTTP Response
  snprintf( (char*)*outMessage, 200, 
           "%s %d %s%s%s %s%s%s %d%s",
           "HTTP/1.1", 200, "OK", kCRLFNewLine, 
           "Content-Type:", contentType, kCRLFNewLine,
           "Content-Length:", (int)inDataLen, kCRLFLineEnding );
  
  // outMessageSize will be the length of the HTTP Header plus the data length
  *outMessageSize = strlen( (char*)*outMessage ) + inDataLen;
  
  endOfHTTPHeader = *outMessage + strlen( (char*)*outMessage );
  memcpy( endOfHTTPHeader, inData, inDataLen ); 
  err = kNoErr;
  
exit:
  return err;
}

OSStatus CreateSimpleHTTPMessageNoCopy( const char *contentType, size_t inDataLen, uint8_t **outMessage, size_t *outMessageSize )
{
  OSStatus err = kParamErr;
  
  require( contentType, exit );
  require( inDataLen, exit );
  
  err = kNoMemoryErr;
  *outMessage = malloc( 200 );
  require( *outMessage, exit );
  
  // Create HTTP Response
  snprintf( (char*)*outMessage, 200, 
           "%s %s %s%s%s %s%s%s %d%s",
           "HTTP/1.1", "200", "OK", kCRLFNewLine, 
           "Content-Type:", contentType, kCRLFNewLine,
           "Content-Length:", (int)inDataLen, kCRLFLineEnding );
  
  // outMessageSize will be the length of the HTTP Header plus the data length
  *outMessageSize = strlen( (char*)*outMessage );
  err = kNoErr;
  
exit:
  return err;
}

char * getStatusString(int status)
{
  if(status == kStatusOK)
    return "OK";
  else if(status == kStatusNoConetnt)
    return "No Content";
  else if(status == kStatusPartialContent)
    return "Multi0Status";
  else if(status == kStatusBadRequest)
    return "Bad Request";
  else if(status == kStatusNotFound)
    return "Not Found";
  else if(status == kStatusMethodNotAllowed)
    return "Not Allowed";
  else if(status == kStatusForbidden) 
    return "Forbidden";
  else if(status == kStatusAuthenticationErr)
    return "Authentication Error";
  else if(status == kStatusInternalServerErr)
    return "Internal Server Error";
  else
    return "OK";
}

OSStatus CreateHTTPRespondMessageNoCopy( int status, const char *contentType, size_t inDataLen, uint8_t **outMessage, size_t *outMessageSize )
{
  OSStatus err = kParamErr;
  char *statusString = getStatusString(status);
    
  err = kNoMemoryErr;
  *outMessage = malloc( 200 );
  require( *outMessage, exit );
  
  // Create HTTP Response
  if(inDataLen)
    snprintf( (char*)*outMessage, 200, 
            "%s %d %s%s%s %s%s%s %d%s",
            "HTTP/1.1", status, statusString, kCRLFNewLine, 
            "Content-Type:", contentType, kCRLFNewLine,
            "Content-Length:", (int)inDataLen, kCRLFLineEnding );
  else
    snprintf( (char*)*outMessage, 200, 
        "%s %d %s%s",
        "HTTP/1.1", status, statusString, kCRLFLineEnding);
  
  // outMessageSize will be the length of the HTTP Header plus the data length
  *outMessageSize = strlen( (char*)*outMessage );
  err = kNoErr;
  
exit:
  return err;
}


OSStatus CreateHTTPMessage( const char *methold, const char *url, const char *contentType, uint8_t *inData, size_t inDataLen, uint8_t **outMessage, size_t *outMessageSize )
{
  uint8_t *endOfHTTPHeader;  
  OSStatus err = kParamErr;
    
  err = kNoMemoryErr;
  *outMessage = malloc( inDataLen + 500 );
  require( *outMessage, exit );
  
  // Create HTTP Response
  if(inDataLen)
    sprintf( (char*)*outMessage,
            "%s %s\? %s%s%s %s%s%s %d%s",
            methold, url, "HTTP/1.1", kCRLFNewLine, 
            "Content-Type:", contentType, kCRLFNewLine,
            "Content-Length:", (int)inDataLen, kCRLFLineEnding );
  else
    sprintf( (char*)*outMessage,
            "%s %s\? %s %s",
            methold, url, "HTTP/1.1", kCRLFLineEnding );
  
  // outMessageSize will be the length of the HTTP Header plus the data length
  *outMessageSize = strlen( (char*)*outMessage ) + inDataLen;
  
  endOfHTTPHeader = *outMessage + strlen( (char*)*outMessage );
  memcpy( endOfHTTPHeader, inData, inDataLen ); 
  err = kNoErr;
  
exit:
  return err;
}

OSStatus CreateHTTPMessageWithHost( const char *methold, const char *url, 
                           const char* host, uint16_t port, 
                           const char *contentType, 
                           uint8_t *inData, size_t inDataLen, 
                           uint8_t **outMessage, size_t *outMessageSize )
{
  uint8_t *endOfHTTPHeader;  
  OSStatus err = kParamErr;
    
  err = kNoMemoryErr;
  *outMessage = malloc( inDataLen + 500 );
  require( *outMessage, exit );
  
  // Create HTTP Response
  if(inDataLen)
    sprintf( (char*)*outMessage,
            "%s %s %s%s%s %s:%d%s%s %s%s%s %d%s",
            methold, url, "HTTP/1.1", kCRLFNewLine, 
            "Host:", host, port, kCRLFNewLine,
            "Content-Type:", contentType, kCRLFNewLine,
            "Content-Length:", (int)inDataLen, kCRLFLineEnding );
  else
    sprintf( (char*)*outMessage,
            "%s %s %s%s%s %s:%d%s",
            methold, url, "HTTP/1.1", kCRLFNewLine,
           "Host:", host, port, kCRLFLineEnding);
  
  // outMessageSize will be the length of the HTTP Header plus the data length
  *outMessageSize = strlen( (char*)*outMessage ) + inDataLen;
  
  endOfHTTPHeader = *outMessage + strlen( (char*)*outMessage );
  memcpy( endOfHTTPHeader, inData, inDataLen ); 
  err = kNoErr;
  
exit:
  return err;
}

void PrintHTTPHeader( HTTPHeader_t *inHeader )
{
  (void)inHeader; // Fix warning when debug=0
  //http_utils_log("Header:\n %s", inHeader->buf);
  // http_utils_log("Length: %d", (int)inHeader->len);
  // http_utils_log("Method: %s", inHeader->methodPtr);
  // http_utils_log("URL: %s", inHeader->urlPtr);
  // http_utils_log("Protocol: %s", inHeader->protocolPtr);
  // http_utils_log("Status Code: %d", inHeader->statusCode);
  // http_utils_log("ChannelID: %d", inHeader->channelID);
  // http_utils_log("Content length: %d", inHeader->contentLength);
  // http_utils_log("Persistent: %s", YesOrNo( inHeader->persistent ));
  //char *extraData = DataToHexString( (uint8_t*)inHeader->extraDataPtr, inHeader->extraDataLen );
  //http_utils_log("Extra data: %s", extraData );
  //if (extraData) free( extraData );
  //http_utils_log("contentlength: %d", inHeader->contentLength );
}

