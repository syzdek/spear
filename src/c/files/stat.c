/*
 * Simple stat() example
 * $Source$
 * $Revision$
 * $Date$
 * $Author$
 */
/*
 * stat.c - simple stat() example
 */
/*
 * Build:
 *    gcc -g -o stat.o stat.c 
 */

/////////////
//         //
// Headers //
//         //
/////////////

   #include <errno.h>
   #include <stdio.h>
   #include <stdlib.h>
   #include <sys/types.h>
   #include <sys/stat.h>
   #include <unistd.h>


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
      struct stat myfile;

   /* Checks for Arguments */
      if ((int) argc < 2) {
         fprintf (stderr, "Usage: %s <file>\n", argv[0]);
         return(1);
      };

   /* Stats file */
      if (stat(argv[1], &myfile) < 0) {
         perror("stat()");
         return(1);
      };

   /* Prints stat */
      printf("Device:\t%i\n", myfile.st_nlink);

   /* Frees Memory, Unbinds, and exits */
      return(0);

}
