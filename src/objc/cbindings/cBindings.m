/*
 *  $Id: $
 */
/*
 *  Simple Objective-C Object Experiment
 *  Copyright (c) 2008 David M. Syzdek <david@syzdek.net>
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
#define _CBINDINGS_M 1
#include "cBindings.h"

/////////////////
//             //
//  Functions  //
//             //
/////////////////

void * init(void)
{
   void * myObject;

   printf("sizeof(MyClass) == %lu\n", sizeof(MyClass));

   myObject = [[MyClass alloc] init];

   return(myObject);
}


void release(void * ptr)
{
   MyClass * obj;
   obj = ptr;
   [obj release];
   return;
}


void setNum1(void * ptr, int num)
{
   MyClass * obj;
   obj = ptr;
   [obj setVar1:num];
   return;
}


int num1(void * ptr)
{
   MyClass * obj;
   obj = ptr;
   return([obj var1]);
}

/* end of source file */
