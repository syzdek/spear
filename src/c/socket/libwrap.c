/*
 * libwrap.c - simple example of using libwrap
 * $Source$
 * $Revision$
 * $Date$
 * $Author$
 */
/*
 * Build:
 *    gcc -g -o libwrap.o libwrap.c -lwrap
 */

/////////////
//         //
// Headers //
//         //
/////////////
									/******************************************/
   #include	<tcpd.h>						/* libwrap include file                   */
   #include	<stdio.h>						/* standard I/O                           */
   #include	<netdb.h>						/* Network include file                   */
   #include	<syslog.h>						/* Syslog include file (needed by libwrap */
   #include     "example.h"						/* Configurations for example programs    */
									/******************************************/

/////////////////////
//                 //
// Global Settings //
//                 //
/////////////////////

   /* libwrap logging settings */					/******************/
      int allow_severity=LOG_INFO;					/* used by tcpd.h */
      int deny_severity=LOG_NOTICE;					/* used by tcpd.h */
									/******************/

///////////////////
//               //
// Main Function //
//               //
///////////////////
int main(int argc, char *argv[]) {

   /* local Vars */							/*************************************/
      struct sockaddr_in si;						/* Main socket information           */
      struct sockaddr_in sic;						/* Child socket information          */
      int si_len;							/* size of si                        */
      int sic_len;							/* size of sic                       */
      int s;								/* listening socket                  */
      int sc;								/* Child socket                      */
      int rc;								/* return code                       */
      int count;							/* Counts number handled connections */
      struct request_info rinfo;					/* Used for libwrap                  */
									/*************************************/

   /* Clear structs to avoid garbage */
      memset(&si, 0, sizeof(si));
      memset(&sic, 0, sizeof(sic));

   /* sets zie of structs */
      si_len = sizeof(si);
      sic_len = sizeof(sic);

   /* Create Socket */
      s = socket(AF_INET, SOCK_STREAM,0);
      if(s == -1) {
         perror("No socket");
         return(1);
      };

   /* Configure Socket */						/***************************/
      si.sin_family = AF_INET;						/* Sets type of connection */
      si.sin_port = htons(LOCAL_PORT);					/* Sets TCP port           */
      si.sin_addr.s_addr = INADDR_ANY;					/* Listen on any address   */
									/***************************/

   /* Bind Socket to interface/port */
      if (bind(s, (struct sockaddr*)&si, sizeof(struct sockaddr)) != 0) {
         perror("socket");
         return(1);
      };

   /* Listen for 2 incoming connections */
      if (listen(s, 2) != 0) {
         perror("listen");
         return(1);
      };

   /* Accept 5 connections */
      count = 0;
      while (count < 5) {
         count++;
         sc = accept(s, (struct sockaddr*)&sic, &sic_len);
         if (sc < 0) {
            close(sc);
            continue;
         };

         /* Verify host against libwrap */				/******************************************************/
            request_init(&rinfo,RQ_FILE,sc,RQ_DAEMON,PACKAGE,0);	/* PACKAGE is how libwrap determines what this daemon */
            fromhost(&rinfo);						/* is called in /etc/hosts.allow.  It was defined in  */
            if(!hosts_access(&rinfo)) {					/* example.h, see "man -S 3 hosts_access" for more.   */
               printf("This host is not authorized\n");			/* Should also log this to syslog.                    */
               close(sc);                                               /* Of course, terminate the connection if not allowed */
               continue;						/* Skip to next connect                               */
            };								/******************************************************/
         
         /* Prints to connection */
            printf("This host is authorized\n");
            write(sc, "\n\nYou are a authorized host\n\n", sizeof("\n\nYou are a authorized host\n\n"));

         /* Close connection */ 
            close(sc);

      }; 

   /* Close socket and exit */
      close(s);
      return(0);

}; 


