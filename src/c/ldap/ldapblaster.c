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

   unsigned int  child_cleanup(struct childpids *);
   int  child_ldap(int);
   void child_nobind(int);
   void child_noresults(int);
   void child_shutdown(int);
   void child_stats(int);
   void child_successes(int);
   int  main(void);
   void parent_nobind(int);
   void parent_noresults(int);
   void parent_null(int);
   void parent_shutdown(int);
   void parent_stats(int);
   void parent_successes(int);
   void signal_init_parent();
   int  spawn_child(int);
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
#define MAX_CHILDREN	5
#define MAX_RUNS	25000
#define MAX_RUN_TIME	300
#define CHILD_TIMEOUT	10
#define UPDATE_FREQ	5

/* LDAP configurations */
#define MY_LDAP_HOST	"ldap007.prv.nwc.acsalaska.net"
#define MY_LDAP_PORT	13891
#define MY_LDAP_BASEDN	"o=acsalaska.net"
#define MY_LDAP_SCOPE	"sub"
#define MY_LDAP_ATTRS	"mail"
#define MY_LDAP_TIMEOUT	15

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
      volatile int ldapblaster_memslots = 0;
      volatile time_t ldapblaster_timestamp = 0;

   /* LDAP Stats */
      volatile int ldapblaster_noconn = 0;
      volatile int ldapblaster_nobind = 0;
      volatile int ldapblaster_noresults = 0;
      volatile int ldapblaster_successes = 0;


////////////////
//            //
// Functions  //
//            //
////////////////


   unsigned int child_cleanup(struct childpids *last_child) {

      /* Declares local vars */
         struct childpids *tmp_child;
         pid_t pid;
         int status;

      /* Checks for Terminated Children */
         while (last_child->previous != NULL) {
            pid = waitpid(last_child->pid, &status, WNOHANG | WUNTRACED);
            if ((WIFEXITED(status)) && (pid != 0)) {
               ldapblaster_children--;
               status = WEXITSTATUS(status);
               if (status == 0) {
                  ldapblaster_successes++;
                 } else if (status == 1) {
                  ldapblaster_noconn++;
                 } else if (status == 2) {
                  ldapblaster_nobind++;
                 } else if (status == 3) {
                  ldapblaster_noresults++;
               };
               if (last_child->next == NULL) {
                  last_child = last_child->previous;
                  free(last_child->next);
                  last_child->next = NULL;
                 } else {
                  last_child->previous->next = last_child->next;
                  last_child->next->previous = last_child->previous;
                  tmp_child = last_child;
                  last_child = last_child->previous;
                  free(tmp_child);
               };
            };
         };
         pid = waitpid(last_child->pid, &status, WNOHANG | WUNTRACED);
         if ((WIFEXITED(status)) && (pid != 0)) {
            ldapblaster_children--;
            status = WEXITSTATUS(status);
            if (status == 0) {
               ldapblaster_successes++;
              } else if (status == 1) {
               ldapblaster_noconn++;
              } else if (status == 2) {
               ldapblaster_nobind++;
              } else if (status == 3) {
               ldapblaster_noresults++;
            };
            if (last_child->next == NULL) {
               free(last_child);
               last_child = NULL;
              } else {
               last_child = last_child->next;
               free(last_child->previous);
               last_child->previous = NULL;
            };
         };
                
         
      /* Ends function */
         return((unsigned int) last_child);

   }



   int child_ldap(int filter) {

      /* Declares Local Vars */
         LDAP *ldap;
         LDAPMessage *mesg, *entry;
         BerElement *ber;
         char *a;
         char **vals;
         struct timeval timeout;

      /* Starts LDAP Connection */
         if ( (ldap = ldap_init(MY_LDAP_HOST, MY_LDAP_PORT)) == NULL) {
            //kill(getppid(), SIGUSR1);
            return(1);
         };

      /* Binds to LDAP server */
         if (ldap_simple_bind_s(ldap, MY_BIND_DN, MY_BIND_PW) != LDAP_SUCCESS) {
            ldap_unbind(ldap);
            //kill(getppid(), SIGUSR2);
            return(2);
         };

      /* Makes Timeout */
         memset(&timeout, 0, sizeof(struct timeval));
         timeout.tv_sec = MY_LDAP_TIMEOUT;

      /* Searches LDAP */
         if (ldap_search_st(ldap, MY_LDAP_BASEDN, LDAP_SCOPE_SUBTREE, filters[filter], NULL, 0, &timeout, &mesg) != LDAP_SUCCESS ) {
            ldap_unbind(ldap);
            //kill(getppid(), SIGUSR2);
            return(3);
         };

      /* retrieves data */
         for (entry = ldap_first_entry(ldap, mesg); entry != NULL; entry = ldap_next_entry(ldap, entry)) {
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
         //kill(getppid(), SIGWINCH);

      /* Ends Function */
         return(0);
   }


   /* Catches Sig for failed no bind */
   void parent_nobind(int sig) {
      ldapblaster_children--;
      ldapblaster_nobind++;
      signal(sig, parent_nobind);
   }


   /* Catches Sig for failed no result */
   void parent_noresults(int sig) {
      signal(sig, parent_noresults);
      ldapblaster_children--;    
      ldapblaster_noresults++;
   }

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


   /* Catches Sig for successes */
   void parent_successes(int sig) {
      ldapblaster_children--;
      ldapblaster_successes++;
      signal(sig, parent_successes);
   }
         

   /* Starts Parent Signal Handling */
   void signal_init_parent() {
      ldapblaster_exit = FALSE;
      signal(SIGALRM, parent_stats);
      signal(SIGHUP, parent_shutdown);
      signal(SIGINT, parent_shutdown);
      signal(SIGTERM, parent_shutdown);
      //signal(SIGUSR1, parent_nobind);
      //signal(SIGUSR2, parent_noresults);
      //signal(SIGWINCH, parent_successes);
      signal(SIGQUIT, parent_stats);
   }


   /* Catches Sig for Stats */
   void stats(void) {
      int failed, success;
      printf("Stats:\n");
      printf("   Failed Connects: %i\n", ldapblaster_nobind);
      printf("   Failed Searches: %i\n", ldapblaster_noresults);
      printf("   Successfull:     %i\n", ldapblaster_successes);
      failed = ldapblaster_nobind + ldapblaster_noresults;
      if (failed == 0)
         failed = 1;
      success = ldapblaster_successes;
      if (success == 0)
         success = 1;
      if (failed < success) {
         printf("   Ratio:           %i.", (success/failed));
         success %= failed;
         success *= 10;
         printf("%i success to 1 failure\n", (success/failed));
        } else {
         printf("   Ratio:           %i.", (failed/success));
         failed %= success;
         failed *= 10;
         printf("%i failures to 1 success\n", (failed/success));
      };
      printf("   Current Children: %i\n", ldapblaster_children);
      printf("   Total Spawned:    %i\n", ldapblaster_spawned);
      printf("   Memory Slots:     %i\n", ldapblaster_memslots);
      printf("   Run Time:         %i\n\n", (int) (time(NULL) - ldapblaster_timestamp));
   }


   /* Spawns Child Process */
   int spawn_child(int filter) {

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
               break;

            default:
               return(pid);
         };

      /* Test LDAP */
         return(child_ldap(filter));
   }


///////////////////
//               //
// Main Function //
//               //
///////////////////
int main(void) {
                           
   /* Declares Local Vars */
      struct childpids *last_child = NULL;
      int filtercount = 0;
      int pid = 0;

      alarm(UPDATE_FREQ);
      ldapblaster_timestamp = time(NULL);
      signal_init_parent();
      while (ldapblaster_exit == FALSE) {
         if (ldapblaster_children < MAX_CHILDREN) {
            pid = spawn_child(filtercount);
            if (pid == 0)
               return(0);
            if (pid > 0) {
               if (last_child == NULL) {
                  last_child = (struct childpids *) malloc(sizeof(struct childpids));
                  if (last_child == NULL) {
                     fprintf(stderr, "Out of Virtual Memory. Must exit now\n");
                     ldapblaster_exit = TRUE;
                    } else {
                     memset(last_child, 0, sizeof(struct childpids));
                     last_child->pid = pid;
                     last_child->timestamp = time(NULL);
                  };
                 } else {
                  last_child->next = (struct childpids *) malloc(sizeof(struct childpids));
                  if (last_child == NULL) {
                     fprintf(stderr, "Out of Virtual Memory. Must exit now\n");
                     ldapblaster_exit = TRUE;
                    } else {
                     memset(last_child->next, 0, sizeof(struct childpids));
                     last_child->next->previous = last_child;
                     last_child = last_child->next;
                     last_child->pid = pid;
                     last_child->timestamp = time(NULL);
                  };
               };
               filtercount++;
               if (filtercount > 114)
                  filtercount = 0;
               ldapblaster_children++;
               ldapblaster_spawned++;
               if (ldapblaster_spawned >= MAX_RUNS)
                  ldapblaster_exit = TRUE;
               if (time(NULL) >= (ldapblaster_timestamp + MAX_RUN_TIME))
                  ldapblaster_exit = TRUE;
               
            };
         };
         if (last_child != NULL)
            last_child = (struct childpids *) child_cleanup(last_child);
      };
  
      setvbuf(stdout, NULL, _IONBF, 0);
      printf("Waiting for our children to exit\n");
      printf("|");
      for (filtercount = 0; filtercount < 20; filtercount++)
         printf("-");
      printf("|\n|");
      for (filtercount = 0; filtercount < 20; filtercount++) {
         sleep(1);
         printf(".");
      };
      printf("|\n");
      stats();
      return(0);
      

}
