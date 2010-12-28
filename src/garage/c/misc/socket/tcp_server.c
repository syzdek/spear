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
/*  src/c/socket/tcp_server.c - simple TCP server */
/*
 *  Build:
 *     libtool --mode=compile   gcc -g -O2 -c src/c/socket/socket_functions.c
 *     libtool --mode=compile   gcc -g -O2 -c src/c/socket/tcp_server.c
 *     libtool --mode=link      gcc -g -O2 -o src/c/socket/tcp_server \
 *                                            src/c/socket/socket_functions.o \
 *                                            src/c/socket/tcp_server.o
 *     libtool --mode=clean     rm -f  src/c/socket/tcp_server \
 *                                     src/c/socket/socket_functions.lo \
 *                                     src/c/socket/tcp_server.lo
 */
#define _SPEAR_SRC_C_SOCKET_TCP_SERVER_C 1
#include "tcp_server.h"

/////////////////
//             //
//  Functions  //
//             //
/////////////////

/* main statement */
int main(int argc, char * argv[])
{
   /* declares local vars */
//   int              s;
   int              x;
//   int              y;
   int              term;
//   int            * ptr;
   int            * clist;
   int            * slist;
   fd_set           rfd;
   fd_set           c_rfd;
   struct timeval   timeout;

   /* sets initial values */
   clist = NULL;
   slist = NULL;

   /* checks for arguments */
   if (argc < 3)
   {
      fprintf(stderr, "usage: %s <ip> <port>\n", argv[0]);
      return(1);
   };

   /* opens tcp socket to remote IP address */
   if (!(slist = socket_bind(NULL, "8080", SOCK_STREAM)))
      return(1);

   /* inits socket set and adds sockets */
   FD_ZERO(&rfd);
   for(x = 0; slist[x] != -1; x++)
      FD_SET(slist[x], &rfd);

   /* master network work */
   term = 1;
   while(term)
   {
      /* sets initial values for select() */
      timeout.tv_sec  = 5;
      timeout.tv_usec = 0;
      c_rfd           = rfd;

      /* wait for an event */
      select(getdtablesize(), &c_rfd,  NULL, NULL, &timeout);

      /* loops through sockets */
      for(x = 0; slist[x] != -1; x++)
      {
         if (FD_ISSET(slist[x], &c_rfd))
         {
         };
      };
      term = 0;
   };

   /* closes socket */
   socket_close_slist(slist);

   /* ends function */
   return(0);
}


/* end of source file */
