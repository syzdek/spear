/*
 * getpeername.c - simple example of getpeername() and getnameinfo()
 * $Source$
 * $Revision$
 * $Date$
 * $Author$
 */
/*
 * Build:
 *    gcc -g -o getpeername.o getpeername.c			// Slackware 8.1
 *    gcc -g -o getpeername.o getpeername.c -lsocket -lnsl	// Solaris 5.9
 */

/////////////
//         //
// Headers //
//         //
/////////////

   #include	<stdio.h>
   #include	<netdb.h>
   #include	<string.h>
   #include     "example.h"

///////////////////
//               //
// Main Function //
//               //
///////////////////
int main(int argc, char *argv[]) {

   /* local Vars */					/*************************************/
      struct sockaddr_in si;				/* Main socket information           */
      struct sockaddr_in sic;				/* Child socket information          */
      int si_len;					/* size of si                        */
      int sic_len;					/* size of sic                       */
      int s;						/* listening socket                  */
      int sc;						/* Child socket                      */
      int rc;						/* return code                       */
      int count;					/* Counts number handled connections */
      char hostbuf[80];					/* Remote host                       */
      char port[40];					/* Remote port                       */
      char *host;					/* Pointer for hostbuf               */
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

   /* Configure Socket */				/***************************/
      si.sin_family = AF_INET;				/* Sets type of connection */
      si.sin_port = htons(LOCAL_PORT);			/* Sets TCP port           */
      si.sin_addr.s_addr = INADDR_ANY;			/* Listen on any address   */
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
         
         /* use getpeername() to identify remote host */
            if(getpeername(s, (struct sockaddr*)&sic, &sic_len)) {
               printf("Connection from %s using getpeername().\n", inet_ntoa(sic.sin_addr));
            };

         /* use getnameinfo() to identify remote host */
            host = hostbuf;
            getnameinfo((struct sockaddr *)&sic, sizeof(struct sockaddr), hostbuf, 80, port, 40, NI_NUMERICHOST|NI_NUMERICSERV);
            if ((strncmp(host,"::ffff:",7)==0)&&(strchr(host+7,':')==NULL))
               host+=7;
            printf("Connection from %s %s using getnameinfo()\n\n", host, port);

         /* Prints to connection */
            write(sc, "\n\nHello computer at ", sizeof("\n\nHello computer at "));
            write(sc, host, strlen(host));
            write(sc, "\n\n", sizeof("\n\n"));

         /* Close connection */ 
            close(sc);

      }; 

   /* Close socket and exit */
      close(s);
      return(0);

}; 


