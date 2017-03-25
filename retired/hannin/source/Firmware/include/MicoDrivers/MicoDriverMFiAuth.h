/**
******************************************************************************
* @file    MicoDriverMFiAuth.h 
* @author  William Xu
* @version V1.0.0
* @date    7-Nov-2014
* @brief   This file provides all the headers of Apple Authentication Coprocessor
*          operations, Apple Authentication Coprocessor should be conntectd by
*          MICO_I2C_CP defined in platform.h, and based on I2C driver defined in 
*          MicoDriverI2c.h
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

#ifndef __MICODRIVERMFIAUTH_H__
#define __MICODRIVERMFIAUTH_H__

#pragma once
#include "Common.h"
#include "MicoPlatform.h"

//---------------------------------------------------------------------------------------------------------------------------
/*! @function   PlatformMFiAuthInitialize
    @abstract   Performs any platform-specific initialization needed. Example: Bring up I2C interface for communication with
                the Apple Authentication Coprocessor.
*/
OSStatus MicoMFiAuthInitialize( mico_i2c_t i2c );

//---------------------------------------------------------------------------------------------------------------------------
/*! @function   PlatformMFiAuthFinalize
    @abstract   Performs any platform-specific cleanup needed. Example: Bringing down the I2C interface for communication with
                the Apple Authentication Coprocessor.
*/
void MicoMFiAuthFinalize( void );

//---------------------------------------------------------------------------------------------------------------------------
/*! @function   PlatformMFiAuthCreateSignature
    @abstract   Create an RSA signature from the specified SHA-1 digest using the Apple Authentication Coprocessor.

    @param      inDigestPtr         Pointer to 20-byte SHA-1 digest.
    @param      inDigestLen         Number of bytes in the digest. Must be 20.
    @param      outSignaturePtr     Receives malloc()'d ptr to RSA signature. Caller must free() on success.
    @param      outSignatureLen     Receives number of bytes in RSA signature.
*/
OSStatus MicoMFiAuthCreateSignature( const  void      *inDigestPtr,
                                            size_t     inDigestLen,
                                            uint8_t  **outSignaturePtr,
                                            size_t    *outSignatureLen );

//---------------------------------------------------------------------------------------------------------------------------
/*! @function   PlatformMFiAuthCopyCertificate
    @abstract   Copy the certificate from the Apple Authentication Coprocessor.

    @param      outCertificatePtr   Receives malloc()'d ptr to a DER-encoded PKCS#7 message containing the certificate.
                                    Caller must free() on success.
    @param      outCertificateLen   Number of bytes in the DER-encoded certificate.
*/
OSStatus MicoMFiAuthCopyCertificate( uint8_t **outCertificatePtr, size_t *outCertificateLen );


#endif // __MICODRIVERMFIAUTH_H__


