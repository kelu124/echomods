/**
******************************************************************************
* @file    MicoSocket.h 
* @author  William Xu
* @version V1.0.0
* @date    16-Sep-2014
* @brief   This file provides all the headers of BSD socket APis.
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

#ifndef __MICOSOCKET_H__
#define __MICOSOCKET_H__

#include "Common.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup MICO_Core_APIs
* @{
*/

/** @defgroup MICO_SOCKET MICO Socket Operations
  * @brief Communicate with other device using TCP or UDP over MICO network
  * @{
  */

#define AF_INET       2
#define SOCK_STREAM   1
#define SOCK_DGRM     2 
#define IPPROTO_TCP   6
#define IPPROTO_UDP   17
#define SOL_SOCKET    1

#define INADDR_ANY        0x0
#define INADDR_BROADCAST  0xFFFFFFFF
#define IPADDR_LOOPBACK   0x7F000001

/**
  * @brief  Socket address structure define
  */
struct sockaddr_t {
  uint16_t        s_type;       /**<  Ignored in MICO */
  uint16_t        s_port;       /**<  Port number */
  uint32_t        s_ip;         /**<  IPv4 address. 32bit */
  uint16_t        s_spares[6];  /**<  Unused in TCP realm */
} ;

/**
  * @brief  Socket errno define
  */
#define  EPERM         1  /* Operation not permitted */
#define  ENOENT        2  /* No such file or directory */
#define  ESRCH         3  /* No such process */
#define  EINTR         4  /* Interrupted system call */
#define  EIO           5  /* I/O error */
#define  ENXIO         6  /* No such device or address */
#define  E2BIG         7  /* Arg list too long */
#define  ENOEXEC       8  /* Exec format error */
#define  EBADF         9  /* Bad file number */
#define  ECHILD       10  /* No child processes */
#define  EAGAIN       11  /* Try again */
#define  ENOMEM       12  /* Out of memory */
#define  EACCES       13  /* Permission denied */
#define  EFAULT       14  /* Bad address */
#define  ENOTBLK      15  /* Block device required */
#define  EBUSY        16  /* Device or resource busy */
#define  EEXIST       17  /* File exists */
#define  EXDEV        18  /* Cross-device link */
#define  ENODEV       19  /* No such device */
#define  ENOTDIR      20  /* Not a directory */
#define  EISDIR       21  /* Is a directory */
#define  EINVAL       22  /* Invalid argument */
#define  ENFILE       23  /* File table overflow */
#define  EMFILE       24  /* Too many open files */
#define  ENOTTY       25  /* Not a typewriter */
#define  ETXTBSY      26  /* Text file busy */
#define  EFBIG        27  /* File too large */
#define  ENOSPC       28  /* No space left on device */
#define  ESPIPE       29  /* Illegal seek */
#define  EROFS        30  /* Read-only file system */
#define  EMLINK       31  /* Too many links */
#define  EPIPE        32  /* Broken pipe */
#define  EDOM         33  /* Math argument out of domain of func */
#define  ERANGE       34  /* Math result not representable */
#define  EDEADLK      35  /* Resource deadlock would occur */
#define  ENAMETOOLONG 36  /* File name too long */
#define  ENOLCK       37  /* No record locks available */
#define  ENOSYS       38  /* Function not implemented */
#define  ENOTEMPTY    39  /* Directory not empty */
#define  ELOOP        40  /* Too many symbolic links encountered */
#define  ENOMSG       42  /* No message of desired type */
#define  EIDRM        43  /* Identifier removed */
#define  ECHRNG       44  /* Channel number out of range */
#define  EL2NSYNC     45  /* Level 2 not synchronized */
#define  EL3HLT       46  /* Level 3 halted */
#define  EL3RST       47  /* Level 3 reset */
#define  ELNRNG       48  /* Link number out of range */
#define  EUNATCH      49  /* Protocol driver not attached */
#define  ENOCSI       50  /* No CSI structure available */
#define  EL2HLT       51  /* Level 2 halted */
#define  EBADE        52  /* Invalid exchange */
#define  EBADR        53  /* Invalid request descriptor */
#define  EXFULL       54  /* Exchange full */
#define  ENOANO       55  /* No anode */
#define  EBADRQC      56  /* Invalid request code */
#define  EBADSLT      57  /* Invalid slot */
    
#define  EDEADLOCK    EDEADLK
    
#define  EBFONT       59  /* Bad font file format */
#define  ENOSTR       60  /* Device not a stream */
#define  ENODATA      61  /* No data available */
#define  ETIME        62  /* Timer expired */
#define  ENOSR        63  /* Out of streams resources */
#define  ENONET       64  /* Machine is not on the network */
#define  ENOPKG       65  /* Package not installed */
#define  EREMOTE      66  /* Object is remote */
#define  ENOLINK      67  /* Link has been severed */
#define  EADV         68  /* Advertise error */
#define  ESRMNT       69  /* Srmount error */
#define  ECOMM        70  /* Communication error on send */
#define  EPROTO       71  /* Protocol error */
#define  EMULTIHOP    72  /* Multihop attempted */
#define  EDOTDOT      73  /* RFS specific error */
#define  EBADMSG      74  /* Not a data message */
#define  EOVERFLOW    75  /* Value too large for defined data type */
#define  ENOTUNIQ     76  /* Name not unique on network */
#define  EBADFD       77  /* File descriptor in bad state */
#define  EREMCHG      78  /* Remote address changed */
#define  ELIBACC      79  /* Can not access a needed shared library */
#define  ELIBBAD      80  /* Accessing a corrupted shared library */
#define  ELIBSCN      81  /* .lib section in a.out corrupted */
#define  ELIBMAX      82  /* Attempting to link in too many shared libraries */
#define  ELIBEXEC     83  /* Cannot exec a shared library directly */
#define  EILSEQ       84  /* Illegal byte sequence */
#define  ERESTART     85  /* Interrupted system call should be restarted */
#define  ESTRPIPE     86  /* Streams pipe error */
#define  EUSERS       87  /* Too many users */
#define  ENOTSOCK     88  /* Socket operation on non-socket */
#define  EDESTADDRREQ 89  /* Destination address required */
#define  EMSGSIZE     90  /* Message too long */
#define  EPROTOTYPE   91  /* Protocol wrong type for socket */
#define  ENOPROTOOPT  92  /* Protocol not available */
#define  EPROTONOSUPPORT 93  /* Protocol not supported */
#define  ESOCKTNOSUPPORT 94  /* Socket type not supported */
#define  EOPNOTSUPP      95  /* Operation not supported on transport endpoint */
#define  EPFNOSUPPORT    96  /* Protocol family not supported */
#define  EAFNOSUPPORT    97  /* Address family not supported by protocol */
#define  EADDRINUSE      98  /* Address already in use */
#define  EADDRNOTAVAIL   99  /* Cannot assign requested address */
#define  ENETDOWN       100  /* Network is down */
#define  ENETUNREACH    101  /* Network is unreachable */
#define  ENETRESET      102  /* Network dropped connection because of reset */
#define  ECONNABORTED   103  /* Software caused connection abort */
#define  ECONNRESET     104  /* Connection reset by peer */
#define  ENOBUFS        105  /* No buffer space available */
#define  EISCONN        106  /* Transport endpoint is already connected */
#define  ENOTCONN       107  /* Transport endpoint is not connected */
#define  ESHUTDOWN      108  /* Cannot send after transport endpoint shutdown */
#define  ETOOMANYREFS   109  /* Too many references: cannot splice */
#define  ETIMEDOUT      110  /* Connection timed out */
#define  ECONNREFUSED   111  /* Connection refused */
#define  EHOSTDOWN      112  /* Host is down */
#define  EHOSTUNREACH   113  /* No route to host */
#define  EALREADY       114  /* Operation already in progress */
#define  EINPROGRESS    115  /* Operation now in progress */
#define  ESTALE         116  /* Stale NFS file handle */
#define  EUCLEAN        117  /* Structure needs cleaning */
#define  ENOTNAM        118  /* Not a XENIX named type file */
#define  ENAVAIL        119  /* No XENIX semaphores available */
#define  EISNAM         120  /* Is a named type file */
#define  EREMOTEIO      121  /* Remote I/O error */
#define  EDQUOT         122  /* Quota exceeded */
    
#define  ENOMEDIUM      123  /* No medium found */
#define  EMEDIUMTYPE    124  /* Wrong medium type */
    
    
#define ENSROK                    0 /* DNS server returned answer with no data */
#define ENSRNODATA              160 /* DNS server returned answer with no data */
#define ENSRFORMERR             161 /* DNS server claims query was misformatted */
#define ENSRSERVFAIL            162 /* DNS server returned general failure */
#define ENSRNOTFOUND            163 /* Domain name not found */
#define ENSRNOTIMP              164 /* DNS server does not implement requested operation */
#define ENSRREFUSED             165 /* DNS server refused query */
#define ENSRBADQUERY            166 /* Misformatted DNS query */
#define ENSRBADNAME             167 /* Misformatted domain name */
#define ENSRBADFAMILY           168 /* Unsupported address family */
#define ENSRBADRESP             169 /* Misformatted DNS reply */
#define ENSRCONNREFUSED         170 /* Could not contact DNS servers */
#define ENSRTIMEOUT             171 /* Timeout while contacting DNS servers */
#define ENSROF                  172 /* End of file */
#define ENSRFILE                173 /* Error reading file */
#define ENSRNOMEM               174 /* Out of memory */
#define ENSRDESTRUCTION         175 /* Application terminated lookup */
#define ENSRQUERYDOMAINTOOLONG  176 /* Domain name is too long */
#define ENSRCNAMELOOP           177 /* Domain name is too long */



/**
  * @brief  Time interval define used in @ref select
  */
struct timeval_t {
  unsigned long		tv_sec;		/**< seconds */
  unsigned long		tv_usec;	/**< microseconds */
};

typedef int socklen_t;

/**
  * @brief  Socket option types
  */
typedef enum {
  SO_REUSEADDR            = 0x0002,     /**< MICO socket always support this option. */
  SO_BROADCAST            = 0x0006,     /**< MICO socket always support this option. */
  IP_ADD_MEMBERSHIP       = 0x0003,     /**< Join multicast group. */
  IP_DROP_MEMBERSHIP      = 0x0004,     /**< Leave Multicast group. */
  TCP_CONN_NUM            = 0x0006,     /**< Read the current connected TCP client number. */
  TCP_MAX_CONN_NUM        = 0x0007,     /**< Set the max number of TCP client that server can support. */
  SO_BLOCKMODE            = 0x1000,     /**< set socket as block(optval=0)/non-block(optval=1) mode. 
                                             Default is block mode. */
  SO_SNDTIMEO             = 0x1005,     /**< Send timeout in block mode. block for ever in dafault mode. */
  SO_RCVTIMEO             = 0x1006,     /**< Recv timeout in block mode. block 1 second in default mode. */
  SO_ERROR                = 0x1007,     /**< Get socket error number. */
  SO_TYPE                 = 0x1008,     /**< Get socket type. */
  SO_NO_CHECK             = 0x100a      /**< Don't create UDP checksum. */
} SOCK_OPT_VAL;

#define FD_SETSIZE        24    /**< MAX fd number is 24 in MICO. */


#define NBBY              8     /**< number of bits in a byte. */
#define NFDBITS (sizeof(unsigned long) * NBBY)        /**< bits per mask */


#define MAX_TCP_CLIENT_PER_SERVER  5


#define howmany(x, y)   (((x) + ((y) - 1)) / (y))

typedef struct fd_set {
  unsigned long   fds_bits[howmany(FD_SETSIZE, NFDBITS)];
} fd_set;

#define _fdset_mask(n)    ((unsigned long)1 << ((n) % NFDBITS))

#define FD_SET(n, p)      ((p)->fds_bits[(n)/NFDBITS] |= _fdset_mask(n))  /**< Add a fd to FD set. */
#define FD_CLR(n, p)      ((p)->fds_bits[(n)/NFDBITS] &= ~_fdset_mask(n)) /**< Remove fd from FD set. */
#define FD_ISSET(n, p)    ((p)->fds_bits[(n)/NFDBITS] & _fdset_mask(n))   /**< Check if the fd is set in FD set. */
#define FD_ZERO(p)        memset(p, 0, sizeof(*(p)))                      /**< Clear FD set. */

/** @defgroup MICO_SOCKET_GROUP_1 MICO BSD-like Socket Functions
  * @{
  */

/**
  * @brief  Create an endpoint for communication
  * @attention  Never doing operations on one socket in different MICO threads
  * @param  domain: Specifies a communication domain; this selects the protocol
  *         family which will be used for communication. 
  *           This parameter can be one value:
  *             @arg AF_INET: IPv4 Internet protocols.
  * @param  type: Specifies the communication semantics.
  *           This parameter can be one of the following values:
  *             @arg SOCK_STREAM: Provides sequenced, reliable, two-way, 
  *                    connection-based byte streams.  An out-of-band data 
  *                    transmission mechanism may be supported. (TCP)
  *             @arg SOCK_DGRAM: Supports datagrams (connectionless, unreliable
  *                    messages of a fixed maximum length).(UDP)
  * @param  protocol: specifies a particular protocol to be used with the socket.
  *            This parameter can be one of the following values:
  *             @arg IPPROTO_TCP: TCP protocol
  *             @arg IPPROTO_UDP: UDP protocol
  * @retval On success, a file descriptor for the new socket is returned.  
            On error, -1 is returned.
  */
int socket(int domain, int type, int protocol);

/**
  * @brief  Set options on sockets
  * @attention  Never doing operations on one socket in different MICO threads
  * @param  sockfd: A file descriptor
  * @param  level: This parameter can be one value: SOL_SOCKET
  * @param  optname: This parameter is defined in SOCK_OPT_VAL
  * @param  optval: address of buffer in which the value for the requested option(s) 
  *         are to be set.
  * @param  optlen: containing the size of the buffer pointed to by optval
  * @retval On success, zero is returned.  On error, -1 is returned.
  */
int setsockopt(int sockfd, int level, int optname,const void *optval, socklen_t optlen);

/**
  * @brief  Get options on sockets
  * @attention  Never doing operations on one socket in different MICO threads
  * @param  sockfd: A file descriptor
  * @param  level: This parameter can be one value: SOL_SOCKET
  * @param  optname: This parameter is defined in SOCK_OPT_VAL
  * @param  optval: address of buffer in which the value for the requested option(s)
  *         are to be returned.
  * @param  optlen: This is a value-result argument, initially containing the size 
  *         of the buffer pointed to by optval, and modified on return to indicate 
  *         the actual size of the value returned. 
  * @retval On success, zero is returned.  On error, -1 is returned.
  */
int getsockopt(int sockfd, int level, int optname,const void *optval, socklen_t *optlen);

/**
  * @brief  bind a name to a socket
  * @attention  Never doing operations on one socket in different MICO threads
  * @note   Assigns the address specified by addr to the socket referred to by the file
  *         descriptor sockfd.
  * @param  sockfd: A file descriptor
  * @param  addr: Point to the target address to be binded
  * @param  addrlen: This parameter containing the size of the buffer pointed to by addr
  * @retval On success, zero is returned.  On error, -1 is returned.
  */
int bind(int sockfd, const struct sockaddr_t *addr, socklen_t addrlen);

/**
  * @brief    Initiate a connection on a socket
  * @attention  Never doing operations on one socket in different MICO threads
  * @details  The connect() system call connects the socket referred to by the file
  *           descriptor sockfd to the address specified by addr. 
  * @param    sockfd: A file descriptor
  * @param    addr: Point to the target address to be binded
  * @param    addrlen: This parameter containing the size of the buffer pointed to by addr
  * @retval   On success, zero is returned.  On error, -1 is returned.
  */
int connect(int sockfd, const struct sockaddr_t *addr, socklen_t addrlen);

/**
  * @brief    Listen for connections on a socket
  * @attention  Never doing operations on one socket in different MICO threads
  * @details  listen() marks the socket referred to by sockfd as a passive socket,
  *           that is, as a socket that will be used to accept incoming connection
  *           requests using accept().
  * @param    sockfd: a file descriptor.
  * @param    backlog: Defines the maximum length to which the queue of pending
  *           connections for sockfd may grow. This parameter is not used in MICO, 
  *           use 0 is fine.
  * @retval   On success, zero is returned.  On error, -1 is returned.
  */
int listen(int sockfd, int backlog);

/**
  * @brief    Accept a connection on a socket
  * @attention  Never doing operations on one socket in different MICO threads
  * @details  The accept() system call is used with connection-based socket types
  *           (SOCK_STREAM).  It extracts the first connection request on the queue
  *           of pending connections for the listening socket, sockfd, creates a 
  *           new connected socket, and returns a new file descriptor referring to 
  *           that socket.  The newly created socket is not in the listening state.  
  *           The original socket sockfd is unaffected by this call.
  * @param    sockfd: A file descriptor.
  * @param    addr: Point to the buffer to store the address of the accepted client.
  * @param    addrlen: This parameter containing the size of the buffer pointed to 
  *             by addr.
  * @retval   On success, zero is returned.  On error, -1 is returned.
  */
int accept(int sockfd, struct sockaddr_t *addr, socklen_t *addrlen);

/**
  * @brief      Monitor multiple file descriptors, waiting until one or more of the 
  *             file descriptors become "ready" for some class of I/O operation 
  *             (e.g., input possible). 
  * @attention  Never doing operations on one socket in different MICO threads
  * @note       A file descriptor is considered ready if it is possible to perform 
  *             the corresponding I/O operation (e.g., read()) without blocking.
  * @param      nfds: is the highest-numbered file descriptor in any of the three
  *             sets, plus 1. In MICO, the mount of file descriptors is fewer, so  
  *             MICO use the MAX number of these file descriptors inside, and this 
  *             parameter is cared.
  * @param      readfds: A file descriptor sets will be watched to see if characters 
  *             become available for readingã€?
  * @param      writefds: A file descriptor sets will be watched to see if a write 
  *             will not block.
  * @param      exceptfds: A file descriptor sets will be watched for exceptions.
  * @param      timeout: The timeout argument specifies the interval that select() 
  *             should block waiting for a file descriptor to become ready. 
  *             If timeout is NULL (no timeout), select() can block indefinitely.   
  * @retval     On success, return the number of file descriptors contained in the 
  *             three returned descriptor sets (that is, the total number of bits 
  *             that are set in readfds, writefds, exceptfds) which may be zero if 
  *             the timeout expires before anything interesting happens.  On error, 
  *             -1 is returned, the file descriptor sets are unmodified, and timeout 
  *             becomes undefined.
  */
int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval_t *timeout);

/**
  * @brief      Send a message on a socket
  * @attention  Never doing operations on one socket in different MICO threads
  * @details    The send() call may be used only when the socket is in a connected
  *             state (so that the intended recipient is known). The only difference
  *             between send() and write() is the presence of flags.  With a zero
  *             flags argument, send() is equivalent to write().
  * @note       When the message does not fit into the send buffer of the socket,
  *             send() normally blocks, unless the socket has been placed in
  *             nonblocking I/O mode.  In nonblocking mode it would fail. The select()
  *             call may be used to determine when it is possible to send more data.        
  * @param      sockfd: A file descriptor.
  * @param      buf: Point to the send data buffer.
  * @param      len: Length of the send data buffer.
  * @param      flags: Zero in MICO.
  * @retval     On success, these calls return the number of bytes sent.  On error,
  *             -1 is returned,
  */
ssize_t send(int sockfd, const void *buf, size_t len, int flags);

/**
  * @brief      Send a message on a socket
  * @attention  Never doing operations on one socket in different MICO threads
  * @note       Refer send() for details.
  */
int write(int sockfd, void *buf, size_t len); 


/**
  * @brief      Send a message on a socket to a specific target address.
  * @attention  Never doing operations on one socket in different MICO threads
  * @details    Refer send() for details. If sendto() is used on a connection-mode 
  *             (SOCK_STREAM, SOCK_SEQPACKET) socket, the arguments dest_addr and 
  *             addrlen are ignored. Otherwise, the address of the target is given by
  *             dest_addr with addrlen specifying its size. 
  * @param      sockfd: Refer send() for details.
  * @param      buf: Refer send() for details.
  * @param      len: Refer send() for details.
  * @param      flags: Refer send() for details.
  * @param      dest_addr: Point to the target address.
  * @param      addrlen: This parameter containing the size of the buffer pointed to 
  *             by dest_addr.
  * @retval     On success, these calls return the number of bytes sent.  On error,
  *             -1 is returned,
  */
ssize_t sendto(int  sockfd, const void *buf,  size_t len,  int flags, 
              const struct sockaddr_t  *dest_addr, socklen_t addrlen);


/**
  * @brief      Receive a message from a socket.
  * @attention  Never doing operations on one socket in different MICO threads
  * @details    If no messages are available at the socket, the receive calls wait
  *             for a message to arrive, unless the socket is nonblocking, in 
  *             which case the value -1 is returned.  The receive calls normally 
  *             return any data available, up to the requested amount, rather than 
  *             waiting for receipt of the full amount requested.
  * @param      sockfd: A file descriptor.
  * @param      buf: Point to the send data buffer.
  * @param      len: Length of the send data buffer.
  * @param      flags: Zero in MICO.
  * @retval     These calls return the number of bytes received, or -1 if an error
  *             occurred.
  *             When a stream socket peer has performed an orderly shutdown, the
  *             return value will be 0 (the traditional "end-of-file" return).
  *             The value 0 may also be returned if the requested number of bytes to
  *             receive from a stream socket was 0.
  */
ssize_t recv(int sockfd, void *buf, size_t len, int flags);

/**
  * @brief      Receive a message from a socket.
  * @attention  Never doing operations on one socket in different MICO threads
  * @note       Refer recv() for details.
  */
int read(int sockfd, void *buf, size_t len);


/**
  * @brief      Receive a message from a socket and get the source address.
  * @attention  Never doing operations on one socket in different MICO threads
  * @details    If src_addr is not NULL, and the underlying protocol provides 
  *             the source address of the message, that source address is placed 
  *             in the buffer pointed to by src_addr.  In this case, addrlen is 
  *             a value-result argument.  Before the call, it should be 
  *             initialized to the size of the buffer associated with src_addr. 
  *             Upon return, addrlen is updated to contain the actual size of 
  *             the source address.  The returned address is truncated if the 
  *             buffer provided is too small; in this case, addrlen will return 
  *             a value greater than was supplied to the call.
  *             If the caller is not interested in the source address, src_addr
  *             should be specified as NULL and addrlen should be specified as 0.
  * @param      sockfd: Refer recv() for details.
  * @param      buf: Refer recv() for details.
  * @param      len: Refer recv() for details.
  * @param      flags: Refer recv() for details.
  * @param      src_addr: Point to the buffer to store the source address.
  * @param      addrlen: This parameter containing the size of the buffer pointed to 
  *             by src_addr.
  * @retval     These calls return the number of bytes received, or -1 if an 
  *             error occurred.
  *             When a stream socket peer has performed an orderly shutdown, the
  *             return value will be 0 (the traditional "end-of-file" return).
  *             The value 0 may also be returned if the requested number of bytes to
  *             receive from a stream socket was 0.
  */
ssize_t recvfrom(int  sockfd,  void  *buf,  size_t  len,  int  flags, 
              struct  sockaddr_t  *src_addr,  socklen_t *addrlen);
 
/**
  * @brief      Close a file descriptor.
  * @attention  Never doing operations on one socket in different MICO threads
  * @details    closes a file descriptor, so that it no longer refers to any
  *             file and may be reused.the resources associated with the
  *             open file description are freed.
  * @param      fd: A file descriptor.
  * @retval     Returns zero on success.  On error, -1 is returned.
  */
int close(int fd);
/**
  * @}
  */


/** @defgroup MICO_SOCKET_GROUP_2 MICO Socket Tool Functions
  * @{
  */

/**
  * @brief      converts the Internet host address from IPv4 numbers-and-dots 
  *             notation into binary data in network byte order
  * @note       If the input is invalid, INADDR_NONE (usually -1) is returned. 
  * @param      s: Internet host address from IPv4 numbers-and-dots.
  * @retval     Returns zero on success.  On error, -1 is returned.
  */
uint32_t inet_addr(char *s); 


/**
  * @brief      Converts the Internet host address in, given in network byte 
  *             order, to a string in IPv4 dotted-decimal notation. 
  * @note       The returned string is stored in a given buffer, and the buffer 
  *             size should larger than 16.
  * @param      s: Point to a buffer to store the returned string in IPv4 
  *             dotted-decimal
  * @param      x: the Internet host address in.
  * @retval     Returns the same value as param s.
  */
char *inet_ntoa( char *s, uint32_t x );


/** @brief      Get the IP address from a host name. 
  * 
  * @note       Different to stand BSD function type, this function in MICO do
  *             not return a buffer that contain the result, but write the result
  *             to a buffer provided by application. Also this function simplify
  *             the return value compared to the standard BSD version. 
  *             This functon runs under block mode.
  *
  * @param      name: This parameter is either a hostname, or an IPv4 address in
  *             standard dot notation.
  * @param      addr: Point to a buffer to store the returned string in IPv4 
  *             dotted-decimal
  * @param      addrLen: This parameter containing the size of the buffer pointed 
  *             to by addr, 16 is recommended.
  * @retval     kNoerr or kGeneralErr
  */
int gethostbyname(const char * name, uint8_t * addr, uint8_t addrLen);


/** @brief      Set TCP keep-alive mechanism parameters. 
 *
 *  @details    When TCP data is not transimitting for a certain time (defined by seconds), 
 *              MICO send keep-alive package over the TCP socket, and the remote device  
 *              should return the keep-alive back to MICO. This is a basic TCP function 
 *              deployed on every TCP/IP stack and application's interaction is not required. 
 *              If the remote device doesn't return the keep-alive package, MICO add 1 to an 
 *              internal counter, and close the current socket connection once this count has 
 *              reached the maxErrNum (defined in parm: maxErrNum). 
 *
 *  @param      inMaxErrNum: The max possible count that the remote device doesn't return the 
 *              keep-alive package. If remote device returns, the internal count is cleared 
 *              to 0. 
 *  @param      inSeconds: The time interval between two keep-alive package
 *
 *  @retval     kNoerr or kGeneralErr
 */
void set_tcp_keepalive(int inMaxErrNum, int inSeconds);


/** @brief      Get TCP keep-alive mechanism parameters. Refer to @ref set_tcp_keepalive
 *
 *  @param      outMaxErrNum: Point to the address that store the maxErrNumber.
 *  @param      outSeconds: Point to the address that store the time interval between two
 *              keep-alive package.
 *
 *  @retval     kNoerr or kGeneralErr
 */
void get_tcp_keepalive(int *outMaxErrNum, int *outSeconds);


/* SSL */
/** @brief      Used by the SSL server. Set the certificate and private key for a SSL server. 
 *
 * @details    This function is called on the server side to set it's certifact and private key.
 *              It must be called before ssl_accept. These two arguments must be global
 *              string buffer, library will not create a copy for them.
 *
 *  @param      _cert_pem: Point to the certificate string in PEM format.
 *  @param      private_key_pem: Point to the private key string in PEM format.
 *
 *  @retval     void
 */
void ssl_set_cert(const char *_cert_pem, const char *private_key_pem);

/** @brief      SSL client create a SSL connection.
 *
 * @details    This function is called on the client side and initiates an SSL/TLS handshake with a 
 *              server.  When this function is called, the underlying communication channel has already 
 *              been set up. This function is called after TCP 3-way handshak finished. 
 *
 *  @param      fd: The fd number for a connected TCP socket.
 *  @param      calen: the string length of ca. 0=do not verify server's certificate.
 *  @param      ca: pointer to the CA certificate string, used to verify server's certificate.
 *  @param      errno: return the errno if ssl_connect return NULL.
 *
 *  @retval     return the SSL context pointer on success or NULL for fail.
 */
void* ssl_connect(int fd, int calen, char*ca, int *errno); 

/** @brief      SSL Server accept a SSL connection
 *
 *  @param      fd: The fd number for a connected TCP socket.
 *
 *  @retval     return the SSL context pointer on success or NULL for fail.
 */
void* ssl_accept(int fd); 


/** @brief      SSL send data
 *
 *  @param      ssl: Point to the SSL context.
 *  @param      data: Point to send data.
 *  @param      len: data length.
 *
 *  @retval     On success, these calls return the number of bytes sent.  On error,
 *             -1 is returned,
 */
int ssl_send(void* ssl, char *data, int len);

/** @brief      SSL receive data
 *
 *  @param      ssl: Point to the SSL context.
 *  @param      data: Point to buffer to receive SSL data.
 *  @param      len: max receive buffer length.
 *
 *  @retval     On success, these calls return the number of bytes received.  On error,
 *             -1 is returned,
 */
int ssl_recv(void* ssl, char *data, int len);

/** @brief      Close the SSL session, release resource.
 *
 *  @param      ssl: Point to the SSL context.
 *
 *  @retval     kNoerr or kGeneralErr
 */
int ssl_close(void* ssl);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
#ifdef __cplusplus
}
#endif

#endif /*__MICO_SOCKET_H__*/



