/*
 * select.c - simple example of using select()
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
int main(int argc, char *argv[]) {

   /* local Vars */
      struct sockaddr_in si;		/* Internet address struct */
      struct sockaddr_in sic;		/* client's address struct */
      int si_len;			/* size of Internet address struct */
      int sic_len;			/* size of client's address struct */
      int s;				/* socket descriptor */
      int sc;				/* new connection's socket descriptor */
      int rc;				/* system calls return value storage */
      fd_set rfd;			/* set of open sockets */
      fd_set c_rfd;			/* set of sockets waiting to be read */
      int dsize;			/* size of file descriptors table */
      int i;				/* index counter for loop operations */
      int ccount;			/* count of number of current connections */
      int lcount;			/* last count of number of current connections */
      char ibuf[INPUT_BUFFER+1];	/* buffer for incoming data */

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

   /* calculate size of file descriptors table */
      dsize = getdtablesize();

   /* close all file descriptors, except our communication socket	*/
   /* this is done to avoid blocking on tty operations and such.	*/
      //for (i=0; i<dsize; i++)
      //   if (i != s)
      //      close(i);

   /* we innitialy have only one socket open,	*/
   /* to receive new incoming connections.	*/
      FD_ZERO(&rfd);
      FD_SET(s, &rfd);

   /* loops indefinetly listening for connections */
      ccount = 0;
      lcount = 1;
      while(1) {
         if (ccount != lcount) {
            printf("Number of concurrent connections: %i\n", ccount);
            lcount = ccount;
         };
         c_rfd = rfd;
         rc = select(dsize, &c_rfd, NULL, NULL, (struct timeval *)NULL);

         /* Checks to see if new connection came in */
            if (FD_ISSET(s, &c_rfd)) {

               /* Accepts connection */
                  sc = accept(s, (struct sockaddr *)&sic, &sic_len);
                  if (sc < 0)
                     continue;

               /* prints hello */
                  ccount++;
                  write(sc, argv[0], strlen(argv[0]));
                  write(sc, " $Revision$\ntype '.' to exit\n", sizeof(" $Revision$\ntype '.' to exit\n"));

               /* add the new socket to the set of open sockets */
                  FD_SET(sc, &rfd);

              /* Loop again */
                 continue;
            };

         /* Check for sockets ready for reading */
            for (i=0; i<dsize; i++) {
               if (i != s && FD_ISSET(i, &c_rfd)) {
                  memset(&ibuf, 0, INPUT_BUFFER);
                  rc = read(i, ibuf, INPUT_BUFFER);
                  if (rc == 0) {
                     close(i);
                     FD_CLR(i, &rfd);
                     ccount--;
                    } else {
                     if ((rc == 3)&&(ibuf[0] == '.')) {
                        write(i, "BYE\n", sizeof("BYE\n"));
                        close(i);
                        FD_CLR(i, &rfd);
                        ccount--;
                       } else {
                        write(i, ibuf, rc);
                     };
                  };
               };
            };
      };
};














