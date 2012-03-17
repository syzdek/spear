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
 *  @file src/sdk/openldap/ldapmodify-async.c an example of an LDAP asynchronous
 *                                            search using an LDAP API.
 */
/*
 *  Simple Build:
 *     gcc -W -Wall -O2 -c ldapmodify-async.c
 *     gcc -W -Wall -O2 -lldap -llber -o ldapmodify-async ldapmodify-async.o
 *
 *  GNU Libtool Build:
 *     libtool --mode=compile gcc -W -Wall -g -O2 -c ldapmodify-async.c
 *     libtool --mode=link    gcc -W -Wall -g -O2 -lldap -llber -o ldapmodify-async ldapmodify-async.lo
 *
 *  GNU Libtool Install:
 *     libtool --mode=install install -c ldapmodify-async /usr/local/bin/ldapmodify-async
 *
 *  GNU Libtool Clean:
 *     libtool --mode=clean rm -f ldapmodify-async.lo ldapmodify-async
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
#include <getopt.h>

#include "ldapcommon.h"


///////////////////
//               //
//  Definitions  //
//               //
///////////////////
#ifdef PMARK
#pragma mark - Definitions & Macros
#endif

#ifndef PROGRAM_NAME
#define PROGRAM_NAME "ldapmodify-async"
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


//////////////////
//              //
//  Prototypes  //
//              //
//////////////////
#ifdef PMARK
#pragma mark - Prototypes
#endif

// retrieves information during interactive SASL auth attempt
int ldapexample_sasl_interact(LDAP * ld, unsigned flags, void * defaults,
   void * sin);

// displays usage information
void ldapexample_usage(void);

// displays version information
void ldapexample_version(void);
   
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

/// @brief displays usage information
void ldapexample_usage(void)
{
   printf(("Usage: %s [OPTIONS] add attribute value\n"
         "         %s [OPTIONS] delete attribute [ value ]\n"
         "         %s [OPTIONS] replace attribute [ [ oldValue ] newValue ]\n"
         "  -2                        use protocol version 2\n"
         "  -3                        use protocol version 3\n"
         "  -C file                   file containing CA certificates\n"
         "  -D dn                     bind DN\n"
         "  -H url                    LDAP URL\n"
         "  -h, --help                print this help and exit\n"
         "  -T timeout                TCP timeout\n"
         "  -t timeout                search timeout\n"
         "  -U user                   SASL bind user\n"
         "  -w password               bind password\n"
         "  -Y mech                   SASL bind mechanism\n"
         "  -Z                        Start TLS request (-ZZ verify hostname matches)\n"
         "\n"
         "Report bugs to <%s>.\n"
      ), PROGRAM_NAME, PROGRAM_NAME, PROGRAM_NAME, PACKAGE_BUGREPORT);
   return;
}


// displays version information
void ldapexample_version(void)
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
   int              opt;
   BerValue       * servercredp;
   int              msgid;
   int              msgtype;
   int              msgcount;
   LDAPMessage    * res;
   char           * dn;
   const char     * attribute;
   BerElement     * ber;
   BerValue      ** vals;
   int              pos;

   // local variables for parsing cli arguments
   int                  c;
   int                  opt_index;
   static char          short_opt[] = "23C:D:H:hT:t:U:Vvw:Y:Z";
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
   strncpy(config.ldap_url, "ldap://localhost/", 1024);
   config.ldap_version   = LDAP_VERSION3;
   timeoutp = NULL;

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
         case 'D':
            config.auth.dn       = optarg;
            break;
         case 'C':
            config.ldap_ca = optarg;
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
            ldapexample_usage();
            return(0);
         case 'T':
            config.tcp_timeout.tv_sec = (int) strtol(optarg, NULL, 0);
            break;
         case 't':
            config.search_timeout.tv_sec = (int) strtol(optarg, NULL, 0);
            timeoutp = &config.search_timeout;
            break;
         case 'U':
            config.auth.authuser = optarg;
            break;
         case 'V':
            ldapexample_version();
            return(0);
         case 'v':
            config.verbose++;
            break;
         case 'w':
            config.auth.cred.bv_val = optarg;
            config.auth.cred.bv_len = strlen(config.auth.cred.bv_val);
            break;
         case 'Y':
            config.auth.saslmech = optarg;
            break;
         case 'Z':
            config.ldap_tls++;
            break;
         case '?':
            fprintf(stderr, "Try `%s --help' for more information.\n", PROGRAM_NAME);
            return(1);
         default:
            fprintf(stderr, "%s: unrecognized option `--%c'\n", PROGRAM_NAME, c);
            fprintf(stderr, "Try `%s --help' for more information.\n", PROGRAM_NAME);
            return(1);
      };
   };

   // checks for unknown options
   if (optind != argc)
   {
      fprintf(stderr, "%s: too many arguments\n", PROGRAM_NAME);
      fprintf(stderr, "Try `%s --help' for more information.\n", PROGRAM_NAME);
      return(1);
   };

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
   ldapexample_verbose(&config, "ldap_initialize()\n");
   if ((err = ldap_initialize(&ld, config.ldap_url)) != LDAP_SUCCESS)
   {
      fprintf(stderr, "ldap_initialize(): %s\n", ldap_err2string(err));
      return(1);
   };


   //
   //  configure's LDAP instance
   //


   // set LDAP protocol version
   ldapexample_verbose(&config, "ldap_set_option(LDAP_OPT_PROTOCOL_VERSION)\n");
   err = ldap_set_option(ld, LDAP_OPT_PROTOCOL_VERSION, &config.ldap_version);
   if (err != LDAP_SUCCESS)
   {
      fprintf(stderr, "ldap_set_option(PROTOCOL_VERSION): %s\n", ldap_err2string(err));
      ldap_unbind_ext_s(ld, NULL, NULL);
      return(1);
   };

   // set network timout
   if ((config.tcp_timeout.tv_sec))
   {
      ldapexample_verbose(&config, "ldap_set_option(LDAP_OPT_NETWORK_TIMEOUT)\n");
      err = ldap_set_option(ld, LDAP_OPT_NETWORK_TIMEOUT, &config.tcp_timeout);
      if (err != LDAP_SUCCESS)
      {
         fprintf(stderr, "ldap_set_option(SIZELIMIT): %s\n", ldap_err2string(err));
         ldap_unbind_ext_s(ld, NULL, NULL);
         return(1);
      };
   };

   // set LDAP search size limit
   ldapexample_verbose(&config, "ldap_set_option(LDAP_OPT_SIZELIMIT)\n");
   err = ldap_set_option(ld, LDAP_OPT_SIZELIMIT, &config.search_limit);
   if (err != LDAP_SUCCESS)
   {
      fprintf(stderr, "ldap_set_option(SIZELIMIT): %s\n", ldap_err2string(err));
      ldap_unbind_ext_s(ld, NULL, NULL);
      return(1);
   };

   // set LDAP instance to require SSL cert
   opt = LDAP_OPT_X_TLS_NEVER;
   if (config.ldap_tls > 1)
      opt = LDAP_OPT_X_TLS_DEMAND;
   ldapexample_verbose(&config, "ldap_set_option(TLS_REQUIRE_CERT)\n");
   err = ldap_set_option(ld, LDAP_OPT_X_TLS_REQUIRE_CERT, &opt);
   if (err != LDAP_SUCCESS)
   {
      fprintf(stderr, "ldap_set_option(TLS_REQUIRE_CERT): %s\n", ldap_err2string(err));
      ldap_unbind_ext_s(ld, NULL, NULL);
      return(1);
   };

   // set SSL/TLS CA cert file
   if ((config.ldap_ca))
   {
      ldapexample_verbose(&config, "ldap_set_option(LDAP_OPT_X_TLS_CACERTFILE)\n");
      err = ldap_set_option(NULL, LDAP_OPT_X_TLS_CACERTFILE, (void *)config.ldap_ca);
      if (err != LDAP_SUCCESS)
      {
         fprintf(stderr, "ldap_set_option(TLS_CACERTFILE): %s\n", ldap_err2string(err));
         ldap_unbind_ext_s(ld, NULL, NULL);
         return(1);
      };
   };


   //
   //  starts TLS/SSL connections
   //


   // starts SSL connection
   if ((config.ldap_tls))
   {
      ldapexample_verbose(&config, "ldap_start_tls_s()\n");
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


   //
   //  bind
   //


   // binds to system with simple bind
   if (!(config.auth.saslmech))
   {
      ldapexample_verbose(&config, "ldap_sasl_bind_s()\n");
      err = ldap_sasl_bind_s
      (
         ld,                // LDAP           * ld
         config.auth.dn,    // const char     * dn
         LDAP_SASL_SIMPLE,  // const char     * mechanism
         &config.auth.cred, // struct berval  * cred
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

   // binds to system with SASL bind
   if ((config.auth.saslmech))
   {
      ldapexample_verbose(&config, "ldap_sasl_interactive_bind_s()\n");
      err = ldap_sasl_interactive_bind_s
      (
         ld,                         // LDAP                    * ld
         NULL,                       // const char              * dn
         config.auth.saslmech,       // const char              * mechs
         NULL,                       // LDAPControl             * sctrls[]
         NULL,                       // LDAPControl             * cctrls[]
         LDAP_SASL_QUIET,            // unsigned                  flags
         ldapexample_sasl_interact,  // LDAP_SASL_INTERACT_PROC * interact
         &config.auth                // void                    * defaults
      );
      if (err != LDAP_SUCCESS)
      {
         fprintf(stderr, "ldap_sasl_interactive_bind_s(): %s\n", ldap_err2string(err));
         ldap_get_option(ld, LDAP_OPT_DIAGNOSTIC_MESSAGE, (void*)&errmsg);
         fprintf(stderr, "ldap_sasl_interactive_bind_s(): %s\n", errmsg);
         ldap_memfree(errmsg);
         ldap_unbind_ext_s(ld, NULL, NULL);
         return(1);
      };
   };

   //
   //  search query
   //


   // perform search
   ldapexample_verbose(&config, "ldap_modify_ext()\n");
   err = ldap_modify_ext(
      ld,                    // LDAP            * ld
      config.ludp->lud_dn,   // char            * base
      mods,                  // LDAPMod      * mods[]
      NULL,                  // LDAPControl ** sctrls
      NULL,                  // LDAPControl ** cctrls
      &msgid                 // int          * msgidp
   );
   if (err != LDAP_SUCCESS)
   {
      fprintf(stderr, "ldap_result(): %s\n", ldap_err2string(err));
      ldap_unbind_ext_s(ld, NULL, NULL);
      return(1);
   };

   // loops through results from search
   msgtype  = LDAP_RES_SEARCH_ENTRY;
   for(msgcount = 0; msgtype != LDAP_RES_SEARCH_RESULT; msgcount++)
   {
      // retrieves result
      ldapexample_verbose(&config, "ldap_result()\n");
      err = ldap_result(ld, msgid, 0, timeoutp, &res);
      switch(err)
      {
         case -1:
            ldap_get_option(ld, LDAP_OPT_RESULT_CODE, &err);
            fprintf(stderr, "ldap_result(): %s\n", ldap_err2string(err));
            return(1);
         case 0:
            fprintf(stderr, "ldap_result(): timeout expired\n");
            ldap_abandon_ext(ld, msgid, NULL, NULL);
            ldap_unbind_ext_s(ld, NULL, NULL);
            return(1);
         default:
            break;
      };

      // determines result type
      msgtype = ldap_msgtype(res);
      if (msgtype != LDAP_RES_SEARCH_ENTRY)
         continue;

      // prints DN
      dn = ldap_get_dn(ld, res);
      fprintf(stderr, "dn: %s\n", dn);
      ldap_memfree(dn);

      // loops through attributes and values
      attribute = ldap_first_attribute(ld, res, &ber);
      while((attribute))
      {
         vals = ldap_get_values_len(ld, res, attribute);
         for(pos = 0; pos < ldap_count_values_len(vals); pos++)
            printf("%s: %s\n", attribute, vals[pos]->bv_val);
         ldap_value_free_len(vals);
         attribute = ldap_next_attribute(ld, res, ber);
      };
      ber_free(ber, 0);

      // frees result
      ldap_memfree(res);
      printf("\n");
   };

   // parses search result
   ldapexample_verbose(&config, "ldap_parse_result()\n");
   ldap_parse_result(ld, res, &err, NULL, NULL, NULL, NULL, 0);
   ldap_memfree(res);
   printf("# result:  (%i) %s\n", err, ldap_err2string(err));
   printf("# entries: %i\n", msgcount-1);


   //
   //  ends connection and frees resources
   //


   // unbind from LDAP server
   ldapexample_verbose(&config, "ldap_unbind_ext_s()\n");
   ldap_unbind_ext_s(ld, NULL, NULL);

   // frees resources
   ldapexample_verbose(&config, "ldap_free_urldesc()\n");
   ldap_free_urldesc(config.ludp);

   return(0);
}

/* end of source */
