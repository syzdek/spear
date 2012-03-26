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
 *  @file src/sdk/openssl/serverinfo.c simple hash utility for sha1
 */
/*
 *  Simple Build:
 *     gcc -W -Wall -O2 -c serverinfo.c
 *     gcc -W -Wall -O2 -lcrypto -o serverinfo serverinfo.o
 *
 *  GNU Libtool Build:
 *     libtool --mode=compile gcc -W -Wall -g -O2 -c serverinfo.c
 *     libtool --mode=link    gcc -W -Wall -g -O2 -o serverinfo serverinfo.lo
 *
 *  GNU Libtool Install:
 *     libtool --mode=install install -c serverinfo /usr/local/bin/serverinfo
 *
 *  GNU Libtool Clean:
 *     libtool --mode=clean rm -f serverinfo.lo serverinfo
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
   char * email;
   char * description;
};


//////////////////
//              //
//  Prototypes  //
//              //
//////////////////
#pragma mark - Prototypes

// main statement
int main(int argc, char * argv[]);

// parses DN into componets
void parse_dn(char * dn, MY_X509_NAME * namep);

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
      fprintf(stderr, "serverinfo: SSL_CTX_new(): %s\n", errmsg);
      return(-1);
   };
   *ctxp = ctx;

   if (!(ssl = SSL_new(ctx)))
   {
      errmsg[1023] = '\0';
      ERR_error_string_n(ERR_get_error(), errmsg, 1023);
      fprintf(stderr, "serverinfo: SSL_new(): %s\n", errmsg);
      return(-1);
   };
   *sslp = ssl;

   if ((err = SSL_set_fd(ssl, s)) != 1)
   {
      errmsg[1023] = '\0';
      ERR_error_string_n(ERR_get_error(), errmsg, 1023);
      fprintf(stderr, "serverinfo: SSL_set_fd(): %s\n", errmsg);
      return(-1);
   };

   if ((err = SSL_connect(ssl)) != 1)
   {
      if (err == -1)
         err = ERR_get_error();
      errmsg[1023] = '\0';
      ERR_error_string_n(err, errmsg, 1023);
      fprintf(stderr, "serverinfo: SSL_connect(): %s\n", errmsg);
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

         fprintf(stderr, "serverinfo: connect(%s): %s\n", addr, strerror(errno));
      };
      close(s);
   };
   if (!(hp))
      fprintf(stderr, "serverinfo: gethostbyname2(AF_INET6): %s\n", hstrerror(h_errno));

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

         fprintf(stderr, "serverinfo: connect(%s): %s\n", addr, strerror(errno));
      };
      close(s);
   };
   if (!(hp))
      fprintf(stderr, "serverinfo: gethostbyname2(AF_INET): %s\n", hstrerror(h_errno));

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

   int s;

   // checks arguments
   if ((argc < 3) || (argc > 4))
   {
      fprintf(stderr, "Usage: serverinfo <host> <port> [ <output> ]\n");
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
      fprintf(stderr, "serverinfo: SSL_get_peer_certificate(): %s\n", errmsg);
      client_disconnect(s, ssl, ctx);
      return(1);
   };

   // prints issuer
   name = X509_get_issuer_name(x);
   X509_NAME_oneline(name, xbuff, 1023);
   xbuff[1023] = '\0';
   parse_dn(xbuff, &my_name);
   printf("Issued By:\n");
   if ((my_name.cn))
      printf("   Common Name:  %s\n", my_name.cn);
   if ((my_name.o))
      printf("   Organization: %s\n", my_name.o);
   if ((my_name.ou))
      printf("   Department:   %s\n", my_name.ou);
   if ((my_name.l))
      printf("   City:         %s\n", my_name.l);
   if ((my_name.st))
      printf("   State:        %s\n", my_name.st);
   if ((my_name.c))
      printf("   Country:      %s\n", my_name.c);
   if ((my_name.email))
      printf("   E-mail:       %s\n", my_name.email);
   if ((my_name.description))
      printf("   Description:  %s\n", my_name.description);

   // prints issuer
   name = X509_get_subject_name(x);
   X509_NAME_oneline(name, xbuff, 1023);
   xbuff[1023] = '\0';
   parse_dn(xbuff, &my_name);
   printf("Issued To:\n");
   if ((my_name.cn))
      printf("   Common Name:  %s\n", my_name.cn);
   if ((my_name.o))
      printf("   Organization: %s\n", my_name.o);
   if ((my_name.ou))
      printf("   Department:   %s\n", my_name.ou);
   if ((my_name.l))
      printf("   City:         %s\n", my_name.l);
   if ((my_name.st))
      printf("   State:        %s\n", my_name.st);
   if ((my_name.c))
      printf("   Country:      %s\n", my_name.c);
   if ((my_name.email))
      printf("   E-mail:       %s\n", my_name.email);
   if ((my_name.description))
      printf("   Description:  %s\n", my_name.description);

   // prints validity
   printf("Issued On:       %s\n", x->cert_info->validity->notBefore->data);
   printf("Expires On:      %s\n", x->cert_info->validity->notAfter->data);

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
         fprintf(stderr, "serverinfo: fopen(%s, w): %s\n", argv[3], strerror(errno));
         X509_free(x);
         client_disconnect(s, ssl, ctx);
         return(1);
      };
      if ((err = PEM_write_X509(fp, x)) != 1)
      {
         errmsg[1023] = '\0';
         ERR_error_string_n(err, errmsg, 1023);
         fprintf(stderr, "serverinfo: PEM_write_X509(): %s\n", errmsg);
      };
      fclose(fp);
   };

   // frees resources
   X509_free(x);
   client_disconnect(s, ssl, ctx);

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


/* end of source */
