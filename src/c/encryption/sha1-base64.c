/*
 * sha1-base64.c - simple example of crypting a password with sha1 in ascii output
 * $Source$
 * $Revision$
 * $Date$
 * $Author$
 */
/*
 * Build:
 *    gcc -o sha1-base64.o sha1-base64.c -lssl		// Slackware 8.1
 */

/////////////
//         //
// Headers //
//         //
/////////////

   #include <openssl/sha.h>
   #include <stdlib.h>
   #include <stdio.h>

 	
char *
encode (const void *buf, size_t len)
{
  /* We know in advance how long the buffer has to be. */
  unsigned char *in = (unsigned char *) buf;
  char *out = malloc (6 + ((len + 3) / 4) * 6 + 1);
  char *cp = out;

  /* Encode the length. */
  /* Using `htonl' is necessary so that the data can be
     decoded even on machines with different byte order. */

  cp = mempcpy (cp, l64a (htonl (len)), 6);

  while (len > 3)
    {
      unsigned long int n = *in++;
      n = (n << 8) | *in++;
      n = (n << 8) | *in++;
      n = (n << 8) | *in++;
      len -= 4;
      if (n)
        cp = mempcpy (cp, l64a (htonl (n)), 6);
      else
            /* `l64a' returns the empty string for n==0, so we 
               must generate its encoding ("......") by hand. */
        cp = stpcpy (cp, "......");
    }
  if (len > 0)
    {
      unsigned long int n = *in++;
      if (--len > 0)
        {
          n = (n << 8) | *in++;
          if (--len > 0)
            n = (n << 8) | *in;
        }
      memcpy (cp, l64a (htonl (n)), 6);
      cp += 6;
    }
  *cp = '\0';
  return out;
}

///////////////////
//               //
// Main Function //
//               //
///////////////////
int main(int argc, char *argv[]) {

   /* Declare local vars */
      unsigned char *md;
      unsigned short int pos;
      char *output;

   /* Gets user input */
      if (argc != 2) {
         fprintf(stderr, "Usage: %s <password>\n", argv[0]);
         return(1);
      };

   /* Encrypts password */
      SHA1(argv[1], strlen(argv[1]), md);

   /* base64 encode the sha1 data */
      output = encode(md, (sizeof(char *) * strlen(md)) );

   /* Displays results */
      printf("Sha:\t%s\n", output);
      printf("Sha Size:\t%i\n", strlen(md));

   return(0);
};
