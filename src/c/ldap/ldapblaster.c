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
#include <ldap.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <sys/time.h>		/* for struct timeval definition */
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include "ldapblaster.h"


//////////////////
//              //
//  Data Types  //
//              //
//////////////////

   struct childpids {
      int pid;
      time_t timestamp;
      struct childpids *previous;
      struct childpids *next;    
   };


//////////////////
//              //
//  Prototypes  //
//              //
//////////////////

   unsigned int  child_cleanup(struct childpids *, time_t);
   int  child_ldap(int);
   void child_nobind(int);
   void child_noresults(int);
   void child_shutdown(int);
   void child_stats(int);
   void child_successes(int);
   int  division(int, int, int);
   int  main(void);
   void parent_null(int);
   void parent_shutdown(int);
   void parent_stats(int);
   void signal_init_parent();
   int  spawn_child(int, int *);
   void stats(void);


///////////////////
//               //
//  Definitions  //
//               //
///////////////////

/* Boolen Expressions */
#define FALSE	0
#define TRUE	1

/* Run time options */
#define MAX_CHILDREN	200
#define MAX_RUNS	100000
#define MAX_RUN_TIME	600
#define CHILD_TIMEOUT	10
#define UPDATE_FREQ	10

/* LDAP configurations */
#define MY_LDAP_HOST	"ldaps.prv.nwc.acsalaska.net"
#define MY_LDAP_PORT	13891
#define MY_LDAP_BASEDN	"o=acsalaska.net"
#define MY_LDAP_SCOPE	"sub"
#define MY_LDAP_ATTRS	"mail"
#define MY_LDAP_TIMEOUT	2

/* Auth Info */
#define MY_BIND_DN		"cn=Directory Manager"
#define MY_BIND_PW		"Lwsu@@ps"


///////////////////
//               //
//  Signal Vars  //
//               //
///////////////////

   /* Term Signals */
      volatile sig_atomic_t ldapblaster_exit = FALSE;

   /* Program Stats */
      volatile int ldapblaster_children = 0;
      volatile int ldapblaster_spawned = 0;
      volatile int ldapblaster_sincelast = 0;
      volatile time_t ldapblaster_timestamp = 0;

   /* LDAP Stats */
      volatile int ldapblaster_noconn = 0;
      volatile int ldapblaster_nobind = 0;
      volatile int ldapblaster_noentries = 0;
      volatile int ldapblaster_noresults = 0;
      volatile int ldapblaster_nosearch = 0;
      volatile int ldapblaster_successes = 0;
      volatile int ldapblaster_unknown = 0;


////////////////
//            //
// Functions  //
//            //
////////////////


   unsigned int child_cleanup(struct childpids pids[], time_t timestamp) {

      /* Declares local vars */
         pid_t pid = 0;
         int status = 0;
         int pidcount = 0;

      /* Loops through */
         for(pidcount = 0; pidcount < MAX_CHILDREN; pidcount++) {
            if (pids[pidcount].pid > 0) {
               pid = waitpid(pids[pidcount].pid, &status, WNOHANG | WUNTRACED);
               if (pid != 0) {
                  if (WIFEXITED(status)) {
                     ldapblaster_children--;
                     status = WEXITSTATUS(status);
                     if (status == 0) {
                        ldapblaster_successes++;
                       } else if (status == 1) {
                        ldapblaster_noconn++;
                       } else if (status == 2) {
                        ldapblaster_nobind++;
                       } else if (status == 3) {
                        ldapblaster_nosearch++;
                       } else if (status == 4) {
                        ldapblaster_noentries++;
                       } else if (status == 4) {
                        ldapblaster_noresults++;
                       } else {
                        ldapblaster_unknown++;
                     };
                     pids[pidcount].pid = 0;
                    } else {
                     if ((pids[pidcount].timestamp + CHILD_TIMEOUT) >= timestamp) {
                        kill(pids[pidcount].pid, SIGTERM);
                       } else if ((pids[pidcount].timestamp + (CHILD_TIMEOUT * 2)) >= timestamp) {
                        kill(pids[pidcount].pid, SIGKILL);
                     };
                  };
               };
            };
         };

      /* Ends Function */
         return(0);

   }



   int child_ldap(int filter) {

      /*
       * Exit Codes
       *   -1 - Internal Error to function
       *    0 - Success
       *    1 - Could make a tcp connection
       *    2 - Could not Bind
       *    3 - Search failed
       *    4 - No entries were returned
       *    5 - No Values were returned
       *  143 - Child was killed by kill() 
       */

      /* Declares Local Vars */
         LDAP *ldap;
         LDAPMessage *mesg, *entry;
         BerElement *ber;
         char *a;
         char **vals;
         struct timeval timeout;

      /* Starts LDAP Connection */
         if ( (ldap = ldap_init(MY_LDAP_HOST, MY_LDAP_PORT)) == NULL)
            return(1);

      /* Binds to LDAP server */
         if (ldap_simple_bind_s(ldap, MY_BIND_DN, MY_BIND_PW) != LDAP_SUCCESS) {
            ldap_unbind(ldap);
            return(2);
         };

      /* Makes Timeout */
         memset(&timeout, 0, sizeof(struct timeval));
         timeout.tv_sec = MY_LDAP_TIMEOUT;

      /* Searches LDAP */
         if (ldap_search_st(ldap, MY_LDAP_BASEDN, LDAP_SCOPE_SUBTREE, filters[filter], NULL, 0, &timeout, &mesg) != LDAP_SUCCESS ) {
            ldap_unbind(ldap);
            return(3);
         };

      /* retrieves data */
         if (ldap_first_entry(ldap, mesg) == NULL) {
            ldap_msgfree(mesg);
            ldap_unbind(ldap);
            return(4);
         };
         for (entry = ldap_first_entry(ldap, mesg); entry != NULL; entry = ldap_next_entry(ldap, entry)) {
            a = ldap_first_attribute(ldap, entry, &ber);
            if (a == NULL) {
               ldap_memfree( a );
               if ( ber != NULL )
                  ber_free( ber, 0 );
               ldap_msgfree(mesg);
               ldap_unbind(ldap);
               return(4);
            };
            for (a = ldap_first_attribute(ldap, entry, &ber); a != NULL; a = ldap_next_attribute(ldap, entry, ber)) {
               if ((vals = ldap_get_values(ldap, entry, a)) != NULL ) {
                  ldap_value_free( vals );
               };
               ldap_memfree( a );
            };
            if ( ber != NULL )
               ber_free( ber, 0 );
         };
         ldap_msgfree(mesg);

      /* Disconnects from LDAP and Sends Success Sig */
         ldap_unbind(ldap);

      /* Ends Function */
         return(0);
   }


   /* Performs Division */


   /* Catches Sig and ignores it */
   void parent_null(int sig) {
      signal(sig, parent_null);
   }


   /* Catches Sig for shutdown */
   void parent_shutdown(int sig) {
      ldapblaster_exit = TRUE;
      signal(SIGALRM, parent_null);
      signal(sig, parent_shutdown);
   }


   /* Catches Sig for Stats */
   void parent_stats(int sig) {
      signal(sig, parent_stats);
      alarm(UPDATE_FREQ);
      stats();
   }



   /* Starts Parent Signal Handling */
   void signal_init_parent() {
      ldapblaster_exit = FALSE;
      signal(SIGALRM, parent_stats);
      signal(SIGHUP, parent_shutdown);
      signal(SIGINT, parent_shutdown);
      signal(SIGTERM, parent_shutdown);
   }


   /* Displays Stats */
   void stats(void) {

      /* Declares Local vars */
         time_t timestamp = time(NULL);
         int noconnects = ldapblaster_noconn;
         int nobind = ldapblaster_nobind;
         int noentries = ldapblaster_noentries;
         int nosearch = ldapblaster_nosearch;
         int noresults = ldapblaster_noresults;
         int unknowns = ldapblaster_unknown;
         int successes = ldapblaster_successes;
         int children = ldapblaster_children;
         int spawned = ldapblaster_spawned;
         int runtime = (int) (timestamp - ldapblaster_timestamp);
         int sincelast = spawned - ldapblaster_sincelast;
         int failed, success;

      /* Resets last count */
         ldapblaster_sincelast = spawned;

      /* Computes total of Successes and Failures */
         failed = noconnects + nobind + noentries + nosearch + noresults + unknowns;
         if (failed == 0)
            failed = 1;
         success = successes;
         if (success == 0)
            success = 1;

      /* Prints Counts */
         printf("Stats:\n");
         printf("   Failed Connects:    %i\n", noconnects);
         printf("   Failed Binds:       %i\n", nobind);
         printf("   Failed Searches:    %i\n", nosearch);
         printf("   Failed Entries:     %i\n", noentries);
         printf("   Failed Results:     %i\n", noresults);
         printf("   Unknown failures:   %i\n", unknowns);
         printf("   Successfull:        %i\n", successes);

      /* Per second stats */
         printf("\n");
         printf("   Successes/Second:   %i\n", (success/runtime));
         printf("   Failures/Second:    %i\n", (failed/runtime));
         printf("   Queries/Second:     %i\n", (spawned/runtime));

      /* Computes Ratios */
         printf("   Success / Failures: ");
         if (failed < success) {
            if (failed == 0) {
               printf("%i/0\n", success);
              } else {
               printf("%i.", (success/failed));
               success %= failed;
               success *= 10;
               printf("%i/1\n", (success/failed));
            };
           } else if (failed > success) {
            if (success == 0) {
               printf("0/%i\n", failed);
              } else {
               printf("1/%i.", (failed/success));
               failed %= success;
               failed *= 10;
               printf("%i\n", (failed/success));
            };
           } else {
            printf("1/1\n");
         };

      /* Print App stats */
         printf("\n");
         printf("   Current Children:   %i\n", children);
         printf("   Spawned Last Time:  %i\n", sincelast);
         printf("   Total Spawned:      %i\n", spawned);
         printf("   Run Time:           %i\n", runtime);
         printf("\n\n");
   }


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
                  return(1);
               };
               *status = child_ldap(filter);
               return(0);
               break;

            default:
               return(pid);
         };

      /* Test LDAP */
         return(0);
   }


///////////////////
//               //
// Main Function //
//               //
///////////////////
int main(void) {
                           
   /* Declares Local Vars */
      struct childpids pids[MAX_CHILDREN];
      time_t timestamp;
      int filtercount = 0;
      int pid = 0;
      int pidcount = 0;
      int status = 0;

      for (pidcount = 0; pidcount < MAX_CHILDREN; pidcount++)
         memset(&pids[pidcount], 0, sizeof(struct childpids));

      alarm(UPDATE_FREQ);
      ldapblaster_timestamp = time(NULL);
      timestamp = ldapblaster_timestamp;
      signal_init_parent();

      while (ldapblaster_exit == FALSE) {
         for(pidcount = 0; pidcount < MAX_CHILDREN; pidcount++) {
            if (pids[pidcount].pid == 0) {
               pid = spawn_child(filtercount, &status);
               if (pid < 0)
                  return(-1);
               if (pid == 0)
                  return(status);
               pids[pidcount].pid = pid;
               pids[pidcount].timestamp = timestamp;
               filtercount++;
               if (filtercount > 114)
                  filtercount = 0;
               ldapblaster_children++;
               ldapblaster_spawned++;
               if (ldapblaster_spawned >= MAX_RUNS) {
                  signal(SIGALRM, parent_null);
                  printf("Spawned max number of children\n");
                  pidcount = MAX_CHILDREN;
                  ldapblaster_exit = TRUE;
               };
            };
            
         };
         child_cleanup(pids, timestamp);
         timestamp = time(NULL);
         if (timestamp >= (ldapblaster_timestamp + MAX_RUN_TIME)) {
            signal(SIGALRM, parent_null);
            printf("Reached max run time\n");
            ldapblaster_exit = TRUE;
         };
      };
  
      signal(SIGALRM, parent_null);
      setvbuf(stdout, NULL, _IONBF, 0);
      printf("\nWaiting for our children to exit\n");
      printf("|");
      for (filtercount = 0; filtercount < (CHILD_TIMEOUT *2); filtercount++)
         printf("-");
      printf("|\n|");
      for (filtercount = 0; filtercount < (CHILD_TIMEOUT *2); filtercount++) {
         if (ldapblaster_children > 0) {
            sleep(1);
            child_cleanup(pids, time(NULL));
         };
         printf(".");
      };
      printf("|\n\n\n");
      stats();
      return(0);
      

}
