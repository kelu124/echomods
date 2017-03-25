/**
******************************************************************************
* @file    MicoAES.h 
* @author  William Xu
* @version V1.0.0
* @date    16-Sep-2014
* @brief   This file provides all the headers of AES operation functions.
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

#ifndef _MICOAES_H_
#define _MICOAES_H_

typedef unsigned char  byte;
typedef unsigned short word16;
typedef unsigned int   word32;

enum {
    AES_ENC_TYPE   = 1,   /* cipher unique type */
    AES_ENCRYPTION = 0,
    AES_DECRYPTION = 1,
    AES_BLOCK_SIZE = 16
};


typedef struct Aes {
    /* AESNI needs key first, rounds 2nd, not sure why yet */
    word32 key[60];
    word32  rounds;

    word32 reg[AES_BLOCK_SIZE / sizeof(word32)];      /* for CBC mode */
    word32 tmp[AES_BLOCK_SIZE / sizeof(word32)];      /* same         */

#ifdef HAVE_AESGCM
    byte H[AES_BLOCK_SIZE];
#ifdef GCM_TABLE
    /* key-based fast multiplication table. */
    byte M0[256][AES_BLOCK_SIZE];
#endif /* GCM_TABLE */
#endif /* HAVE_AESGCM */
#ifdef CYASSL_AESNI
    byte use_aesni;
#endif /* CYASSL_AESNI */
#ifdef HAVE_CAVIUM
    AesType type;            /* aes key type */
    int     devId;           /* nitrox device id */
    word32  magic;           /* using cavium magic */
    word64  contextHandle;   /* nitrox context memory handle */
#endif
} Aes;

int AesSetKey(Aes* aes, const byte* userKey, word32 keylen, const byte* iv,
              int dir);
int AesSetKeyDirect(Aes* aes, const byte* userKey, word32 keylen,
                        const byte* iv, int dir);
void AesEncryptDirect(Aes* aes, byte* out, const byte* in);
void AesDecryptDirect(Aes* aes, byte* out, const byte* in);


int  AesSetIV(Aes* aes, const byte* iv);
int  AesCbcEncrypt(Aes* aes, byte* out, const byte* in, word32 sz);
int  AesCbcDecrypt(Aes* aes, byte* out, const byte* in, word32 sz);
void AesCtrEncrypt(Aes* aes, byte* out, const byte* in, word32 sz);


#ifdef HAVE_AESGCM
void AesGcmSetKey(Aes* aes, const byte* key, word32 len);
void AesGcmEncrypt(Aes* aes, byte* out, const byte* in, word32 sz,
                              const byte* iv, word32 ivSz,
                              byte* authTag, word32 authTagSz,
                              const byte* authIn, word32 authInSz);
int  AesGcmDecrypt(Aes* aes, byte* out, const byte* in, word32 sz,
                              const byte* iv, word32 ivSz,
                              const byte* authTag, word32 authTagSz,
                              const byte* authIn, word32 authInSz);
#endif /* HAVE_AESGCM */
#ifdef HAVE_AESCCM
void AesCcmSetKey(Aes* aes, const byte* key, word32 keySz);
void AesCcmEncrypt(Aes* aes, byte* out, const byte* in, word32 inSz,
                              const byte* nonce, word32 nonceSz,
                              byte* authTag, word32 authTagSz,
                              const byte* authIn, word32 authInSz);
int  AesCcmDecrypt(Aes* aes, byte* out, const byte* in, word32 inSz,
                              const byte* nonce, word32 nonceSz,
                              const byte* authTag, word32 authTagSz,
                              const byte* authIn, word32 authInSz);
#endif /* HAVE_AESCCM */

#ifdef HAVE_CAVIUM
int  AesInitCavium(Aes*, int);
void AesFreeCavium(Aes*);
#endif


#endif
