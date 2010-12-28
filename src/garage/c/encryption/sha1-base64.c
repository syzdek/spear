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
/*
 * Notes:
 *    Does not make a true base64 encoding, however it's working well
 *    enough to hash uniq data such as PID, Epoch, Client IP, and random
 *    numbers to create a 41 byte session ID.
 */

/////////////
//         //
// Headers //
//         //
/////////////

   #include <openssl/sha.h>
   #include <stdlib.h>
   #include <stdio.h>

 	
///////////////////
//               //
// Main Function //
//               //
///////////////////
int main(int argc, char *argv[]) {

   /* Declare local vars */
      char *md;
      char pos;
      char ascii_encode[43];
      int bin_data;

   /* Gets user input */
      if (argc != 2) {
         fprintf(stderr, "Usage: %s <password>\n", argv[0]);
         return(1);
      };

   /* Encrypts password */
      SHA1(argv[1], strlen(argv[1]), md);

   /* encodes sha1 in base64 */
      memset(ascii_encode, 0, 43);
      for(pos = 0; pos < 8; pos++) {
         if (md[pos*4] == 0) 
            md[pos*4] = 1;
         memcpy(&bin_data, md+(pos*4), 4);
         memcpy(&ascii_encode[pos*6], l64a(htonl(bin_data)), 6);
      };
      ascii_encode[42] = '\0';
      for(pos = 0; pos < 41; pos++)
         if (ascii_encode[pos] == 0)
            ascii_encode[pos] = '0';

   /* Displays results */
      printf("Sha1:\t%s\n", ascii_encode);
      printf("Sha1 Size:\t%i\n", strlen(ascii_encode));

   /* Ends program */
      return(0);
};
