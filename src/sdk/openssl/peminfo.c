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
 *  @file src/sdk/openssl/peminfo.c simple hash utility for sha1
 */
/*
 *  Simple Build:
 *     gcc -W -Wall -O2 -c peminfo.c
 *     gcc -W -Wall -O2 -lcrypto -o peminfo peminfo.o
 *
 *  GNU Libtool Build:
 *     libtool --mode=compile gcc -W -Wall -g -O2 -c peminfo.c
 *     libtool --mode=link    gcc -W -Wall -g -O2 -o peminfo peminfo.lo
 *
 *  GNU Libtool Install:
 *     libtool --mode=install install -c peminfo /usr/local/bin/peminfo
 *
 *  GNU Libtool Clean:
 *     libtool --mode=clean rm -f peminfo.lo peminfo
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
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/x509.h>
#include <openssl/bio.h>


//////////////////
//              //
//  Prototypes  //
//              //
//////////////////
#pragma mark - Prototypes

// main statement
int main(int argc, char * argv[]);


/////////////////
//             //
//  Functions  //
//             //
/////////////////
#pragma mark - Functions

/// main statement
/// @param[in]  argc  number of arguments passed to program
/// @param[in]  argv  array of arguments passed to program
int main(int argc, char * argv[])
{
   struct stat           sb;
   unsigned char       * buff;
   int                   fd;
   ssize_t               len;
   BIO                 * bio;
   X509                * x;
   unsigned              err;
   int                   pos;
   char                  errmsg[1024];
   const EVP_MD        * digest;
   unsigned char         md[EVP_MAX_MD_SIZE];
   unsigned int          n;

   // checks arguments
   if (argc != 2)
   {
      fprintf(stderr, "Usage: peminfo <pemfile>\n");
      return(1);
   };

   // checks file
   if ((stat(argv[1], &sb)) == -1)
   {
      perror("peminfo: stat()");
      return(1);
   };
   len = (sb.st_size * 2);

   // allocates memory
   if (!(buff = malloc(len)))
   {
      fprintf(stderr, "peminfo: out of virtual memory\n");
      return(1);
   };

   // opens file for reading
   if ((fd = open(argv[1], O_RDONLY)) == -1)
   {
      perror("peminfo: open()");
      free(buff);
      return(1);
   };

   // reads file
   if ((len = read(fd, buff, len)) == -1)
   {
      perror("peminfo: read()");
      free(buff);
      return(1);
   };

   // closes file
   close(fd);

   // initialize OpenSSL
   SSL_load_error_strings();
   SSL_library_init();

   // creates BIO buffer
   bio = BIO_new_mem_buf(buff, len);

   // decodes buffer
   if (!(x = PEM_read_bio_X509(bio, NULL, 0L, NULL)))
   {
      while((err = ERR_get_error()))
      {
         errmsg[1023] = '\0';
         ERR_error_string_n(err, errmsg, 1023);
         fprintf(stderr, "peminfo: %s\n", errmsg);
      };
      BIO_free(bio);
      free(buff);
      return(1);
   };

   // prints x509 info
   printf("name:      %s\n",    x->name);
   printf("serial:    ");
   printf("%02X", x->cert_info->serialNumber->data[0]);
   for(pos = 1; pos < x->cert_info->serialNumber->length; pos++)
      printf(":%02X", x->cert_info->serialNumber->data[pos]);
   printf("\n");

   // calculate & print fingerprint
   digest = EVP_get_digestbyname("sha1");
   X509_digest(x, digest, md, &n);
   printf("Fingerprint: ");
   for(pos = 0; pos < 19; pos++)
      printf("%02x:", md[pos]);
   printf("%02x\n", md[19]);

   // frees memory
   BIO_free(bio);
   free(buff);

   return(0);
}


/* end of source */
