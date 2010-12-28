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
 *  src/c/socket/tcp_server.h - prototypes for simple tcp server
 */
#ifndef _SPEAR_SRC_C_SOCKET_TCP_SERVER_H
#define _SPEAR_SRC_C_SOCKET_TCP_SERVER_H 1

///////////////
//           //
//  Headers  //
//           //
///////////////

#ifdef _SPEAR_SRC_C_SOCKET_TCP_SERVER_C

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <inttypes.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <spear.h>

#include "socket_functions.h"

#endif


//////////////////
//              //
//  Prototypes  //
//              //
//////////////////

/* main statement */
int main PARAMS((int argc, char * argv[]));

#endif /* End Header File */
