/*
 * sha1.c - simple example of crypting a password with sha1
 * $Source$
 * $Revision$
 * $Date$
 * $Author$
 */
/*
 * Build:
 *    gcc -o sha1.o sha1.c -lssl		// Slackware 8.1
 */

/////////////
//         //
// Headers //
//         //
/////////////

   #include <openssl/sha.h>
   #include <stdio.h>


///////////////////
//               //
// Main Function //
//               //
///////////////////
int main(int argc, char *argv[]) {

   /* Declare local vars */
      unsigned char *md;
      unsigned short int pos;

   /* Gets user input */
      if (argc != 2) {
         fprintf(stderr, "Usage: %s <password>\n", argv[0]);
         return(1);
      };

   /* Encrypts password */
      SHA1(argv[1], strlen(argv[1]), md);

   /* Displays results */
      printf("Sha:");
      for(pos = 0; pos < strlen(md); pos++) {
         if ( (pos % 4) == 0 ) 
            printf("\n\t");
         printf("%i\t", md[pos]);
      };
      printf("\n\nSha Size:\t%i\n", strlen(md));

   return(0);
};
