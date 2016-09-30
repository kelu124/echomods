/**
******************************************************************************
* @file    SHAUtils.c 
* @author  William Xu
* @version V1.0.0
* @date    05-May-2014
* @brief   SHA Utilities, Port of libtom's SHA-1, SHA-256, and SHA-512 code.
*          Port of floodyberry's SHA-3 code.
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

#include "SHAUtils.h"

#include "Common.h"
#include "Debug.h"

#include "StringUtils.h"

//===========================================================================================================================
//  SHA-1 internals
//===========================================================================================================================

#define SHA1_BLOCK_SIZE     64

static void _SHA1_Compress( SHA_CTX_compat *ctx, const uint8_t *inPtr );

//===========================================================================================================================
//  SHA1_Init_compat
//===========================================================================================================================

int SHA1_Init_compat( SHA_CTX_compat *ctx )
{
    ctx->length = 0;
    ctx->state[ 0 ] = UINT32_C( 0x67452301 );
    ctx->state[ 1 ] = UINT32_C( 0xefcdab89 );
    ctx->state[ 2 ] = UINT32_C( 0x98badcfe );
    ctx->state[ 3 ] = UINT32_C( 0x10325476 );
    ctx->state[ 4 ] = UINT32_C( 0xc3d2e1f0 );
    ctx->curlen = 0;
    return( 0 );
}

//===========================================================================================================================
//  SHA1_Update_compat
//===========================================================================================================================

int SHA1_Update_compat( SHA_CTX_compat *ctx, const void *inData, size_t inLen )
{
    const uint8_t *     src = (const uint8_t *) inData;
    size_t              n;
    
    while( inLen > 0 )
    {
        if( ( ctx->curlen == 0 ) && ( inLen >= SHA1_BLOCK_SIZE ) )
        {
            _SHA1_Compress( ctx, src );
            ctx->length += ( SHA1_BLOCK_SIZE * 8 );
            src         += SHA1_BLOCK_SIZE;
            inLen       -= SHA1_BLOCK_SIZE;
        }
        else
        {
            n = Min( inLen, SHA1_BLOCK_SIZE - ctx->curlen );
            memcpy( ctx->buf + ctx->curlen, src, n );
            ctx->curlen += n;
            src         += n;
            inLen       -= n;
            if( ctx->curlen == SHA1_BLOCK_SIZE )
            {
                _SHA1_Compress( ctx, ctx->buf );
                ctx->length += ( SHA1_BLOCK_SIZE * 8 );
                ctx->curlen = 0;
            }
        }
    }
    return( 0 );
}

//===========================================================================================================================
//  SHA1_Final_compat
//===========================================================================================================================

int SHA1_Final_compat( unsigned char *outDigest, SHA_CTX_compat *ctx )
{
    int     i;
     
    ctx->length += ctx->curlen * 8;
    ctx->buf[ ctx->curlen++ ] = 0x80;
    
    // If length > 56 bytes, append zeros then compress. Then fall back to padding zeros and length encoding like normal.
    if( ctx->curlen > 56 )
    {
        while( ctx->curlen < 64 ) ctx->buf[ ctx->curlen++ ] = 0;
        _SHA1_Compress( ctx, ctx->buf );
        ctx->curlen = 0;
    }

    // Pad up to 56 bytes of zeros.
    while( ctx->curlen < 56 ) ctx->buf[ ctx->curlen++ ] = 0;
    
    // Store length.
    WriteBig64( ctx->buf + 56, ctx->length );
    _SHA1_Compress( ctx, ctx->buf );

    // Copy output.
    for( i = 0; i < 5; ++i )
    {
        WriteBig32( outDigest + ( 4 * i ), ctx->state[ i ] );
    }
    memset( ctx, 0, sizeof( *ctx ) ); // Zero sensitive info.
    return( 0 );
}

//===========================================================================================================================
//  SHA1_compat
//===========================================================================================================================

unsigned char * SHA1_compat( const void *inData, size_t inLen, unsigned char *outDigest )
{
    SHA_CTX_compat      ctx;
    
    SHA1_Init_compat( &ctx );
    SHA1_Update_compat( &ctx, inData, inLen );
    SHA1_Final_compat( outDigest, &ctx );
    return( outDigest );
}

//===========================================================================================================================
//  _SHA1_Compress
//===========================================================================================================================

#define SHA1_F0( x, y, z )              (z ^ ( x & ( y ^ z ) ) )
#define SHA1_F1( x, y, z )              (x ^ y ^ z )
#define SHA1_F2( x, y, z )              ( ( x & y ) | ( z & ( x | y ) ) )
#define SHA1_F3( x, y, z )              (x ^ y ^ z )
#define SHA1_FF0( a, b, c, d, e, i )    e = ( ROTL32( a, 5 ) + SHA1_F0( b, c, d ) + e + W[ i ] + UINT32_C( 0x5a827999 ) ); b = ROTL32( b, 30);
#define SHA1_FF1( a, b, c, d, e, i )    e = ( ROTL32( a, 5 ) + SHA1_F1( b, c, d ) + e + W[ i ] + UINT32_C( 0x6ed9eba1 ) ); b = ROTL32( b, 30);
#define SHA1_FF2( a, b, c, d, e, i )    e = ( ROTL32( a, 5 ) + SHA1_F2( b, c, d ) + e + W[ i ] + UINT32_C( 0x8f1bbcdc ) ); b = ROTL32( b, 30);
#define SHA1_FF3( a, b, c, d, e, i )    e = ( ROTL32( a, 5 ) + SHA1_F3( b, c, d ) + e + W[ i ] + UINT32_C( 0xca62c1d6 ) ); b = ROTL32( b, 30);

static void _SHA1_Compress( SHA_CTX_compat *ctx, const uint8_t *inPtr )
{
    uint32_t        a, b, c, d, e, W[ 80 ], i, tmp;
    
    // Copy the state into 512-bits into W[0..15].
    for( i = 0; i < 16; ++i )
    {
        W[ i ] = ReadBig32( inPtr );
        inPtr += 4;
    }
    
    // Copy state
    a = ctx->state[ 0 ];
    b = ctx->state[ 1 ];
    c = ctx->state[ 2 ];
    d = ctx->state[ 3 ];
    e = ctx->state[ 4 ];
    
    // Expand it
    for( i = 16; i < 80; ++i )
    {
        tmp = W[ i-3 ] ^ W[ i-8 ] ^ W[ i-14 ] ^ W[ i-16 ];
        W[ i ] = ROTL32( tmp, 1 ); 
    }
    
    // Compress
    // Round 1
    for( i = 0; i < 20; )
    {
        SHA1_FF0( a, b, c, d, e, i++ );
        SHA1_FF0( e, a, b, c, d, i++ );
        SHA1_FF0( d, e, a, b, c, i++ );
        SHA1_FF0( c, d, e, a, b, i++ );
        SHA1_FF0( b, c, d, e, a, i++ );
    }
    
    // Round 2
    for( ; i < 40; )
    { 
        SHA1_FF1( a, b, c, d, e, i++ );
        SHA1_FF1( e, a, b, c, d, i++ );
        SHA1_FF1( d, e, a, b, c, i++ );
        SHA1_FF1( c, d, e, a, b, i++ );
        SHA1_FF1( b, c, d, e, a, i++ );
    }
    
    // Round 3
    for( ; i < 60; )
    { 
        SHA1_FF2( a, b, c, d, e, i++ );
        SHA1_FF2( e, a, b, c, d, i++ );
        SHA1_FF2( d, e, a, b, c, i++ );
        SHA1_FF2( c, d, e, a, b, i++ );
        SHA1_FF2( b, c, d, e, a, i++ );
    }
    
    // Round 4
    for( ; i < 80; )
    { 
        SHA1_FF3( a, b, c, d, e, i++ );
        SHA1_FF3( e, a, b, c, d, i++ );
        SHA1_FF3( d, e, a, b, c, i++ );
        SHA1_FF3( c, d, e, a, b, i++ );
        SHA1_FF3( b, c, d, e, a, i++ );
    }
    
    // Store
    ctx->state[ 0 ] = ctx->state[ 0 ] + a;
    ctx->state[ 1 ] = ctx->state[ 1 ] + b;
    ctx->state[ 2 ] = ctx->state[ 2 ] + c;
    ctx->state[ 3 ] = ctx->state[ 3 ] + d;
    ctx->state[ 4 ] = ctx->state[ 4 ] + e;
}

//===========================================================================================================================
//  SHA-512 internals
//===========================================================================================================================

#define SHA512_BLOCK_SIZE   128

static const uint64_t       K[ 80 ] = 
{
    UINT64_C( 0x428a2f98d728ae22 ), UINT64_C( 0x7137449123ef65cd ), UINT64_C( 0xb5c0fbcfec4d3b2f ), UINT64_C( 0xe9b5dba58189dbbc ),
    UINT64_C( 0x3956c25bf348b538 ), UINT64_C( 0x59f111f1b605d019 ), UINT64_C( 0x923f82a4af194f9b ), UINT64_C( 0xab1c5ed5da6d8118 ),
    UINT64_C( 0xd807aa98a3030242 ), UINT64_C( 0x12835b0145706fbe ), UINT64_C( 0x243185be4ee4b28c ), UINT64_C( 0x550c7dc3d5ffb4e2 ),
    UINT64_C( 0x72be5d74f27b896f ), UINT64_C( 0x80deb1fe3b1696b1 ), UINT64_C( 0x9bdc06a725c71235 ), UINT64_C( 0xc19bf174cf692694 ),
    UINT64_C( 0xe49b69c19ef14ad2 ), UINT64_C( 0xefbe4786384f25e3 ), UINT64_C( 0x0fc19dc68b8cd5b5 ), UINT64_C( 0x240ca1cc77ac9c65 ),
    UINT64_C( 0x2de92c6f592b0275 ), UINT64_C( 0x4a7484aa6ea6e483 ), UINT64_C( 0x5cb0a9dcbd41fbd4 ), UINT64_C( 0x76f988da831153b5 ),
    UINT64_C( 0x983e5152ee66dfab ), UINT64_C( 0xa831c66d2db43210 ), UINT64_C( 0xb00327c898fb213f ), UINT64_C( 0xbf597fc7beef0ee4 ),
    UINT64_C( 0xc6e00bf33da88fc2 ), UINT64_C( 0xd5a79147930aa725 ), UINT64_C( 0x06ca6351e003826f ), UINT64_C( 0x142929670a0e6e70 ),
    UINT64_C( 0x27b70a8546d22ffc ), UINT64_C( 0x2e1b21385c26c926 ), UINT64_C( 0x4d2c6dfc5ac42aed ), UINT64_C( 0x53380d139d95b3df ),
    UINT64_C( 0x650a73548baf63de ), UINT64_C( 0x766a0abb3c77b2a8 ), UINT64_C( 0x81c2c92e47edaee6 ), UINT64_C( 0x92722c851482353b ),
    UINT64_C( 0xa2bfe8a14cf10364 ), UINT64_C( 0xa81a664bbc423001 ), UINT64_C( 0xc24b8b70d0f89791 ), UINT64_C( 0xc76c51a30654be30 ),
    UINT64_C( 0xd192e819d6ef5218 ), UINT64_C( 0xd69906245565a910 ), UINT64_C( 0xf40e35855771202a ), UINT64_C( 0x106aa07032bbd1b8 ),
    UINT64_C( 0x19a4c116b8d2d0c8 ), UINT64_C( 0x1e376c085141ab53 ), UINT64_C( 0x2748774cdf8eeb99 ), UINT64_C( 0x34b0bcb5e19b48a8 ),
    UINT64_C( 0x391c0cb3c5c95a63 ), UINT64_C( 0x4ed8aa4ae3418acb ), UINT64_C( 0x5b9cca4f7763e373 ), UINT64_C( 0x682e6ff3d6b2b8a3 ),
    UINT64_C( 0x748f82ee5defb2fc ), UINT64_C( 0x78a5636f43172f60 ), UINT64_C( 0x84c87814a1f0ab72 ), UINT64_C( 0x8cc702081a6439ec ),
    UINT64_C( 0x90befffa23631e28 ), UINT64_C( 0xa4506cebde82bde9 ), UINT64_C( 0xbef9a3f7b2c67915 ), UINT64_C( 0xc67178f2e372532b ),
    UINT64_C( 0xca273eceea26619c ), UINT64_C( 0xd186b8c721c0c207 ), UINT64_C( 0xeada7dd6cde0eb1e ), UINT64_C( 0xf57d4f7fee6ed178 ),
    UINT64_C( 0x06f067aa72176fba ), UINT64_C( 0x0a637dc5a2c898a6 ), UINT64_C( 0x113f9804bef90dae ), UINT64_C( 0x1b710b35131c471b ),
    UINT64_C( 0x28db77f523047d84 ), UINT64_C( 0x32caab7b40c72493 ), UINT64_C( 0x3c9ebe0a15c9bebc ), UINT64_C( 0x431d67c49c100d4c ),
    UINT64_C( 0x4cc5d4becb3e42b6 ), UINT64_C( 0x597f299cfc657e2a ), UINT64_C( 0x5fcb6fab3ad6faec ), UINT64_C( 0x6c44198c4a475817 )
};

static void _SHA512_Compress( SHA512_CTX_compat *ctx, const uint8_t *inPtr );

//===========================================================================================================================
//  SHA512_Init_compat
//===========================================================================================================================

int SHA512_Init_compat( SHA512_CTX_compat *ctx )
{
    ctx->length = 0;
    ctx->state[ 0 ] = UINT64_C( 0x6a09e667f3bcc908 );
    ctx->state[ 1 ] = UINT64_C( 0xbb67ae8584caa73b );
    ctx->state[ 2 ] = UINT64_C( 0x3c6ef372fe94f82b );
    ctx->state[ 3 ] = UINT64_C( 0xa54ff53a5f1d36f1 );
    ctx->state[ 4 ] = UINT64_C( 0x510e527fade682d1 );
    ctx->state[ 5 ] = UINT64_C( 0x9b05688c2b3e6c1f );
    ctx->state[ 6 ] = UINT64_C( 0x1f83d9abfb41bd6b );
    ctx->state[ 7 ] = UINT64_C( 0x5be0cd19137e2179 );
    ctx->curlen = 0;
    return( 0 );
}

//===========================================================================================================================
//  SHA512_Update_compat
//===========================================================================================================================

int SHA512_Update_compat( SHA512_CTX_compat *ctx, const void *inData, size_t inLen )
{
    const uint8_t *     src = (const uint8_t *) inData;
    size_t              n;
    
    while( inLen > 0 )
    {
        if( ( ctx->curlen == 0 ) && ( inLen >= SHA512_BLOCK_SIZE ) )
        {
            _SHA512_Compress( ctx, src );
            ctx->length += ( SHA512_BLOCK_SIZE * 8 );
            src         += SHA512_BLOCK_SIZE;
            inLen       -= SHA512_BLOCK_SIZE;
        }
        else
        {
            n = Min( inLen, SHA512_BLOCK_SIZE - ctx->curlen );
            memcpy( ctx->buf + ctx->curlen, src, n );
            ctx->curlen += n;
            src         += n;
            inLen       -= n;
            if( ctx->curlen == SHA512_BLOCK_SIZE )
            {
                _SHA512_Compress( ctx, ctx->buf );
                ctx->length += ( SHA512_BLOCK_SIZE * 8 );
                ctx->curlen = 0;
            }
        }
    }
    return( 0 );
}

//===========================================================================================================================
//  SHA512_Final_compat
//===========================================================================================================================

int SHA512_Final_compat( unsigned char *outDigest, SHA512_CTX_compat *ctx )
{
    int     i;
    
    ctx->length += ( ctx->curlen * UINT64_C( 8 ) );
    ctx->buf[ ctx->curlen++ ] = 0x80;
    
    // If length > 112 bytes, append zeros then compress. Then fall back to padding zeros and length encoding like normal.
    if( ctx->curlen > 112 )
    {
        while( ctx->curlen < 128 ) ctx->buf[ ctx->curlen++ ] = 0;
        _SHA512_Compress( ctx, ctx->buf );
        ctx->curlen = 0;
    }
    
    // Pad up to 120 bytes of zeroes.
    // Note: that from 112 to 120 is the 64 MSB of the length. We assume that you won't hash 2^64 bits of data.
    while( ctx->curlen < 120 ) ctx->buf[ ctx->curlen++ ] = 0;
    
    // Store length
    WriteBig64( ctx->buf + 120, ctx->length );
    _SHA512_Compress( ctx, ctx->buf );
    
    // Copy output
    for( i = 0; i < 8; ++i )
    {
        WriteBig64( outDigest + ( 8 * i ), ctx->state[ i ] );
    }
    memset( ctx, 0, sizeof( *ctx ) ); // Zero sensitive info.
    return( 0 );
}

//===========================================================================================================================
//  SHA512_compat
//===========================================================================================================================

unsigned char * SHA512_compat( const void *inData, size_t inLen, unsigned char *outDigest )
{
    SHA512_CTX_compat       ctx;
    
    SHA512_Init_compat( &ctx );
    SHA512_Update_compat( &ctx, inData, inLen );
    SHA512_Final_compat( outDigest, &ctx );
    return( outDigest );
}

//===========================================================================================================================
//  _SHA512_Compress
//===========================================================================================================================

#define SHA512_Ch(x,y,z)        (z ^ (x & (y ^ z)))
#define SHA512_Maj(x,y,z)       (((x | y) & z) | (x & y)) 
#define SHA512_S(x, n)          ROTR64(x, n)
#define SHA512_R(x, n)          (((x) & UINT64_C(0xFFFFFFFFFFFFFFFF)) >> ((uint64_t) n))
#define SHA512_Sigma0(x)        (SHA512_S(x, 28) ^ SHA512_S(x, 34) ^ SHA512_S(x, 39))
#define SHA512_Sigma1(x)        (SHA512_S(x, 14) ^ SHA512_S(x, 18) ^ SHA512_S(x, 41))
#define SHA512_Gamma0(x)        (SHA512_S(x,  1) ^ SHA512_S(x,  8) ^ SHA512_R(x,  7))
#define SHA512_Gamma1(x)        (SHA512_S(x, 19) ^ SHA512_S(x, 61) ^ SHA512_R(x,  6))
#define SHA512_RND( a, b, c, d, e, f, g, h, i ) \
     t0 = h + SHA512_Sigma1( e ) + SHA512_Ch( e, f, g ) + K[ i ] + W[ i ]; \
     t1 = SHA512_Sigma0( a ) + SHA512_Maj( a, b, c); \
     d += t0; \
     h  = t0 + t1;

static void _SHA512_Compress( SHA512_CTX_compat *ctx, const uint8_t *inPtr )
{
    uint64_t        S[ 8] , W[ 80 ], t0, t1;
    int             i;
    
    // Copy state into S
    for( i = 0; i < 8; ++i )
    {
        S[ i ] = ctx->state[ i ];
    }
    
    // Copy the state into 1024-bits into W[0..15]
    for( i = 0; i < 16; ++i )
    {
        W[ i ] = ReadBig64( inPtr );
        inPtr += 8;
    }
    
    // Fill W[16..79]
    for( i = 16; i < 80; ++i )
    {
        W[ i ] = SHA512_Gamma1( W[ i-2 ] ) + W[ i-7 ] + SHA512_Gamma0( W[ i-15 ] )  + W[ i-16 ];
    }       
    
    // Compress
    for( i = 0; i < 80; i += 8 )
    {
         SHA512_RND( S[ 0 ], S[ 1 ], S[ 2 ], S[ 3 ], S[ 4 ], S[ 5 ], S[ 6 ], S[ 7 ], i+0 );
         SHA512_RND( S[ 7 ], S[ 0 ], S[ 1 ], S[ 2 ], S[ 3 ], S[ 4 ], S[ 5 ], S[ 6 ], i+1 );
         SHA512_RND( S[ 6 ], S[ 7 ], S[ 0 ], S[ 1 ], S[ 2 ], S[ 3 ], S[ 4 ], S[ 5 ], i+2 );
         SHA512_RND( S[ 5 ], S[ 6 ], S[ 7 ], S[ 0 ], S[ 1 ], S[ 2 ], S[ 3 ], S[ 4 ], i+3 );
         SHA512_RND( S[ 4 ], S[ 5 ], S[ 6 ], S[ 7 ], S[ 0 ], S[ 1 ], S[ 2 ], S[ 3 ], i+4 );
         SHA512_RND( S[ 3 ], S[ 4 ], S[ 5 ], S[ 6 ], S[ 7 ], S[ 0 ], S[ 1 ], S[ 2 ], i+5 );
         SHA512_RND( S[ 2 ], S[ 3 ], S[ 4 ], S[ 5 ], S[ 6 ], S[ 7 ], S[ 0 ], S[ 1 ], i+6 );
         SHA512_RND( S[ 1 ], S[ 2 ], S[ 3 ], S[ 4 ], S[ 5 ], S[ 6 ], S[ 7 ], S[ 0 ], i+7 );
    }
    
    // Feedback
    for( i = 0; i < 8; ++i )
    {
        ctx->state[ i ] += S[ i ];
    }
}

//===========================================================================================================================
//  SHA-3 internals
//
//  Based on code from <https://github.com/floodyberry>.
//===========================================================================================================================

static const uint64_t       kSHA3RoundConstants[24] = 
{
    UINT64_C( 0x0000000000000001 ), UINT64_C( 0x0000000000008082 ),
    UINT64_C( 0x800000000000808a ), UINT64_C( 0x8000000080008000 ),
    UINT64_C( 0x000000000000808b ), UINT64_C( 0x0000000080000001 ),
    UINT64_C( 0x8000000080008081 ), UINT64_C( 0x8000000000008009 ),
    UINT64_C( 0x000000000000008a ), UINT64_C( 0x0000000000000088 ),
    UINT64_C( 0x0000000080008009 ), UINT64_C( 0x000000008000000a ),
    UINT64_C( 0x000000008000808b ), UINT64_C( 0x800000000000008b ),
    UINT64_C( 0x8000000000008089 ), UINT64_C( 0x8000000000008003 ),
    UINT64_C( 0x8000000000008002 ), UINT64_C( 0x8000000000000080 ),
    UINT64_C( 0x000000000000800a ), UINT64_C( 0x800000008000000a ),
    UINT64_C( 0x8000000080008081 ), UINT64_C( 0x8000000000008080 ),
    UINT64_C( 0x0000000080000001 ), UINT64_C( 0x8000000080008008 )
};

static void _SHA3_Block( SHA3_CTX_compat *ctx, const uint8_t *in );

//===========================================================================================================================
//  SHA3_Init_compat
//===========================================================================================================================

int SHA3_Init_compat( SHA3_CTX_compat *ctx )
{
    memset( ctx, 0, sizeof( *ctx ) );
    return( 0 );
}

//===========================================================================================================================
//  SHA3_Update_compat
//===========================================================================================================================

int SHA3_Update_compat( SHA3_CTX_compat *ctx, const void *inData, size_t inLen )
{
    const uint8_t *     in = (const uint8_t *) inData;
    size_t              want;
    
    // Handle the previous data.
    if( ctx->leftover > 0 )
    {
        want = SHA3_BLOCK_SIZE - ctx->leftover;
        want = ( want < inLen ) ? want : inLen;
        memcpy( ctx->buffer + ctx->leftover, in, want );
        ctx->leftover += want;
        if( ctx->leftover < SHA3_BLOCK_SIZE ) goto exit;
        in    += want;
        inLen -= want;
        _SHA3_Block( ctx, ctx->buffer );
    }
    
    // Handle the current data.
    while( inLen >= SHA3_BLOCK_SIZE )
    {
        _SHA3_Block( ctx, in );
        in    += SHA3_BLOCK_SIZE;
        inLen -= SHA3_BLOCK_SIZE;
    }
    
    // Handle leftover data.
    ctx->leftover = inLen;
    if( inLen > 0 ) memcpy( ctx->buffer, in, inLen );
    
exit:
    return( 0 );
}

//===========================================================================================================================
//  SHA3_Update_compat
//===========================================================================================================================

int SHA3_Final_compat( uint8_t *outDigest, SHA3_CTX_compat *ctx )
{
    size_t      i;
    
    ctx->buffer[ctx->leftover] = 0x01;
    memset( ctx->buffer + ( ctx->leftover + 1 ), 0, SHA3_BLOCK_SIZE - ( ctx->leftover + 1 ) );
    ctx->buffer[SHA3_BLOCK_SIZE - 1] |= 0x80;
    _SHA3_Block( ctx, ctx->buffer );

    for( i = 0; i < SHA3_DIGEST_LENGTH; i += 8 )
    {
        WriteLittle64( &outDigest[i], ctx->state[i / 8] );
    }
    return( 0 );
}

//===========================================================================================================================
//  SHA3_Update_compat
//===========================================================================================================================

uint8_t *   SHA3_compat( const void *inData, size_t inLen, uint8_t outDigest[64] )
{
    SHA3_CTX_compat     ctx;
    
    SHA3_Init_compat( &ctx );
    SHA3_Update_compat( &ctx, inData, inLen );
    SHA3_Final_compat( outDigest, &ctx );
    return( outDigest );
}

//===========================================================================================================================
//  _SHA3_Block
//===========================================================================================================================

static void _SHA3_Block( SHA3_CTX_compat *ctx, const uint8_t *in )
{
    uint64_t        s0, s1, s2, s3, s4, s5, s6, s7, s8, s9, s10;
    uint64_t        s11, s12, s13, s14, s15, s16, s17, s18, s19, s20;
    uint64_t        s21, s22, s23, s24;
    uint64_t        t0, t1, t2, t3, t4, u0, u1, u2, u3, u4, v, w;
    size_t          i;
    
    s0  = ctx->state[ 0] ^ ReadLittle64( &in[0] );
    s1  = ctx->state[ 1] ^ ReadLittle64( &in[8] );
    s2  = ctx->state[ 2] ^ ReadLittle64( &in[16] );
    s3  = ctx->state[ 3] ^ ReadLittle64( &in[24] );
    s4  = ctx->state[ 4] ^ ReadLittle64( &in[32] );
    s5  = ctx->state[ 5] ^ ReadLittle64( &in[40] );
    s6  = ctx->state[ 6] ^ ReadLittle64( &in[48] );
    s7  = ctx->state[ 7] ^ ReadLittle64( &in[56] );
    s8  = ctx->state[ 8] ^ ReadLittle64( &in[64] );
    s9  = ctx->state[ 9];
    s10 = ctx->state[10];
    s11 = ctx->state[11];
    s12 = ctx->state[12];
    s13 = ctx->state[13];
    s14 = ctx->state[14];
    s15 = ctx->state[15];
    s16 = ctx->state[16];
    s17 = ctx->state[17];
    s18 = ctx->state[18];
    s19 = ctx->state[19];
    s20 = ctx->state[20];
    s21 = ctx->state[21];
    s22 = ctx->state[22];
    s23 = ctx->state[23];
    s24 = ctx->state[24];
    
    for( i = 0; i < 24; ++i )
    {
        // theta: c = a[0,i] ^ a[1,i] ^ .. a[4,i]
        t0 = s0 ^ s5 ^ s10 ^ s15 ^ s20;
        t1 = s1 ^ s6 ^ s11 ^ s16 ^ s21;
        t2 = s2 ^ s7 ^ s12 ^ s17 ^ s22;
        t3 = s3 ^ s8 ^ s13 ^ s18 ^ s23;
        t4 = s4 ^ s9 ^ s14 ^ s19 ^ s24;

        // theta: d[i] = c[i+4] ^ rotl(c[i+1],1)
        u0 = t4 ^ ROTL64(t1, 1);
        u1 = t0 ^ ROTL64(t2, 1);
        u2 = t1 ^ ROTL64(t3, 1);
        u3 = t2 ^ ROTL64(t4, 1);
        u4 = t3 ^ ROTL64(t0, 1);

        // theta: a[0,i], a[1,i], .. a[4,i] ^= d[i]
        s0 ^= u0; s5 ^= u0; s10 ^= u0; s15 ^= u0; s20 ^= u0;
        s1 ^= u1; s6 ^= u1; s11 ^= u1; s16 ^= u1; s21 ^= u1;
        s2 ^= u2; s7 ^= u2; s12 ^= u2; s17 ^= u2; s22 ^= u2;
        s3 ^= u3; s8 ^= u3; s13 ^= u3; s18 ^= u3; s23 ^= u3;
        s4 ^= u4; s9 ^= u4; s14 ^= u4; s19 ^= u4; s24 ^= u4;

        // rho pi: b[..] = rotl(a[..], ..)
        v   = s1;
        s1  = ROTL64(s6,  44);
        s6  = ROTL64(s9,  20);
        s9  = ROTL64(s22, 61);
        s22 = ROTL64(s14, 39);
        s14 = ROTL64(s20, 18);
        s20 = ROTL64(s2,  62);
        s2  = ROTL64(s12, 43);
        s12 = ROTL64(s13, 25);
        s13 = ROTL64(s19,  8);
        s19 = ROTL64(s23, 56);
        s23 = ROTL64(s15, 41);
        s15 = ROTL64(s4,  27);
        s4  = ROTL64(s24, 14);
        s24 = ROTL64(s21,  2);
        s21 = ROTL64(s8,  55);
        s8  = ROTL64(s16, 45);
        s16 = ROTL64(s5,  36);
        s5  = ROTL64(s3,  28);
        s3  = ROTL64(s18, 21);
        s18 = ROTL64(s17, 15);
        s17 = ROTL64(s11, 10);
        s11 = ROTL64(s7,   6);
        s7  = ROTL64(s10,  3);
        s10 = ROTL64(v,    1);
        
        // chi: a[i,j] ^= ~b[i,j+1] & b[i,j+2]
        v = s0;
        w = s1;
        s0 ^= (~w)  & s2;
        s1 ^= (~s2) & s3;
        s2 ^= (~s3) & s4;
        s3 ^= (~s4) & v;
        s4 ^= (~v)  & w;
        v = s5;
        w = s6;
        s5 ^= (~w)  & s7;
        s6 ^= (~s7) & s8;
        s7 ^= (~s8) & s9;
        s8 ^= (~s9) & v;
        s9 ^= (~v)  & w;
        v = s10;
        w = s11;
        s10 ^= (~w)   & s12;
        s11 ^= (~s12) & s13;
        s12 ^= (~s13) & s14;
        s13 ^= (~s14) & v;
        s14 ^= (~v)  & w;
        v = s15;
        w = s16;
        s15 ^= (~w)   & s17;
        s16 ^= (~s17) & s18;
        s17 ^= (~s18) & s19;
        s18 ^= (~s19) & v;
        s19 ^= (~v)   & w;
        v = s20;
        w = s21;
        s20 ^= (~w)   & s22;
        s21 ^= (~s22) & s23;
        s22 ^= (~s23) & s24;
        s23 ^= (~s24) & v;
        s24 ^= (~v)   & w;
        
        // iota: a[0,0] ^= round constant
        s0 ^= kSHA3RoundConstants[i];
    }
    
    ctx->state[ 0] = s0;
    ctx->state[ 1] = s1;
    ctx->state[ 2] = s2;
    ctx->state[ 3] = s3;
    ctx->state[ 4] = s4;
    ctx->state[ 5] = s5;
    ctx->state[ 6] = s6;
    ctx->state[ 7] = s7;
    ctx->state[ 8] = s8;
    ctx->state[ 9] = s9;
    ctx->state[10] = s10;
    ctx->state[11] = s11;
    ctx->state[12] = s12;
    ctx->state[13] = s13;
    ctx->state[14] = s14;
    ctx->state[15] = s15;
    ctx->state[16] = s16;
    ctx->state[17] = s17;
    ctx->state[18] = s18;
    ctx->state[19] = s19;
    ctx->state[20] = s20;
    ctx->state[21] = s21;
    ctx->state[22] = s22;
    ctx->state[23] = s23;
    ctx->state[24] = s24;
}


