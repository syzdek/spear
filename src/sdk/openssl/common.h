/*
 *  Simple Programming Examples And References
 *  Copyright (C) 2011 David M. Syzdek <david@syzdek.net>.
 *
 *  @SYZDEK_BSD_LICENSE_START@
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are
 *  met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of David M. Syzdek nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 *  IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL BINDLE BINARIES BE LIABLE FOR
 *  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 *  OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 *  SUCH DAMAGE.
 *
 *  @SYZDEK_BSD_LICENSE_END@
 */
/**
 *  @file src/sdk/openssl/common.h common functions for openssl examples
 */
#ifndef _SPEAR_SRC_SDK_OPENSSL_COMMON_H
#define _SPEAR_SRC_SDK_OPENSSL_COMMON_H 1

///////////////
//           //
//  Headers  //
//           //
///////////////
#pragma mark Headers

#include <openssl/x509.h>


/////////////////
//             //
//  Datatypes  //
//             //
/////////////////
#pragma mark - Datatypes

typedef struct my_x509_name_st MY_X509_NAME;
struct my_x509_name_st
{
   char * c;
   char * st;
   char * l;
   char * o;
   char * ou;
   char * cn;
   char * gn;
   char * sn;
   char * email;
   char * description;
};


//////////////////
//              //
//  Prototypes  //
//              //
//////////////////
#pragma mark - Prototypes

// initiates SSL connection on socket
int client_ssl_connect(int s, SSL ** sslp, SSL_CTX ** ctxp);

// connects to remote TCP port
int client_tcp_connect(const char * host, int port);

// disconnects from remote TCP port
int client_disconnect(int s, SSL * ssl, SSL_CTX * ctx);

// parses ASN1_TIME into struct tm
int parse_asn1_time(const ASN1_TIME * atp, struct tm * tsp);

// parses DN into componets
void parse_dn(char * dn, MY_X509_NAME * namep);

// prints dn
void print_dn(const char * prefix, MY_X509_NAME * namep);

#endif
/* end of header */
