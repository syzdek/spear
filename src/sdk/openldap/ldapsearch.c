/*
 *  Simple Programming Examples And References
 *  Copyright (C) 2010 David M. Syzdek <david@syzdek.net>.
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
 *  @file src/sdk/openldap/ldapsearch.c simple LDAP search example
 */
/*
 *  Simple Build:
 *     gcc -W -Wall -O2 -c ldap_common.c
 *     gcc -W -Wall -O2 -c ldapsearch.c
 *     gcc -W -Wall -O2 -lldap -llber -o ldapsearch ldapsearch.o ldap_common.o
 *
 *  GNU Libtool Build:
 *     libtool --mode=compile gcc -W -Wall -g -O2 -c codetagger.c
 *     libtool --mode=link    gcc -W -Wall -g -O2 -o codetagger codetagger.lo
 *
 *  GNU Libtool Install:
 *     libtool --mode=install install -c codetagger /usr/local/bin/codetagger
 *
 *  GNU Libtool Clean:
 *     libtool --mode=clean rm -f codetagger.lo codetagger
 */

///////////////
//           //
//  Headers  //
//           //
///////////////
#pragma mark Headers

#include <stdio.h>
#include <getopt.h>
#include <inttypes.h>
#include <stdlib.h>
#include <ldap.h>

#include "ldapcommon.h"


///////////////////
//               //
//  Definitions  //
//               //
///////////////////
#pragma mark -
#pragma mark Definitions & Macros

#undef PROGRAM_NAME
#define PROGRAM_NAME "ldapsearch"

#undef PACKAGE_BUGREPORT
#define PACKAGE_BUGREPORT "david@syzdek.net"

#undef PACKAGE_NAME
#define PACKAGE_NAME "Simple Programming Examples And References"

#undef PACKAGE_VERSION
#define PACKAGE_VERSION "0.1"


//////////////////
//              //
//  Prototypes  //
//              //
//////////////////
#pragma mark -
#pragma mark Prototypes

// displays usage
void ldapsearch_usage(void);

// displays version information
void ldapsearch_version(void);

// main statement
int main(int argc, char * argv[]);


/////////////////
//             //
//  Functions  //
//             //
/////////////////
#pragma mark -
#pragma mark Functions

/// displays usage
void ldapsearch_usage(void)
{
   printf(("Usage: %s [OPTIONS] [filter [attributes...]]\n"
         "  -b  basedn                base DN for LDAP search\n"
         "  -c                        do not exit on errors\n"
         "  -D  binddn                bind DN\n"
         "  -d  level                 debugging level\n"
         "  -H  URI                   LDAP Uniform Resource Identifier\n"
         "  -h, --help                print this help and exit\n"
         "  -l  limit                 time limit for search\n"
         "  -P  version               protocol version\n"
         "  -q, --quiet, --silent     do not print messages\n"
         "  -R  realm                 SASL realm (if using SASL auth)\n"
         "  -s  scope                 LDAP search scope (base, one, sub, or children)\n"
         "  -U  authcid               SASL authentication identity (initiates SASL auth)\n"
         "  -V, --version             print version number and exit\n"
         "  -v, --verbose             print verbose messages\n"
         "  -w  passwd                bind password\n"
         "  -Y  mech                  SASL mechanism (if using SASL auth)\n"
         "  -Z                        use TLS\n"
         "  -z limit                  size limit for search\n"
         "\n"
         "Report bugs to <%s>.\n"
      ), PROGRAM_NAME, PACKAGE_BUGREPORT
   );
   return;
}


/// displays version information
void ldapsearch_version(void)
{
   printf(("%s (%s) %s\n"
         "Written by David M. Syzdek.\n"
         "\n"
         "Copyright 2010 David M. Syzdek <david@syzdek.net>.\n"
         "This is free software; see the source for copying conditions.  There is NO\n"
         "warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n"
      ), PROGRAM_NAME, PACKAGE_NAME, PACKAGE_VERSION
   );
   return;
}


/// main statement
/// @param[in]  argc  number of arguments passed to program
/// @param[in]  argv  array of arguments passed to program
int main(int argc, char * argv[])
{
   int           c;
   int           i;
   int           err;
   int           opt_index;
   char        * attribute;
   char       ** attrs;
   BerElement  * ber;
   LDAPMessage * res;
   LDAPMessage * entry;
   LDAPConfig    cnf;  // LDAPConfig is a custom datatype defined in ldap_common.h
   struct berval ** vals;

   static char   short_opt[] = "b:cD:d:H:hl:P:q:R:s:U:Vvw:Y:Zz:";
   static struct option long_opt[] =
   {
      {"help",          no_argument, 0, 'h'},
      {"silent",        no_argument, 0, 'q'},
      {"quiet",         no_argument, 0, 'q'},
      {"verbose",       no_argument, 0, 'v'},
      {"version",       no_argument, 0, 'V'},
      {NULL,            0,           0, 0  }
   };

   memset(&cnf, 0, sizeof(LDAPConfig));

   while((c = getopt_long(argc, argv, short_opt, long_opt, &opt_index)) != -1)
   {
      switch(c)
      {
         case -1:	/* no more arguments */
         case 0:	/* long options toggles */
            break;
         case 'b':
            cnf.ldapBaseDN = optarg;
            break;
         case 'c':
            break;
         case 'D':
            cnf.ldapBindDN = optarg;
            break;
         case 'd':
            cnf.ldapDebug = strtol(optarg, NULL, 0);
            break;
         case 'H':
            cnf.ldapURI = optarg;
            break;
         case 'h':
            ldapsearch_usage();
            return(0);
         case 'l':
            cnf.ldapTimeLimit = strtol(optarg, NULL, 0);
            break;
         case 'P':
            switch(strtol(optarg, NULL, 0))
            {
               case 2:  cnf.ldapVersion = LDAP_VERSION2; break;
               case 3:  cnf.ldapVersion = LDAP_VERSION3; break;
               default:
                  fprintf(stderr, "%s: version should be 2 or 3\n", PROGRAM_NAME);
                  fprintf(stderr, "Try `%s --help' for more information.\n", PROGRAM_NAME);
                  return(1);
            };
            break;
         case 'q':
            cnf.silent = 1;
            break;
         case 'R':
            cnf.ldapSaslRealm = optarg;
            break;
         case 's':
            if (!(strcasecmp(optarg, "base")))
               cnf.ldapScope = LDAP_SCOPE_BASE;
            else if (!(strcasecmp(optarg, "one")))
               cnf.ldapScope = LDAP_SCOPE_ONE;
            else if (!(strcasecmp(optarg, "sub")))
               cnf.ldapScope = LDAP_SCOPE_SUB;
            else if (!(strcasecmp(optarg, "children")))
               cnf.ldapScope = LDAP_SCOPE_CHILDREN;
            else
            {
               fprintf(stderr, "%s: scope should be base, one, or sub\n", PROGRAM_NAME);
               fprintf(stderr, "Try `%s --help' for more information.\n", PROGRAM_NAME);
               return(1);
            };
            break;
         case 'U':
            cnf.ldapUseSasl      = 1;
            cnf.ldapSaslAuthUser = optarg;
            break;
         case 'V':
            ldapsearch_version();
            return(0);
         case 'v':
            cnf.verbose++;
            break;
         case 'w':
            cnf.ldapPassword = optarg;
            break;
         case 'Y':
            cnf.ldapSaslMech = optarg;
            break;
         case 'Z':
            cnf.ldapUseTls = 1;
            break;
         case 'z':
            cnf.ldapSearchLimit = strtol(optarg, NULL, 0);
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

   if ((optind+1) <= argc)
      cnf.ldapFilter = argv[optind];

   if ((ldapcommon_initialize(&cnf)))
      return(1);

   // add attributes to retrieve to a NULL terminated array
   if (!(attrs = malloc(sizeof(char *) * (argc - optind))))
   {
      fprintf(stderr, "%s: out of virtual memory\n", PROGRAM_NAME);
      return(1);
   };
   memset(attrs, 0, (sizeof(char *) * (argc - optind)));
   for(i = (optind+1); i < argc; i++)
      attrs[i-optind-1] = argv[i];

   // perform LDAP lookup
   if ((err = ldap_search_ext_s(cnf.ld, cnf.ldapBaseDN, cnf.ldapScope, cnf.ldapFilter, attrs, 0, NULL, NULL, NULL, -1, &res)))
   {
      fprintf(stderr, "ldap_search_ext_s(): %s\n", ldap_err2string(err));
      ldap_unbind_ext_s(cnf.ld, NULL, NULL);
      free(attrs);
      return(1);
   };

   // free array of attributes (no longer needed after the search)
   free(attrs);

   // verifies entries were found
   if (!(ldap_count_entries(cnf.ld, res)))
   {
      printf("# no entries found.\n");
      ldap_msgfree(res);
      ldap_unbind_ext_s(cnf.ld, NULL, NULL);
      return(0);
   };

   // retrieves the first entry
   if (!(entry = ldap_first_entry(cnf.ld, res)))
   {
      fprintf(stderr, "ldap_first_entry(): %s\n", ldap_err2string(err));
      ldap_msgfree(res);
      ldap_unbind_ext_s(cnf.ld, NULL, NULL);
      return(1);
   };

   // loops through remaining entries
   while(entry)
   {
      printf("dn: %s\n", ldap_get_dn(cnf.ld, entry));

      // retrieve first attribute
      attribute = ldap_first_attribute(cnf.ld, entry, &ber);

      // loops through remaining attributes and displays values
      while(attribute)
      {
         if ((vals = ldap_get_values_len(cnf.ld, entry, attribute)))
         {
            for(i = 0; vals[i]; i++)
               printf("%s: %s\n", attribute, vals[i]->bv_val);
            ldap_value_free_len(vals);
         };
         ldap_memfree(attribute);
         attribute = ldap_next_attribute(cnf.ld, entry, ber);
      };
      printf("\n");

      // skip to the next entry
      entry = ldap_next_entry(cnf.ld, entry);
   };

   // disconnects from LDAP and frees resources
   ldap_unbind_ext_s(cnf.ld, NULL, NULL);

   return(0);
}


/* end of source */
