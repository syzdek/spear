/*
 *  $Id: $
 */
/*
 *  Simple Objective-C Object Experiment
 *  Copyright (C) 2008 David M. Syzdek <david@syzdek.net>.
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
 *  cBindings.h - wraps Objective-C object for C functions
 */
#ifndef _CBINDINGS_H
#define _CBINDINGS_H 1


///////////////
//           //
//  Headers  //
//           //
///////////////

#ifdef _CBINDINGS_M
#include <objc/Object.h>
#include <stdio.h>
#include <stdlib.h>
#include "MyClass.h"
#endif


//////////////////
//              //
//  Prototypes  //
//              //
//////////////////

void * init(void);
void   setNum1(void * ptr, int num);
int    num1(void * ptr);
void   release(void * ptr);

#endif /* end of header file */
