/*
 * Simple setuid() example
 * $Source$
 * $Revision$
 * $Date$
 * $Author$
 */
/*
 * setuid.c - simple setuid() example
 */
/*
 * Build:
 *    gcc -g -o setuid.o setuid.c 
 */

/////////////
//         //
// Headers //
//         //
/////////////

   #include <errno.h>
   #include <pwd.h>
   #include <stdio.h>
   #include <sys/types.h>
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
      struct passwd *my_user;

   /* Checks for Arguments */
      if ((int) argc < 2) {
         fprintf (stderr, "Usage: %s <uid>\n", argv[0]);
         return(1);
      };

   /* Looks up the user */
      my_user = getpwnam(argv[1]);
      if (my_user == NULL) {
         perror("getpwnam()");
         return(1);
      };

   /* Prints some intresting info */
      printf("User:\t%s\n", my_user->pw_name);
      printf("UID:\t%i\n", my_user->pw_uid);
      printf("GID:\t%i\n", my_user->pw_gid);
      printf("Gecos:\t%s\n", my_user->pw_gecos);
      printf("Home:\t%s\n", my_user->pw_dir);
      printf("Shell:\t%s\n", my_user->pw_shell);

   /* Changes UID */
      printf("\nChanging to uid %i\n", my_user->pw_uid);
      if (setuid(my_user->pw_uid)) {
         perror("setuid()");
         return(1);
      };

   /* Sleeps for 20 seconds */
      sleep(20);

   /* exits */
      return(0);

}
