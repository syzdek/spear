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
 *  @file src/sdk/openssl/servercertinfo.c simple hash utility for sha1
 */
/*
 *  Simple Build:
 *     gcc -W -Wall -O2 -c servercertinfo.c
 *     gcc -W -Wall -O2 -lcrypto -o servercertinfo servercertinfo.o
 *
 *  GNU Libtool Build:
 *     libtool --mode=compile gcc -W -Wall -g -O2 -c servercertinfo.c
 *     libtool --mode=link    gcc -W -Wall -g -O2 -o servercertinfo servercertinfo.lo
 *
 *  GNU Libtool Install:
 *     libtool --mode=install install -c servercertinfo /usr/local/bin/servercertinfo
 *
 *  GNU Libtool Clean:
 *     libtool --mode=clean rm -f servercertinfo.lo servercertinfo
 */

///////////////
//           //
//  Headers  //
//           //
///////////////
#pragma mark Headers

#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/x509.h>
#include <openssl/bio.h>

#include "common.h"


//////////////////
//              //
//  Prototypes  //
//              //
//////////////////
#pragma mark - Prototypes

// main statement
int main(int argc, char * argv[]);

// initiates SSL connection on socket
int client_ssl_connect(int s, SSL ** sslp, SSL_CTX ** ctxp);

// connects to remote TCP port
int client_tcp_connect(const char * host, int port);

// disconnects from remote TCP port
int client_disconnect(int s, SSL * ssl, SSL_CTX * ctx);


/////////////////
//             //
//  Functions  //
//             //
/////////////////
#pragma mark - Functions

/// disconnects from remote TCP port
/// @param[in]  s     socket handle
int client_disconnect(int s, SSL * ssl, SSL_CTX * ctx)
{
   if ((ssl))
   {
      SSL_shutdown(ssl);
      SSL_free(ssl);
   };

   if ((ctx))
      SSL_CTX_free(ctx);

   close(s);

   return(0);
}


/// initiates SSL connection on socket
/// @param[in]  s         active TCP socket
/// @param[out] sslp      reference to SSL pointer
/// @param[out] ctxp      reference to SSL Context pointer
int client_ssl_connect(int s, SSL ** sslp, SSL_CTX ** ctxp)
{
   SSL     * ssl;
   SSL_CTX * ctx;
   char      errmsg[1024];
   int       err;

   ssl   = NULL;
   ctx   = NULL;
   *sslp = NULL;
   *ctxp = NULL;

   SSL_load_error_strings();
   SSL_library_init();

   if (!(ctx = SSL_CTX_new(SSLv23_client_method())))
   {
      errmsg[1023] = '\0';
      ERR_error_string_n(ERR_get_error(), errmsg, 1023);
      fprintf(stderr, "servercertinfo: SSL_CTX_new(): %s\n", errmsg);
      return(-1);
   };
   *ctxp = ctx;

   if (!(ssl = SSL_new(ctx)))
   {
      errmsg[1023] = '\0';
      ERR_error_string_n(ERR_get_error(), errmsg, 1023);
      fprintf(stderr, "servercertinfo: SSL_new(): %s\n", errmsg);
      return(-1);
   };
   *sslp = ssl;

   if ((err = SSL_set_fd(ssl, s)) != 1)
   {
      errmsg[1023] = '\0';
      ERR_error_string_n(ERR_get_error(), errmsg, 1023);
      fprintf(stderr, "servercertinfo: SSL_set_fd(): %s\n", errmsg);
      return(-1);
   };

   if ((err = SSL_connect(ssl)) != 1)
   {
      if (err == -1)
         err = ERR_get_error();
      errmsg[1023] = '\0';
      ERR_error_string_n(err, errmsg, 1023);
      fprintf(stderr, "servercertinfo: SSL_connect(): %s\n", errmsg);
      return(-1);
   };

   return(0);
}


/// connects to remote TCP port
/// @param[in]  host  remote host name
/// @param[in]  port  remote TCP port
int client_tcp_connect(const char * host, int port)
{
   int                   s;
   int                   opt;
   int                   i;
   struct hostent      * hp;
   struct sockaddr_in    sa;
   struct sockaddr_in6   sa6;
   char                  addr[INET6_ADDRSTRLEN+1];

   // attempts to create connection to IPv6 address
   if ((hp = gethostbyname2(host, AF_INET6)))
   {
      if ((s = socket(AF_INET6, SOCK_STREAM, 0)) == -1)
         return(-1);

      opt = 1;
      setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (void *)&opt, sizeof(int));
      setsockopt(s, SOL_SOCKET, SO_KEEPALIVE, (void *)&opt, sizeof(int));
      setsockopt(s, SOL_SOCKET, SO_NOSIGPIPE, (void *)&opt, sizeof(int));

      memset(&sa6, 0, sizeof(struct sockaddr_in6));
      sa6.sin6_family = hp->h_addrtype;
      sa6.sin6_port   = htons(port);
      sa6.sin6_len    = sizeof(struct sockaddr_in6);

      if ((hp))
      for(i = 0; ((hp->h_addr_list[i])); i++)
      {
         inet_ntop(hp->h_addrtype, &hp->h_addr_list[i], addr, INET6_ADDRSTRLEN);
         addr[INET6_ADDRSTRLEN] = '\0';

         printf("Trying %s...\n", addr);

         memcpy(&sa6.sin6_addr, hp->h_addr_list[0], (size_t)hp->h_length);

         if (connect(s, (struct sockaddr *)&sa6, sizeof(sa6)) != -1)
         {
            //fcntl(s, F_SETFL, O_NONBLOCK);
            return(s);
         };

         fprintf(stderr, "servercertinfo: connect(%s): %s\n", addr, strerror(errno));
      };
      close(s);
   };
   if (!(hp))
      fprintf(stderr, "servercertinfo: gethostbyname2(AF_INET6): %s\n", hstrerror(h_errno));

   // attempts to create connection to IPv4 address
   if ((hp = gethostbyname2(host, AF_INET)))
   {
      if ((s = socket(AF_INET, SOCK_STREAM, 0)) == -1)
         return(-1);

      opt = 1;
      setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (void *)&opt, sizeof(int));
      setsockopt(s, SOL_SOCKET, SO_KEEPALIVE, (void *)&opt, sizeof(int));
      setsockopt(s, SOL_SOCKET, SO_NOSIGPIPE, (void *)&opt, sizeof(int));

      memset(&sa, 0, sizeof(struct sockaddr_in));
      sa.sin_family = hp->h_addrtype;
      sa.sin_port   = htons(port);
      sa.sin_len    = sizeof(struct sockaddr_in);

      for(i = 0; (((hp->h_addr_list[i])) && ((hp))); i++)
      {
         inet_ntop(hp->h_addrtype, &hp->h_addr_list[i], addr, INET6_ADDRSTRLEN);
         addr[INET6_ADDRSTRLEN] = '\0';

         printf("Trying %s...\n", addr);

         memcpy(&sa.sin_addr, hp->h_addr_list[i], (size_t)hp->h_length);

         if (connect(s, (struct sockaddr *)&sa, sizeof(sa)) != -1)
         {
            //fcntl(s, F_SETFL, O_NONBLOCK);
            return(s);
         };

         fprintf(stderr, "servercertinfo: connect(%s): %s\n", addr, strerror(errno));
      };
      close(s);
   };
   if (!(hp))
      fprintf(stderr, "servercertinfo: gethostbyname2(AF_INET): %s\n", hstrerror(h_errno));

   return(-1);
}


/// main statement
/// @param[in]  argc  number of arguments passed to program
/// @param[in]  argv  array of arguments passed to program
int main(int argc, char * argv[])
{
   X509                * x;
   int                   pos;
   int                   err;
   char                  errmsg[1024];
   const EVP_MD        * digest;
   unsigned char         md[EVP_MAX_MD_SIZE];
   char                  xbuff[1024];
   unsigned int          n;
   MY_X509_NAME          my_name;
   X509_NAME           * name;
   SSL                 * ssl;
   SSL_CTX             * ctx;
   FILE                * fp;
   struct tm             ts;
   char                  timestr[27];

   int s;

   // checks arguments
   if ((argc < 3) || (argc > 4))
   {
      fprintf(stderr, "Usage: servercertinfo <host> <port> [ <output> ]\n");
      return(1);
   };

   if ((s = client_tcp_connect(argv[1], atol(argv[2]))) == -1)
      return(1);

   if ((client_ssl_connect(s, &ssl, &ctx)))
   {
      client_disconnect(s, ssl, ctx);
      return(1);
   };

   if (!(x = SSL_get_peer_certificate(ssl)))
   {
      errmsg[1023] = '\0';
      ERR_error_string_n(ERR_get_error(), errmsg, 1023);
      fprintf(stderr, "servercertinfo: SSL_get_peer_certificate(): %s\n", errmsg);
      client_disconnect(s, ssl, ctx);
      return(1);
   };

   // prints issuer
   name = X509_get_issuer_name(x);
   X509_NAME_oneline(name, xbuff, 1023);
   xbuff[1023] = '\0';
   parse_dn(xbuff, &my_name);
   printf("Issued By:\n");
   print_dn("   ", &my_name);

   // prints issuer
   name = X509_get_subject_name(x);
   X509_NAME_oneline(name, xbuff, 1023);
   xbuff[1023] = '\0';
   parse_dn(xbuff, &my_name);
   printf("Issued To:\n");
   print_dn("   ", &my_name);

   // prints validity
   parse_asn1_time(X509_get_notBefore(x), &ts);
   asctime_r(&ts, timestr);
   timestr[strlen(timestr)-1] = '\0';
   printf("Issued On:       %s\n", timestr);
   parse_asn1_time(X509_get_notAfter(x), &ts);
   asctime_r(&ts, timestr);
   timestr[strlen(timestr)-1] = '\0';
   printf("Expires On:      %s\n", timestr);

   // prints x509 info
   printf("serial:          ");
   printf("%02X", x->cert_info->serialNumber->data[0]);
   for(pos = 1; pos < x->cert_info->serialNumber->length; pos++)
      printf(":%02X", x->cert_info->serialNumber->data[pos]);
   printf("\n");

   // calculate & print fingerprint
   digest = EVP_get_digestbyname("sha1");
   X509_digest(x, digest, md, &n);
   printf("Fingerprint:     ");
   for(pos = 0; pos < 19; pos++)
      printf("%02x:", md[pos]);
   printf("%02x\n", md[19]);

   if (argc == 4)
   {
      if (!(fp = fopen(argv[3], "w")))
      {
         fprintf(stderr, "servercertinfo: fopen(%s, w): %s\n", argv[3], strerror(errno));
         X509_free(x);
         client_disconnect(s, ssl, ctx);
         return(1);
      };
      if ((err = PEM_write_X509(fp, x)) != 1)
      {
         errmsg[1023] = '\0';
         ERR_error_string_n(err, errmsg, 1023);
         fprintf(stderr, "servercertinfo: PEM_write_X509(): %s\n", errmsg);
      };
      fclose(fp);
   };

   // frees resources
   X509_free(x);
   client_disconnect(s, ssl, ctx);

   return(0);
}


/* end of source */
