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
/*  src/c/socket/tcp_client.c - simple TCP client */
/*
 *  Build:
 *     libtool --mode=compile   gcc -g -O2 -c src/c/socket/socket_functions.c
 *     libtool --mode=compile   gcc -g -O2 -c src/c/socket/tcp_client.c
 *     libtool --mode=link      gcc -g -O2 -o src/c/socket/tcp_client \
 *                                            src/c/socket/socket_functions.o \
 *                                            src/c/socket/tcp_client.o
 *     libtool --mode=clean     rm -f  src/c/socket/tcp_client \
 *                                     src/c/socket/socket_functions.lo \
 *                                     src/c/socket/tcp_client.lo
 */
#define _SPEAR_SRC_C_SOCKET_TCP_CLIENT_C 1
#include "tcp_client.h"

/////////////////
//             //
//  Functions  //
//             //
/////////////////

/* main statement */
int main(int argc, char * argv[])
{
   /* declares local vars */
   int s;
   int len;
   char buff[1024];

   /* checks for arguments */
   if (argc < 3)
   {
      fprintf(stderr, "usage: %s <ip> <port>\n", PROGRAM_NAME);
      return(1);
   };

   /* opens tcp socket to remote IP address */
   if ((s = socket_connect(argv[1], argv[2], SOCK_STREAM)) == -1)
      return(1);

   if ((len = read(s, buff, 1023)) == -1)
   {
      perror("read()");
      close(s);
      return(1);
   };
   buff[len] = '\0';
   printf("<< %s", buff);

   len = snprintf(buff, 1023, "HELO blah\r\n");
   buff[len] = '\0';
   printf(">> %s", buff);
   if ((write(s, buff, (unsigned)len)) ==  -1)
   {
      perror("write()");
      close(s);
      return(1);
   };

   if ((len = read(s, buff, 1023)) == -1)
   {
      perror("read()");
      close(s);
      return(1);
   };
   buff[len] = '\0';
   printf("<< %s", buff);

   /* closes socket */
   close(s);

   /* ends function */
   return(0);
}


/* end of source file */
