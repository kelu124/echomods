/**
  ******************************************************************************
  * @file    SocketUtils.c 
  * @author  William Xu
  * @version V1.0.0
  * @date    05-May-2014
  * @brief   This file contains function called by socket operation
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

#include "SocketUtils.h"
#include "Debug.h"
#include "MICO.h"

#define socket_utils_log(M, ...) custom_log("SocketUtils", M, ##__VA_ARGS__)
#define socket_utils_log_trace() custom_log_trace("SocketUtils")

OSStatus SocketSend( int fd, const uint8_t *inBuf, size_t inBufLen )
{
    socket_utils_log_trace();
    OSStatus err = kParamErr;
    ssize_t writeResult;
    int selectResult;
    size_t numWritten;
    fd_set writeSet;
    struct timeval_t t;

    require( fd>=0, exit );
    require( inBuf, exit );
    require( inBufLen, exit );

    err = kNotWritableErr;

    FD_ZERO( &writeSet );
    FD_SET( fd, &writeSet );

    t.tv_sec = 5;
    t.tv_usec = 0;
    numWritten = 0;
    do
    {
        selectResult = select( fd + 1, NULL, &writeSet, NULL,  &t );
        require( selectResult >= 1, exit );

        writeResult = write( fd, (void *)( inBuf + numWritten ), ( inBufLen - numWritten ) );
        require( writeResult > 0, exit );

        numWritten += writeResult;

        //socket_utils_log("Wrote %zu / %zu bytes", numWritten, inBufLen);

    } while( numWritten < inBufLen );

    require_action( numWritten == inBufLen,
                    exit,
                    socket_utils_log("ERROR: Did not write all the bytes in the buffer. BufLen: %zu, Bytes Written: %zu", inBufLen, numWritten ); err = kUnderrunErr );

    err = kNoErr;

exit:
    return err;
}

void SocketClose(int* fd)
{
    int tempFd = *fd;
    if ( tempFd < 0 )
      return;
    *fd = -1;
    close(tempFd);
}

void SocketCloseForOSEvent(int* fd)
{
    int tempFd = *fd;
    if ( tempFd < 0 )
      return;
    *fd = -1;
    mico_delete_event_fd(tempFd);
}

void SocketAccept(int *plocalTcpClientsPool, int maxClientsNum, int newFd)
{
    int minFd = plocalTcpClientsPool[0];
    int minFdIndex = 0;
    int i;

    for(i = 0; i < maxClientsNum; i++) {
        if(minFd >= plocalTcpClientsPool[i]){
            minFd = plocalTcpClientsPool[i];
            minFdIndex = i;
        }
    }

    if(minFd != -1){
        SocketClose(&minFd);
        socket_utils_log("Force close, %d@%d", minFd, minFdIndex);
    }
          
    plocalTcpClientsPool[minFdIndex] = newFd;  
}

