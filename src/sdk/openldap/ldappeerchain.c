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
 *  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL DAVID M. SYZDEK BE LIABLE FOR
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
 *  @file src/sdk/openldap/ldappeerchain.c downloads TLS/SSL certificate from LDAP server
 */
/*
 *  Simple Build:
 *     gcc -W -Wall -O2 -c ldappeerchain.c
 *     gcc -W -Wall -O2 -lldap -llber -lcrypto -lssl -o ldappeerchain ldappeerchain.o
 *
 *  GNU Libtool Build:
 *     libtool --mode=compile gcc -W -Wall -g -O2 -c ldappeerchain.c
 *     libtool --mode=link    gcc -W -Wall -g -O2 -lldap -llber -lcrypto \
 *                                -lssl -o ldappeerchain ldappeerchain.lo
 *
 *  GNU Libtool Install:
 *     libtool --mode=install install -c ldappeerchain /usr/local/bin/ldappeerchain
 *
 *  GNU Libtool Clean:
 *     libtool --mode=clean rm -f ldappeerchain.lo ldappeerchain
 */
/*
 *  NOTES:
 *     Only works with OpenSSL.
 */


///////////////
//           //
//  Headers  //
//           //
///////////////
#ifdef PMARK
#pragma mark - Headers
#endif

#include <stdio.h>
#include <ldap.h>
#include <sasl/sasl.h>
#include <getopt.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdarg.h>
#include <fcntl.h>
#include <openssl/x509.h>
#include <openssl/ssl.h>
#include <openssl/err.h>


///////////////////
//               //
//  Definitions  //
//               //
///////////////////
#ifdef PMARK
#pragma mark - Definitions & Macros
#endif

#ifndef PROGRAM_NAME
#define PROGRAM_NAME "ldappeerchain"
#endif

#ifndef PACKAGE_BUGREPORT
#define PACKAGE_BUGREPORT "syzdek@bindlebinaries.com"
#endif

#ifndef PACKAGE_NAME
#define PACKAGE_NAME "Simple Programming Examples And References"
#endif

#ifndef PACKAGE_VERSION
#define PACKAGE_VERSION ""
#endif


/////////////////
//             //
//  Datatypes  //
//             //
/////////////////
#ifdef PMARK
#pragma mark - Datatypes
#endif


/// @brief stores data for interactive SASL authentication
typedef struct ldappeerchain_config LDAPConfig;
struct ldappeerchain_config
{
   int              verbose;
   int              quiet;
   char             ldap_url[1024];
   int              ldap_version;
   struct timeval   tcp_timeout;
   LDAPURLDesc    * ludp;
};


//////////////////
//              //
//  Prototypes  //
//              //
//////////////////
#ifdef PMARK
#pragma mark - Prototypes
#endif

// TLS callback function
void ldappeerchain_tls_cb(LDAP * ld, SSL * ssl, SSL_CTX * ctx, void * arg);

// displays usage information
void ldappeerchain_usage(void);

// print verbose message
void ldappeerchain_verbose(LDAPConfig * cnfp, const char * fmt, ...);

// displays version information
void ldappeerchain_version(void);
   
// main execution loop
int main(int argc, char * argv[]);


/////////////////
//             //
//  Functions  //
//             //
/////////////////
#ifdef PMARK
#pragma mark - Functions
#endif

/// TLS callback function
void ldappeerchain_tls_cb(LDAP * ld, SSL * ssl, SSL_CTX * ctx, void * arg)
{ 
   ld  = NULL;

   *((SSL **)arg) = ssl;

   SSL_CTX_set_verify(ctx, SSL_VERIFY_NONE, NULL);
   SSL_set_verify(ssl, SSL_VERIFY_NONE, NULL);

   return;
}


/// @brief displays usage information
void ldappeerchain_usage(void)
{
   printf(("Usage: %s [OPTIONS] <filename>\n"
         "  -2                        use protocol version 2\n"
         "  -3                        use protocol version 3\n"
         "  -H url                    LDAP URL\n"
         "  -h, --help                print this help and exit\n"
         "  -q, --quiet               suppresses informational messages\n"
         "  -T timeout                TCP timeout\n"
         "  -V, --version             displays version\n"
         "  -v, --verbose             enable verbose messages\n"
         "\n"
         "LDAP URL: ldap://hostport/dn[?attrs[?scope[?filter[?exts]]]]\n"
         "\n"
         "   example: ldap://ldap.example.net/dc=example,dc=net?cn,sn?sub?(cn=*)\n"
         "\n"
         "Report bugs to <%s>.\n"
      ), PROGRAM_NAME, PACKAGE_BUGREPORT);
   return;
}


/// @brief print verbose message
/// @param verbose    verbose level
/// @param fmt        printf format
/// @param ...        printf format arguments
void ldappeerchain_verbose(LDAPConfig * cnfp, const char * fmt, ...)
{
   va_list args;

   if (cnfp->verbose < 1)
      return;

   va_start(args, fmt);
   vfprintf (stderr, fmt, args );
   va_end(args);

   return;
}


/// @brief displays version information
void ldappeerchain_version(void)
{
   printf(("%s (%s) %s\n"
         "Written by David M. Syzdek.\n"
         "\n"
         "Copyright 2012 David M. Syzdek <david@syzdek.net>.\n"
         "This is free software; see the source for copying conditions.  There is NO\n"
         "warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n"
      ), PROGRAM_NAME, PACKAGE_NAME, PACKAGE_VERSION
   );
   return;
}


/// @brief main loop
/// @param argc       number of arguments passed to program
/// @param argv       array of arguments passed to program
int main(int argc, char * argv[])
{
   // local variables
   LDAPConfig       config;
   struct timeval * timeoutp;
   LDAP           * ld;
   int              err;
   char           * errmsg;
   //int              opt;
   X509           * x;
   SSL            * ssl;
   void           * invalue;
   char             msg[1024];
   char           * datafile;
   int              skpos;
   STACK_OF(X509) * skx;
   BerValue         cred;
   BerValue       * servercredp;
   BIO            * mem;
   int              fd;
   char           * fbuff;
   char             rbuff[1024];
   int              flen;
   int              rlen;
   void           * ptr;

   // local variables for parsing cli arguments
   int                  c;
   int                  opt_index;
   static char          short_opt[] = "23H:hT:qVv";
   static struct option long_opt[] =
   {
      {"help",          no_argument, 0, 'h'},
      {"silent",        no_argument, 0, 'q'},
      {"quiet",         no_argument, 0, 'q'},
      {"verbose",       no_argument, 0, 'v'},
      {"version",       no_argument, 0, 'V'},
      {NULL,            0,           0, 0  }
   };

   // reset config data
   memset(&config, 0, sizeof(LDAPConfig));
   memset(&cred,   0, sizeof(BerValue));
   strncpy(config.ldap_url, "ldap://localhost/", 1024);
   config.ldap_version = LDAP_VERSION3;
   timeoutp            = NULL;
   ssl                 = NULL;
   x                   = NULL;
   servercredp         = NULL;

   // processes command line arguments
   while((c = getopt_long(argc, argv, short_opt, long_opt, &opt_index)) != -1)
   {
      switch(c)
      {
         case -1:       /* no more arguments */
         case 0:        /* long options toggles */
         break;

         case '2':
         config.ldap_version = LDAP_VERSION2;
         break;

         case '3':
         config.ldap_version = LDAP_VERSION3;
         break;

         case 'H':
         if ((ldap_url_parse(optarg, &config.ludp)))
         {
            fprintf(stderr, "ldap_url_parse(): invalid LDAP URL\n");
            return(1);
         };
         snprintf(config.ldap_url, 1024, "%s://%s:%i",
         config.ludp->lud_scheme, config.ludp->lud_host,
         config.ludp->lud_port);
         break;

         case 'h':
         ldappeerchain_usage();
         return(0);

         case 'q':
         config.quiet++;
         break;

         case 'T':
         config.tcp_timeout.tv_sec = (int) strtol(optarg, NULL, 0);
         break;

         case 'V':
         ldappeerchain_version();
         return(0);

         case 'v':
         config.verbose++;
         break;

         case '?':
         fprintf(stderr, "Try `%s --help' for more information.\n", PROGRAM_NAME);
         return(1);

         default:
         fprintf(stderr, "%s: unrecognized option `-%c'\n", PROGRAM_NAME, c);
         fprintf(stderr, "Try `%s --help' for more information.\n", PROGRAM_NAME);
         return(1);
      };
   };

   // checks for unknown options
   if (((optind+1) != argc) && (optind != argc))
   {
      fprintf(stderr, "%s: too many arguments\n", PROGRAM_NAME);
      fprintf(stderr, "Try `%s --help' for more information.\n", PROGRAM_NAME);
      return(1);
   };
   datafile = NULL;
   if ((optind+1) == argc)
      datafile = argv[optind];

   // checks for required arguments
   if (!(config.ludp))
   {
      fprintf(stderr, "%s: missing required option `-H'\n", PROGRAM_NAME);
      fprintf(stderr, "Try `%s --help' for more information.\n", PROGRAM_NAME);
      return(1);
   };


   //
   //  initializes LDAP instance
   //


   // initialize LDAP handle
   ldappeerchain_verbose(&config, "ldap_initialize()\n");
   if ((err = ldap_initialize(&ld, config.ldap_url)) != LDAP_SUCCESS)
   {
      fprintf(stderr, "ldap_initialize(): %s\n", ldap_err2string(err));
      return(1);
   };


   //
   //  configure's LDAP instance
   //


   // set LDAP protocol version
   ldappeerchain_verbose(&config, "ldap_set_option(LDAP_OPT_PROTOCOL_VERSION)\n");
   err = ldap_set_option(ld, LDAP_OPT_PROTOCOL_VERSION, &config.ldap_version);
   if (err != LDAP_SUCCESS)
   {
      fprintf(stderr, "ldap_set_option(PROTOCOL_VERSION): %s\n", ldap_err2string(err));
      ldap_unbind_ext_s(ld, NULL, NULL);
      return(1);
   };

   // set TLS callback function argument version
   ldappeerchain_verbose(&config, "ldap_set_option(LDAP_OPT_X_TLS_CONNECT_ARG)\n");
   err = ldap_set_option(ld, LDAP_OPT_X_TLS_CONNECT_ARG, &ssl);
   if (err != LDAP_SUCCESS)
   {
      fprintf(stderr, "ldap_set_option(LDAP_OPT_X_TLS_CONNECT_ARG): %s\n", ldap_err2string(err));
      ldap_unbind_ext_s(ld, NULL, NULL);
      return(1);
   };

   // set TLS callback function
   invalue = (void *)ldappeerchain_tls_cb;
   ldappeerchain_verbose(&config, "ldap_set_option(LDAP_OPT_X_TLS_CONNECT_CB)\n");
   err = ldap_set_option(ld, LDAP_OPT_X_TLS_CONNECT_CB, invalue);
   if (err != LDAP_SUCCESS)
   {
      fprintf(stderr, "ldap_set_option(LDAP_OPT_X_TLS_CONNECT_CB): %s\n", ldap_err2string(err));
      ldap_unbind_ext_s(ld, NULL, NULL);
      return(1);
   };

   // set network timout
   if ((config.tcp_timeout.tv_sec))
   {
      ldappeerchain_verbose(&config, "ldap_set_option(LDAP_OPT_NETWORK_TIMEOUT)\n");
      err = ldap_set_option(ld, LDAP_OPT_NETWORK_TIMEOUT, &config.tcp_timeout);
      if (err != LDAP_SUCCESS)
      {
         fprintf(stderr, "ldap_set_option(SIZELIMIT): %s\n", ldap_err2string(err));
         ldap_unbind_ext_s(ld, NULL, NULL);
         return(1);
      };
   };


   //
   //  starts TLS/SSL connections
   //

   // starts connection if using TLS
   if ((strcasecmp(config.ludp->lud_scheme, "ldaps")))
   {
      ldappeerchain_verbose(&config, "ldap_start_tls_s()\n");
      err = ldap_start_tls_s(ld, NULL, NULL);
      switch(err)
      {
         case LDAP_SUCCESS:
         break;

         case LDAP_CONNECT_ERROR:
         ldap_get_option(ld, LDAP_OPT_DIAGNOSTIC_MESSAGE, (void*)&errmsg);
         fprintf(stderr, "ldap_start_tls_s(): %s\n", errmsg);
         ldap_memfree(errmsg);
         ldap_unbind_ext_s(ld, NULL, NULL);
         return(1);

         default:
         fprintf(stderr, "ldap_start_tls_s(): %s\n", ldap_err2string(err));
         ldap_unbind_ext_s(ld, NULL, NULL);
         return(1);
      };
   };

   // uses anonymous binds to start SSL connection
   if (!(strcasecmp(config.ludp->lud_scheme, "ldaps")))
   {
      ldappeerchain_verbose(&config, "ldap_sasl_bind_s()\n");
      err = ldap_sasl_bind_s
      (
         ld,                // LDAP           * ld
         NULL,              // const char     * dn
         LDAP_SASL_SIMPLE,  // const char     * mechanism
         &cred,             // struct berval  * cred
         NULL,              // LDAPControl    * sctrls[]
         NULL,              // LDAPControl    * cctrls[]
         &servercredp       // struct berval ** servercredp
      );
      if (err != LDAP_SUCCESS)
      {
         fprintf(stderr, "ldap_sasl_bind_s(): %s\n", ldap_err2string(err));
         ldap_unbind_ext_s(ld, NULL, NULL);
         return(1);
      };
   };


   //
   //  writes certificates to file
   //

   // retrieves SSL handle
   if (!(ssl))
   {
      ldappeerchain_verbose(&config, "ldap_get_option(LDAP_OPT_X_TLS_SSL_CTX)\n");
      ldap_get_option(ld, LDAP_OPT_X_TLS_SSL_CTX, &ssl);
   };
   if (!(ssl))
   {
      fprintf(stderr, "ldappeerchain: unable to retrieve SSL handle\n");
      ldap_unbind_ext_s(ld, NULL, NULL);
      return(1);
   };

   // retrieves stack of certs from peer
   ldappeerchain_verbose(&config, "SSL_get_peer_cert_chain()\n");
   if (!(skx = SSL_get_peer_cert_chain(ssl)))
   {
      msg[1023] = '\0';
      ERR_error_string_n(ERR_get_error(), msg, 1023);
      fprintf(stderr, "ldappeerchain: SSL_get_peer_cert_chain(): %s\n", msg);
      ldap_unbind_ext_s(ld, NULL, NULL);
      return(1);
   };
   if (!(config.quiet))
      fprintf(stderr, "%i certificates in peer chain\n", sk_num(skx));

   // Creates new BIO
   ldappeerchain_verbose(&config, "BIO_new()\n");
   if (!(mem = BIO_new(BIO_s_mem())))
   {
      ERR_error_string_n(ERR_get_error(), msg, 1023);
      fprintf(stderr, "ldappeerchain: BIO_new(): %s\n", msg);
      ldap_unbind_ext_s(ld, NULL, NULL);
      return(1);
   };

   // loops through stack
   for(skpos = 0; skpos < sk_num(skx); skpos++)
   {
      x = (X509 *)sk_value(skx, skpos);
      ldappeerchain_verbose(&config, "PEM_write_bio_X509()\n");
      if ((err = PEM_write_bio_X509(mem, x)) != 1)
      //if ((err = PEM_write_X509(fp, x)) != 1)
      {
         msg[1023] = '\0';
         ERR_error_string_n(err, msg, 1023);
         fprintf(stderr, "ldappeerchain: PEM_write_bio_X509(): %s\n", msg);
      };
   };

   // opens file for writing
   fd = STDOUT_FILENO;
   if ((datafile))
   {
      ldappeerchain_verbose(&config, "open(%s)\n", datafile);
      fd = open(datafile, O_WRONLY|O_CREAT|O_APPEND, 0644);
   };
   if (fd == -1)
   {
      fprintf(stderr, "ldappeerchain: open(%s, w): %s\n", datafile, strerror(errno));
      BIO_free(mem);
      ldap_unbind_ext_s(ld, NULL, NULL);
      return(1);
   };

   // prints data to file handle
   flen  = 0;
   fbuff = NULL;
   while((rlen = BIO_read(mem, rbuff, 1024)) > 0)
   {
      if ((ptr = realloc(fbuff, flen+rlen)))
      {
         fbuff = ptr;
         memcpy(&fbuff[flen], rbuff, rlen);
         flen += rlen;
      };
   };
   ldappeerchain_verbose(&config, "write()\n");
   write(fd, fbuff, flen);

   // frees buffer
   free(fbuff);

   // closes file
   if ((datafile))
   {
      ldappeerchain_verbose(&config, "close()\n");
      close(fd);
   };

   // frees bio
   ldappeerchain_verbose(&config, "BIO_free()\n");
   BIO_free(mem);


   //
   //  ends connection and frees resources
   //


   // unbind from LDAP server
   ldappeerchain_verbose(&config, "ldap_unbind_ext_s()\n");
   ldap_unbind_ext_s(ld, NULL, NULL);

   // frees resources
   ldappeerchain_verbose(&config, "ldap_free_urldesc()\n");
   ldap_free_urldesc(config.ludp);

   return(0);
}

/* end of source */
