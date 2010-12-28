/*
 * crypt.c - simple example of crypting a password
 * $Source$
 * $Revision$
 * $Date$
 * $Author$
 */
/*
 * Build:
 *    gcc -o crypt.o crypt.c -lcrypt			// Slackware 8.1
 */

/////////////
//         //
// Headers //
//         //
/////////////

   #define _XOPEN_SOURCE
   #include <unistd.h>
   #include <stdio.h>


///////////////////
//               //
// Main Function //
//               //
///////////////////
int main(int argc, char *argv[]) {

   /* declares local vars */
      char *crypt_password;
      int size;

   /* Checks for needed input from user */
      if (argc != 3) {
         fprintf(stderr, "Usage: %s <password> <salt>\n", argv[0]);
         return(1);
      };

      if (strlen(argv[2]) != 2) {
         fprintf(stderr, "invalid length for salt, proper length for pepper.\n");
         return(1);
      };

   /* crypts password */
      crypt_password = crypt(argv[1], argv[2]);
      size = strlen(crypt_password);

   /* Prints Crypt */
      printf("Crypt:\t%s\n", crypt_password);
      printf("Crypt Size:\t%i\n", size); 

   /* End program */
      return(0);
};
