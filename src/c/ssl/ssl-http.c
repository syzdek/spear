/*
 * Simple https example
 * $Source$
 * $Revision$
 * $Date$
 * $Author$
 */
/*
 * ssl-http.c - simple https example
 */
/*
 * Build:
 *    gcc -g -o ssl-http.o ssl-http.c 
 */

/////////////
//         //
// Headers //
//         //
/////////////

#include <openssl/err.h>	/*  ssh error messages      */
#include <openssl/ssl.h>	/*  ssh libs                */
#include <stdio.h>		/*  Input output functions  */


//////////////////
//              //
//  Prototypes  //
//              //
//////////////////

   int main(int, char **);

///////////////////
//               //
// Main Function //
//               //
///////////////////

int main(int argc, char **argv) {

   /* Declares local vars */
      DIR *root;
      struct dirent *subdir;

   /* Checks for Arguments */
      if ((int) argc < 2) {
         fprintf (stderr, "Usage: %s <directory>\n", argv[0]);
         return(1);
      };

   /* Stats file */
      if (chroot(argv[1])) {
         perror("chroot()");
         return(1);
      };

   /* Lists directory */
      root = opendir("/");
      if (root == NULL) {
         perror("opendir()");
         return(1);
      };
      subdir = readdir(root);
      while(subdir != NULL) {
         printf("%s\n", subdir->d_name);
         subdir = readdir(root);
      };
      closedir(root);
      

   /* Frees Memory, Unbinds, and exits */
      return(0);

}
