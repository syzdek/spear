/*
 * Simple LDAP Load Tester Example v0.1
 * $Source$
 * $Revision$
 * $Date$
 * $Author$
 */
/*
 * ldapblaster.c - simple ldap load tester
 */
/*
 * Software used in development:
 *    Sun Solaris 5.9
 *    Linux 2.4.21
 *    OpenLDAP 2.1.17
 *    GCC 2.95.3
 */
/*
 * Related Links:
 *    http://www.openldap.org
 */
/*
 * Build:
 *    gcc -g -o ldapblaster.o ldapblaster.c -lldap -llber -lresolv
 */

/////////////
//         //
// Headers //
//         //
/////////////

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>


//////////////////
//              //
//  Prototypes  //
//              //
//////////////////

   int  main(void);
   int  spawn_child(int, int *);


////////////////
//            //
// Functions  //
//            //
////////////////


   /* Spawns Child Process */
   int spawn_child(int filter, int *status) {

      /* Declares Local Vars */
         int pid;

      /* Detaches from Process */
         pid = fork();
         switch (pid) {
            case -1:
               return(-1);

            case 0:
               close (STDIN_FILENO);
               close (STDOUT_FILENO);
               close (STDERR_FILENO);
               if (setsid () == -1) {
                  syslog(LOG_NOTICE, "setsid(): %s", strerror(errno));
                  return(-1);
               };
               break;

            default:
               return(pid);
         };

      /* Test LDAP */
         *status = filter;
         return(0);
   }


///////////////////
//               //
// Main Function //
//               //
///////////////////
int main(void) {
                           
   /* Declares Local Vars */
      time_t timestamp;
      int status;
      int pid;

   /* Gets Timestamp */
      //timestamp = time(NULL);
      timestamp = 256;

   /* Spawns Child */
      pid = spawn_child(timestamp, &status);
      if (pid < 0) {
         return(1);
        } else if (pid == 0) {
         return(status);
      };

   /* Gets Child */
      sleep(1);
      pid = waitpid(pid, &status, WUNTRACED);
      if (pid != 0) {
         if (WIFEXITED(status)) {
            status = WEXITSTATUS(status);
            printf("Timestamp: %i\n", status);
           } else {
            printf("Still running");
         }; 
        } else {
         printf("No such process");
      };

   /* Ends function */
      return(0);

}
