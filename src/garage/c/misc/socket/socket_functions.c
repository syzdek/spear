/*
 *  $Id: $
 */
/*
 *  Simple Programming Examples and References
 *  Copyright (C) 2007 David M. Syzdek <syzdek@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */
/*
 *  src/c/socket/socket_functions.c - socket functions
 */
#define _SPEAR_SRC_C_SOCKET_SOCKET_FUNCTIONS_C 1
#include "socket_functions.h"

/////////////////
//             //
//  Functions  //
//             //
/////////////////

/* creates a socket and binds to interface */
int * socket_bind(const char * host, const char * service, int socktype)
{
   /* declares local vars */
   int               s;		// stores socket number
   int               e;		// stores error code from getaddrinfo()
   int               opt;	// user to set socket options
   int             * ptr;	// used when reallocating memory
   int             * slist;	// array of socket handles
   int               slist_len;	// length of socket list
   size_t            len;	// used to calculate memory allocations
   struct addrinfo * r;
   struct addrinfo * res;
   struct addrinfo   hints;
   char              hbuff[NI_MAXHOST];
   char              sbuff[NI_MAXSERV];

   /* clears memory */
   memset(hbuff,  0, NI_MAXHOST);
   memset(sbuff,  0, NI_MAXSERV);
   memset(&hints, 0, sizeof(struct addrinfo));

   /* sets initial values */
   s                  = -1;
   slist              = NULL;
   slist_len          = 0;
   hints.ai_flags     = AI_PASSIVE|AI_ADDRCONFIG;
   hints.ai_socktype  = socktype;

   /* resolves host and port */
   if ((e = getaddrinfo(host, service, &hints, &res)) != 0)
   {
      fprintf(stderr, "getaddrinfo(): %s\n", gai_strerror(e));
      return(NULL);
   };

   /* loops through results */
   for(r = res; r; r = r->ai_next)
   {
      /* prints host information */
      getnameinfo(r->ai_addr, r->ai_addrlen, hbuff, NI_MAXHOST, sbuff,
                  NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV);
      printf("attempting to bind to %s %s...\n", hbuff, sbuff);

      /* creates socket */
      if ((s = socket(r->ai_family, r->ai_socktype, r->ai_protocol)) == -1)
      {
         perror("socket()");
         return(NULL);
      };

      /* sets socket options */
      opt = 1;
      setsockopt(s, SOL_SOCKET, SO_NOSIGPIPE, (void *)&opt, sizeof(int));
      opt = 1;
      setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (void *)&opt, sizeof(int));
      opt = 1;
      if (socktype == SOCK_STREAM)
         setsockopt(s, SOL_SOCKET, SO_KEEPALIVE, (void *)&opt, sizeof(int));

      /* binds to socket */
      if ((bind(s, r->ai_addr, r->ai_addrlen)) == -1)
      {
         perror("bind()");
         close(s);
         s = -1;
      };

      /* listens for connections */
      if (s != -1)
         if (listen(s, 5))
         {
            perror("listen()");
            close(s);
            s = -1;
         };

      /* allocates memory in slist for new socket */
      if (s != -1)
      {
         len = sizeof(int) * (slist_len + 2);
         if (!(ptr = (int *) realloc(slist, len)))
         {
            fprintf(stderr, "%s: out of virtual memory\n", PROGRAM_NAME);
            close(s);
            return(NULL);
         };
         slist            = ptr;
         slist[slist_len] = s;
         slist_len++;
         slist[slist_len] = -1;
      };
   };

   /* frees memory */
   freeaddrinfo(res);

   /* ends function */
   return(slist);
}


/* closes list of file descriptors */
void socket_close_slist(int * slist)
{
   int   i;
   if (!(slist))
      return;
   for(i = 0; slist[i] != -1; i++)
      close(slist[i]);
   free(slist);
   return;
}


/* creates a socket and connects to remote host */
int socket_connect(const char * host, const char * service, int socktype)
{
   /* declares local vars */
   int               s;
   int               e;
   int               opt;
   struct addrinfo * r;
   struct addrinfo * res;
   struct addrinfo   hints;
   char              hbuff[NI_MAXHOST];
   char              sbuff[NI_MAXSERV];

   /* clears memory */
   memset(hbuff,  0, NI_MAXHOST);
   memset(sbuff,  0, NI_MAXSERV);
   memset(&hints, 0, sizeof(struct addrinfo));

   /* sets initial values */
   s = -1;
   hints.ai_socktype = socktype;
#ifdef AI_ADDRCONFIG
   hints.ai_flags    = AI_ADDRCONFIG;
#endif

   /* resolves host and port */
   if ((e = getaddrinfo(host, service, &hints, &res)) != 0)
   {
      fprintf(stderr, "getaddrinfo(): %s\n", gai_strerror(e));
      return(-1);
   };

   /* loops through results */
   for(r = res; r; r = r->ai_next)
   {
      /* prints host information */
      getnameinfo(r->ai_addr, r->ai_addrlen, hbuff, NI_MAXHOST, sbuff,
                  NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV);
      printf("attempting to connect to %s %s...\n", hbuff, sbuff);

      /* creates socket */
      if ((s = socket(r->ai_family, r->ai_socktype, r->ai_protocol)) == -1)
      {
         perror("socket()");
         return(-1);
      };

      /*
       *  disables signal sigpipe
       *  Note:
       *     This prevents the application from terminating when a socket
       *     terminates unexpectedly and triggers an unhandled SIGPIPE.
       */
#ifdef SO_NOSIGPIPE
      opt = 1;
      if (setsockopt(s, SOL_SOCKET, SO_NOSIGPIPE, (void *)&opt, sizeof(int)))
      {
         perror("setsockopt()");
         close(s);
         return(-1);
      };
#endif

      /*
       *  enables TCP keep alives
       *  Note:
       *     This should be implemented in the application layer
       *     if possible whether the purpose is to tear down an idle
       *     connection or to maintain a connection which passes through
       *     a firewall.  For UDP connections, keepalives must be performed
       *     at the application layer.
       */
      if (socktype == SOCK_STREAM)
      {
         opt = 1;
         if (setsockopt(s, SOL_SOCKET, SO_KEEPALIVE, (void *)&opt, sizeof(int)))
         {
            perror("setsockopt()");
            close(s);
            return(-1);
         };
      };

      /* connects socket to remote host */
      if (!(connect(s, r->ai_addr, r->ai_addrlen)))
           break;

       perror("connect()");
       close(s);
       s = -1;
   };

   /* frees memory */
   freeaddrinfo(res);

   if (s == -1)
   {
      fprintf(stderr, "connection attempt failed\n");
      return(-1);
   };

   /* sets socket to non-blocking */
//   if ((fcntl(s, F_SETFL, O_NONBLOCK)) == -1)
//   {
//      perror("sfcntl()");
//      close(s);
//      return(-1);
//   };

   /* ends function */
   return(s);
}


/* counts sockets in list */
int socket_slist_len(int * slist)
{
   int i;
   if (!(slist))
      return(0);
   for(i = 0; slist[i] != -1; i++);
   return(i);
}


/* end of source file */
