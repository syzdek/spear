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
 *  @file src/sdk/openssl/sha1hash.c simple hash utility for sha1
 */
/*
 *  Simple Build:
 *     gcc -W -Wall -O2 -c sha1hash.c
 *     gcc -W -Wall -O2 -lcrypto -o sha1hash sha1hash.o
 *
 *  GNU Libtool Build:
 *     libtool --mode=compile gcc -W -Wall -g -O2 -c sha1hash.c
 *     libtool --mode=link    gcc -W -Wall -g -O2 -o sha1hash sha1hash.lo
 *
 *  GNU Libtool Install:
 *     libtool --mode=install install -c sha1hash /usr/local/bin/sha1hash
 *
 *  GNU Libtool Clean:
 *     libtool --mode=clean rm -f sha1hash.lo sha1hash
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
#include <openssl/sha.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <fcntl.h>
#include <unistd.h>


///////////////////
//               //
//  Definitions  //
//               //
///////////////////
#pragma mark -
#pragma mark Definitions & Macros

#undef PROGRAM_NAME
#define PROGRAM_NAME "sha1hash"

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
void sha1hash_usage(void);

// displays version information
void sha1hash_version(void);

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
void sha1hash_usage(void)
{
   printf(("Usage: %s [OPTIONS] file\n"
         "  -h, --help                print this help and exit\n"
         "  -q, --quiet, --silent     do not print messages\n"
         "  -V, --version             print version number and exit\n"
         "  -v, --verbose             print verbose messages\n"
         "\n"
         "Report bugs to <%s>.\n"
      ), PROGRAM_NAME, PACKAGE_BUGREPORT
   );
   return;
}


/// displays version information
void sha1hash_version(void)
{
   printf(("%s (%s) %s\n"
         "Written by David M. Syzdek.\n"
         "\n"
         "Copyright 2011 David M. Syzdek <david@syzdek.net>.\n"
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
   int           x;
   int           y;
   int           fd;
   int           quiet;
   int           verbose;
   int           opt_index;
   char          data[512];
   ssize_t       data_len;
   SHA_CTX       sha1;
   unsigned char buff[SHA_DIGEST_LENGTH];

   static char   short_opt[] = "hqVv";
   static struct option long_opt[] =
   {
      {"help",          no_argument, 0, 'h'},
      {"silent",        no_argument, 0, 'q'},
      {"quiet",         no_argument, 0, 'q'},
      {"verbose",       no_argument, 0, 'v'},
      {"version",       no_argument, 0, 'V'},
      {NULL,            0,           0, 0  }
   };

   quiet   = 0;
   verbose = 0;

   while((c = getopt_long(argc, argv, short_opt, long_opt, &opt_index)) != -1)
   {
      switch(c)
      {
         case -1:	/* no more arguments */
         case 0:	/* long options toggles */
            break;
         case 'h':
            sha1hash_usage();
            return(0);
         case 'q':
            quiet++;
            break;
         case 'V':
            sha1hash_version();
            return(0);
         case 'v':
            verbose++;
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

   if (optind >= argc)
   {
      fprintf(stderr, "%s: missing required argument\n", PROGRAM_NAME);
      fprintf(stderr, "Try `%s --help' for more information.\n", PROGRAM_NAME);
      return(1);
   };

   for(x = optind; x < argc; x++)
   {
      if (verbose) printf("opening \"%s\"...\n", argv[x]);
      if ((fd = open(argv[x], O_RDONLY)) == -1)
      {
         if (!(quiet))
            perror("open()");
         return(1);
      };

      if (verbose) printf("generating hash for \"%s\"...\n", argv[x]);
      SHA1_Init(&sha1);
printf("sizeof(sha1) == %lu\n", sizeof(sha1));
      while((data_len = read(fd, data, 512)) > 0)
         SHA1_Update(&sha1, data, data_len);
      if (data_len == -1)
      {
         if (!(quiet))
            perror("open()");
         return(1);
      };
      
      SHA1_Final(buff, &sha1);

      if (verbose) printf("displaying hash for \"%s\"...\n", argv[x]);
      for(y = 0; y < SHA_DIGEST_LENGTH; y++)
         printf("%02x", buff[y]);
      printf("  %s\n", argv[x]);

      if (verbose) printf("closing \"%s\"...\n", argv[x]);
      close(fd);
   };

   return(0);
}


/* end of source */
