/**
******************************************************************************
* @file    SHAUtils.h 
* @author  William Xu
* @version V1.0.0
* @date    05-May-2014
* @brief   SHA Utilities
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


#ifndef __SHAUtils_h_
#define __SHAUtils_h_

#include "Common.h"


//===========================================================================================================================
//  SHA-1
//===========================================================================================================================

typedef struct
{
    uint64_t        length;
    uint32_t        state[ 5 ];
    uint32_t        curlen;
    uint8_t         buf[ 64 ];
    
}   SHA_CTX_compat;

int SHA1_Init_compat( SHA_CTX_compat *ctx );
int SHA1_Update_compat( SHA_CTX_compat *ctx, const void *inData, size_t inLen );
int SHA1_Final_compat( unsigned char *outDigest, SHA_CTX_compat *ctx );
unsigned char * SHA1_compat( const void *inData, size_t inLen, unsigned char *outDigest );

//===========================================================================================================================
//  SHA-512
//===========================================================================================================================

typedef struct
{
    uint64_t        length;
    uint64_t        state[ 8 ];
    size_t          curlen;
    uint8_t         buf[ 128 ];
    
}   SHA512_CTX_compat;

int SHA512_Init_compat( SHA512_CTX_compat *ctx );
int SHA512_Update_compat( SHA512_CTX_compat *ctx, const void *inData, size_t inLen );
int SHA512_Final_compat( unsigned char *outDigest, SHA512_CTX_compat *ctx );
unsigned char * SHA512_compat( const void *inData, size_t inLen, unsigned char *outDigest );

//===========================================================================================================================
//  SHA-3 (Keccak)
//===========================================================================================================================

#define SHA3_DIGEST_LENGTH      64
#define SHA3_F                  1600
#define SHA3_C                  ( SHA3_DIGEST_LENGTH * 8 * 2 )  // 512=1024
#define SHA3_R                  ( SHA3_F - SHA3_C )             // 512=576
#define SHA3_BLOCK_SIZE         ( SHA3_R / 8 )

typedef struct
{
    uint64_t        state[ SHA3_F / 64 ];
    size_t          leftover;
    uint8_t         buffer[ SHA3_BLOCK_SIZE ];
    
}   SHA3_CTX_compat;

int SHA3_Init_compat( SHA3_CTX_compat *ctx );
int SHA3_Update_compat( SHA3_CTX_compat *ctx, const void *inData, size_t inLen );
int SHA3_Final_compat( unsigned char *outDigest, SHA3_CTX_compat *ctx );
uint8_t *   SHA3_compat( const void *inData, size_t inLen, uint8_t outDigest[ 64 ] );

#endif // __SHAUtils_h_


