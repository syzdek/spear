/*
 * socket-server.c - simple socket server
 * $Source$
 * $Revision$
 * $Date$
 * $Author$
 */
/*
 * Build:
 *    gcc -g -o socket-server.o socket-server.c			// Slackware 8.1
 *    gcc -g -o socket-server.o socket-server.c -lsocket	// Solaris 5.9
 */

/////////////
//         //
// Headers //
//         //
/////////////
										/***************************************/
   #include	<stdio.h>							/* standard I/O                        */
   #include	<netdb.h>							/* network functions and types         */
   #include     "example.h"							/* Configurations for example programs */
										/***************************************/
///////////////////
//               //
// Main Function //
//               //
///////////////////
int main(int argc, char *argv[]) {

   /* local Vars */								/*************************************/
      struct sockaddr_in si;							/* Main socket information           */
      struct sockaddr_in sic;							/* Child socket information          */
      int si_len;								/* size of si                        */
      int sic_len;								/* size of sic                       */
      int s;									/* listening socket                  */
      int sc;									/* socket child                      */
      int rc;									/* return code                       */
										/*************************************/

   /* Clear structs to avoid garbage */
      memset(&si, 0, sizeof(si));
      memset(&sic, 0, sizeof(sic));

   /* sets to size of structs */
      si_len = sizeof(si);
      sic_len = sizeof(sic);

   /* Create Socket */								/**********************************/
      s = socket(AF_INET, SOCK_STREAM,0);					/* AF_INET     -- Internet class  */
      if(s == -1) {								/* SOCK_STREAM -- TCP connection  */
         perror("No socket");							/* 0           -- Extra protocols */
         return(1);								/**********************************/
      };

   /* Configure Socket */							/***************************/
      si.sin_family = AF_INET;							/* Sets type of connection */
      si.sin_port = htons(LOCAL_PORT);						/* Sets TCP port           */
      si.sin_addr.s_addr = INADDR_ANY;						/* Listen on any address   */
										/***************************/

   /* Bind Socket to interface/port */						/************************************/
      if (bind(s, (struct sockaddr*)&si, sizeof(struct sockaddr)) != 0) {	/* Bind program with config from si */
         perror("socket");							/************************************/
         return(1);
      };

   /* Listen for 2 incoming connections */					/****************************************************/
      if (listen(s, 2) != 0) {							/* Since we are a server, set socket to listen      */
         perror("listen");							/* and allow 2 pending connections before rejecting */
         return(1);								/* connections                                      */
      };									/****************************************************/

   /* Handles connection to clients */

      /* waits for incoming connections */					/*********************************************/
         sc = accept(s, (struct sockaddr*)&sic, &sic_len);			/* Wait for an incoming connection and spawn */
         if (sc < 0) {								/* a child socket. Skip and disregard if     */
            close(sc);								/* connection has any problems.              */
         };									/*********************************************/
      
      /* Prints to connection and closes */					/*******************************************/
         write(sc, "\n\nHello World\n\n", sizeof("\n\nHello World\n\n"));	/* Send data to client via the socket      */
         close(sc);								/* Closes socket child (client connection) */
         									/*******************************************/

   /* Close socket and exit */							/***************************/
      close(s);									/* Closes listening socket */
      return(0);								/* Ends program            */
										/***************************/
}; 


