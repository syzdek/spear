/*
 * Simple Socket Server v0.
 * $Source$
 * $Revision$
 * $Date$
 * $Author$
 */
/*
 * tcp_socket_server.c - simple socket server for playing with TCP servers
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
 *    gcc -g -o tcp_socket_server.o tcp_socket_server.c -lresolv
 */

/////////////
//         //
// Headers //
//         //
/////////////

   #include <stdio.h>		/* Basic I/O routines          */
   #include <sys/types.h>	/* standard system types       */
   #include <sys/socket.h>	/* socket interface functions  */
   #include <netinet/in.h>	/* Internet address structures */
   #include <netdb.h>		/* host to IP resolution       */
   #include <sys/poll.h>	/* wait for some event         */


/////////////////////
//                 //
// Global Settings //
//                 //
/////////////////////

   #define PORT		8080
   #define ADDRESS	"127.0.0.1"


///////////////////
//               //
// Main Function //
//               //
///////////////////

int main(int *argc, char **argv) {

   /* Declares Local Vars */
      int	rc;		/* system calls return value storage  */
      int	s;		/* socket descriptor                  */
      int	cs;		/* new connection's socket descriptor */
      struct sockaddr_in sa;	/* Internet address struct            */
      struct sockaddr_in csa;	/* client's address struct            */
      int	size_csa;	/* size of client's address struct    */

   /* clear out the struct, to avoid garbage */
      memset(&sa, 0, sizeof(sa));

   /* Using Internet address family */
      sa.sin_family = AF_INET;

   /* copy port number in network byte order */
      sa.sin_port = htons(PORT);

   /* we will accept connections coming through any IP address that belongs to our host, using the INADDR_ANY wild-card. */
      sa.sin_addr.s_addr = INADDR_ANY;

   /* allocate a free socket */
      s = socket(AF_INET, SOCK_STREAM, 0);
      if (s < 0) {
         perror("socket: allocation failed");
      };

   /* bind the socket to the newly formed address */
      rc = bind(s, (struct sockaddr *)&sa, sizeof(sa));
      if (rc) {
         perror("bind");
      };

   /* ask the system to listen for incoming connections   */
      rc = listen(s, 5);
      if (rc) {
         perror("listen");
      };

   /* remember size for later usage */
      size_csa = sizeof(csa);

   /* Handle Connections */
      while(1) {
         cs = 
         cs = accept(s, (struct sockaddr *)&csa, &size_csa);
         if (cs < 0)
            continue;

         write(cs, "This is a test message\n", sizeof("This is a test message\n"));

        close(cs);
      };
      return(0);

};
