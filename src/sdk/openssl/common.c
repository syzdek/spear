/*
 *  Simple Programming Examples And References
 *  Copyright (C) 2012 David M. Syzdek <david@syzdek.net>.
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
 *  @file src/sdk/openssl/common.c common functions for openssl examples
 */
#include "common.h"

///////////////
//           //
//  Headers  //
//           //
///////////////
#pragma mark Headers

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <openssl/x509.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/bio.h>


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
      fprintf(stderr, "servercainfo: SSL_CTX_new(): %s\n", errmsg);
      return(-1);
   };
   *ctxp = ctx;

   if (!(ssl = SSL_new(ctx)))
   {
      errmsg[1023] = '\0';
      ERR_error_string_n(ERR_get_error(), errmsg, 1023);
      fprintf(stderr, "servercainfo: SSL_new(): %s\n", errmsg);
      return(-1);
   };
   *sslp = ssl;

   if ((err = SSL_set_fd(ssl, s)) != 1)
   {
      errmsg[1023] = '\0';
      ERR_error_string_n(ERR_get_error(), errmsg, 1023);
      fprintf(stderr, "servercainfo: SSL_set_fd(): %s\n", errmsg);
      return(-1);
   };

   if ((err = SSL_connect(ssl)) != 1)
   {
      if (err == -1)
         err = ERR_get_error();
      errmsg[1023] = '\0';
      ERR_error_string_n(err, errmsg, 1023);
      fprintf(stderr, "servercainfo: SSL_connect(): %s\n", errmsg);
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

         fprintf(stderr, "servercainfo: connect(%s): %s\n", addr, strerror(errno));
      };
      close(s);
   };
   if (!(hp))
      fprintf(stderr, "servercainfo: gethostbyname2(AF_INET6): %s\n", hstrerror(h_errno));

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

         fprintf(stderr, "servercainfo: connect(%s): %s\n", addr, strerror(errno));
      };
      close(s);
   };
   if (!(hp))
      fprintf(stderr, "servercainfo: gethostbyname2(AF_INET): %s\n", hstrerror(h_errno));

   return(-1);
}


// parses ASN1_TIME into struct tm
int parse_asn1_time(const ASN1_TIME * atp, struct tm * tsp)
{
   const char * str;
   unsigned     offset;
   int          val;
   char         buff[5];

   if ((atp->type != V_ASN1_GENERALIZEDTIME) && (atp->type != V_ASN1_UTCTIME))
      return(1);

   memset(tsp, 0, sizeof(struct tm));
   str    = (const char *)atp->data;
   offset = 0;

   // Date format:
   //    YYMMDDHHMMSSZ   - before year 2050
   //    YYYYMMDDHHMMSSZ - after year 2049

   // parses year
   switch(atp->type)
   {
      case V_ASN1_GENERALIZEDTIME:
      sscanf(&str[offset], "%04i", &val);
      val -= 1900;
      tsp->tm_year  = val;
      offset += 4;
      break;

      case V_ASN1_UTCTIME:
      sscanf(&str[offset], "%02i", &val);
      if (val < 50)
         val += 2000 - 1900;
      tsp->tm_year  = val;
      offset += 2;
      break;

      default:
      return(1);
   };

   // parses month
   sscanf(&str[offset], "%02s", buff);
   buff[2]       = '\0';
   val           = strtol(buff, NULL, 10) - 1;
   tsp->tm_mon   = val;
   offset       += 2;

   // parses day of month
   sscanf(&str[offset], "%02s", buff);
   buff[2]       = '\0';
   val           = strtol(buff, NULL, 10);
   tsp->tm_mday  = val;
   offset       += 2;

   // parses hour
   sscanf(&str[offset], "%02s", buff);
   buff[2]       = '\0';
   val           = strtol(buff, NULL, 10);
   tsp->tm_hour  = val;
   offset       += 2;

   // parses minute
   sscanf(&str[offset], "%02s", buff);
   buff[2]       = '\0';
   val           = strtol(buff, NULL, 10);
   tsp->tm_min   = val;
   offset       += 2;

   // parses second
   sscanf(&str[offset], "%02s", buff);
   buff[2]       = '\0';
   val           = strtol(buff, NULL, 10);
   tsp->tm_sec   = val;

   return(0);
}


// parses DN into componets
void parse_dn(char * dn, MY_X509_NAME * namep)
{
   char                * bol;
   char                * eol;

   memset(namep, 0, sizeof(MY_X509_NAME));
   bol = &dn[1];
   while((bol))
   {
      eol    = index(bol, '/');
      if ((eol))
         eol[0] = '\0';
      if      (!(strncasecmp(bol, "C=", 2)))
         namep->c = &bol[2];
      else if (!(strncasecmp(bol, "st=", 3)))
         namep->st = &bol[3];
      else if (!(strncasecmp(bol, "l=", 2)))
         namep->l = &bol[2];
      else if (!(strncasecmp(bol, "o=", 2)))
         namep->o = &bol[2];
      else if (!(strncasecmp(bol, "ou=", 3)))
         namep->ou = &bol[3];
      else if (!(strncasecmp(bol, "gn=", 3)))
         namep->gn = &bol[3];
      else if (!(strncasecmp(bol, "sn=", 3)))
         namep->sn = &bol[3];
      else if (!(strncasecmp(bol, "cn=", 3)))
         namep->cn = &bol[3];
      else if (!(strncasecmp(bol, "emailAddress=", 13)))
         namep->email = &bol[13];
      else if (!(strncasecmp(bol, "description=", 13)))
         namep->description = &bol[13];
      bol    = ((eol)) ? &eol[1] : NULL;
   };
   return;
}


// prints dn
void print_dn(const char * prefix, MY_X509_NAME * namep)
{
   if (!(prefix))
      prefix = "";

   if ((namep->gn))
      printf("%sGiven Name:   %s\n", prefix, namep->gn);
   if ((namep->sn))
      printf("%sSurname:      %s\n", prefix, namep->sn);
   if ((namep->cn))
      printf("%sCommon Name:  %s\n", prefix, namep->cn);
   if ((namep->o))
      printf("%sOrganization: %s\n", prefix, namep->o);
   if ((namep->ou))
      printf("%sDepartment:   %s\n", prefix, namep->ou);
   if ((namep->l))
      printf("%sCity:         %s\n", prefix, namep->l);
   if ((namep->st))
      printf("%sState:        %s\n", prefix, namep->st);
   if ((namep->c))
      printf("%sCountry:      %s\n", prefix, namep->c);
   if ((namep->email))
      printf("%sE-mail:       %s\n", prefix, namep->email);
   if ((namep->description))
      printf("%sDescription:  %s\n", prefix, namep->description);

   return;
}


/* end of source */
