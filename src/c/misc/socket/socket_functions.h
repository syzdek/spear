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
 *  src/c/socket/socket_functions.h - prototypes for tcp socket functions
 */
#ifndef _SPEAR_SRC_C_SOCKET_SOCKET_FUNCTIONS_H
#define _SPEAR_SRC_C_SOCKET_SOCKET_FUNCTIONS_H 1

///////////////////
//               //
//  Definitions  //
//               //
///////////////////

#undef SPEAR_DEFAULT_HOST
#define SPEAR_DEFAULT_HOST	"localhost"

#undef SPEAR_DEFAULT_SERVICE
#define SPEAR_DEFAULT_SERVICE	1982


///////////////
//           //
//  Headers  //
//           //
///////////////

#ifdef _SPEAR_SRC_C_SOCKET_SOCKET_FUNCTIONS_C

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <inttypes.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

#include <spear.h>

#endif

#ifndef SO_NOSIGPIPE
#define SO_NOSIGPIPE SO_REUSEADDR
#endif


//////////////////
//              //
//  Prototypes  //
//              //
//////////////////

/* creates a socket and binds to interface */
int * socket_bind PARAMS((const char * host, const char * service, int socktype));

/* closes list of file descriptors */
void socket_close_slist PARAMS((int * slist));

/* creates a socket and connects to remote host */
int socket_connect PARAMS((const char * host, const char * service, int socktype));

/* counts sockets in list */
int socket_slist_len PARAMS((int * slist));

#endif /* End Header File */
