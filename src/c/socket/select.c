/*
 * libwrap.c - simple example of using libwrap
 * $Source$
 * $Revision$
 * $Date$
 * $Author$
 */
/*
 * Build:
 *    gcc -g -o select.o select.c			// Slackware 8.1
 *    gcc -g -o select.o select.c -lsocket -lnsl	// Solaris 5.9
 */

/////////////
//         //
// Headers //
//         //
/////////////
				/********************************/
   #include <stdio.h>		/* Basic I/O routines 		*/
   #include <sys/types.h>	/* standard system types 	*/
   #include <netinet/in.h>	/* Internet address structures 	*/
   #include <sys/socket.h>	/* socket interface functions 	*/
   #include <netdb.h>		/* host to IP resolution 	*/
   #include <sys/time.h>	/* for timeout values 		*/
   #include <unistd.h>		/* for table size calculations 	*/
   #include "example.h"		/* Configs for examples         */
				/********************************/

///////////////////
//               //
// Main Function //
//               //
///////////////////
int main() {

   /* local Vars */
      struct sockaddr_in si;
      struct sockaddr_in sic;
      int si_len;
      int sic_len;
      int s;
      int sc;
      int rc;

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

   /* Configure Socket */            
      si.sin_family = AF_INET;      
      si.sin_port = htons(LOCAL_PORT);
      si.sin_addr.s_addr = INADDR_ANY;

   /* Bind Socket to interface/port */
      if (bind(s, (struct sockaddr*)&si, sizeof(struct sockaddr)) != 0) {
         perror("socket");
         return(1);
      };

   /* Listen for 2 incoming connections */
      if (listen(s, 5) != 0) {
         perror("listen");
         return(1);
      };

   /* loops indefinetly listening for connections */
}
