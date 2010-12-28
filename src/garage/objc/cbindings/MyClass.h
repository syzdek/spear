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
 *  MyClass.h - simple object
 */
#ifndef _MYCLASS_H
#define _MYCLASS_H 1

///////////////
//           //
//  Headers  //
//           //
///////////////

#include <objc/Object.h>
#include <stdlib.h>


///////////////////////
//                   //
//  Class Definition //
//                   //
///////////////////////
@interface MyClass : Object
{
   int owners;
   int var0;
   int var1;
   int var2;
   int var3;

   char buff[1572864];
}

- (void) retain;
- (void) release;

- (int)  var1;
- (void) setVar1:(int)anInt;

- (int)  var2;
- (void) setVar2:(int)anInt;

- (int)  var3;
- (void) setVar3:(int)anInt;

@end

#endif /* end of header */
