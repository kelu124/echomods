/**
******************************************************************************
* @file    MicoSRPServer.h 
* @author  William Xu
* @version V1.0.0
* @date    16-Sep-2014
* @brief   This is a direct implementation of the Secure Remote Password
 *         Protocol version 6a as described by http://srp.stanford.edu/design.html
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

#ifndef SRP_H
#define SRP_H

#include "Debug.h"
#include "Common.h"

struct SRPVerifier;

typedef enum
{
    SRP_NG_1024,
    SRP_NG_2048,
    SRP_NG_3072,
    SRP_NG_4096,
    SRP_NG_8192,
    SRP_NG_CUSTOM
} SRP_NGType;

typedef enum 
{
    SRP_SHA1, 
    SRP_SHA224, 
    SRP_SHA256,
    SRP_SHA384, 
    SRP_SHA512
} SRP_HashAlgorithm;

/*Pair info*/
typedef struct _srp_server_t {
  SRP_HashAlgorithm alg;
  bool              authenticated;
  SRP_NGType        ng_type;
  const char        * n_hex;
  const char        * g_hex;
  char              *username;
  unsigned char     *bytes_s;
  int               len_s;
  unsigned char     *bytes_B;
  int               len_B;
  unsigned char     *bytes_b;
  int               len_b;  
  unsigned char     *bytes_v;
  int               len_v;
  unsigned char     *session_key;
  int               len_session_key;
  unsigned char     *bytes_M;
  int               len_M;
  unsigned char     *bytes_AMK;
  int               len_AMK;
} srp_server_t;



/* Out: bytes_s, len_s, bytes_v, len_v
 * 
 * The caller is responsible for freeing the memory allocated for bytes_s and bytes_v
 * 
 * The n_hex and g_hex parameters should be 0 unless SRP_NG_CUSTOM is used for ng_type.
 * If provided, they must contain ASCII text of the hexidecimal notation.
 */
void srp_create_salted_verification_key( SRP_HashAlgorithm alg, 
                                         SRP_NGType ng_type, const char * username,
                                         const unsigned char * password, int len_password,
                                         const unsigned char ** bytes_s, int * len_s, 
                                         const unsigned char ** bytes_v, int * len_v,
                                         const unsigned char ** bytes_B, int * len_B,
                                         const unsigned char ** bytes_b, int * len_b,
                                         const char * n_hex, const char * g_hex );

srp_server_t* srp_server_setup( SRP_HashAlgorithm alg, 
                                SRP_NGType ng_type, const char * username,
                                const unsigned char * password, int len_password, 
                                const unsigned char * verifier, int len_verifier,
                                const unsigned char * salt, int len_salt, 
                                const char * n_hex, const char * g_hex );

OSStatus srp_server_generate_session_key( srp_server_t* server, const unsigned char * bytes_A, int len_A );

void srp_server_verify_session( srp_server_t* server, const unsigned char * user_M, const unsigned char ** bytes_HAMK );

void srp_server_delete( srp_server_t** server);



/* Out: bytes_B, len_B.
 * 
 * On failure, bytes_B will be set to NULL and len_B will be set to 0
 * 
 * The n_hex and g_hex parameters should be 0 unless SRP_NG_CUSTOM is used for ng_type
 */
struct SRPVerifier *  srp_verifier_new( SRP_HashAlgorithm alg, SRP_NGType ng_type, const char * username,
                                        const unsigned char * bytes_s, int len_s, 
                                        const unsigned char * bytes_v, int len_v,
                                        const unsigned char * bytes_A, int len_A,
                                        const unsigned char * bytes_B, int len_B,
                                        const unsigned char * bytes_b, int len_b,
                                        const char * n_hex, const char * g_hex );


void                  srp_verifier_delete( struct SRPVerifier * ver );


int                   srp_verifier_is_authenticated( struct SRPVerifier * ver );


const char *          srp_verifier_get_username( struct SRPVerifier * ver );

/* key_length may be null */
const unsigned char * srp_verifier_get_session_key( struct SRPVerifier * ver, int * key_length );


int                   srp_verifier_get_session_key_length( struct SRPVerifier * ver );


/* user_M must be exactly srp_verifier_get_session_key_length() bytes in size */
void                  srp_verifier_verify_session( struct SRPVerifier * ver,
                                                   const unsigned char * user_M, 
                                                   const unsigned char ** bytes_HAMK );

#endif /* Include Guard */

